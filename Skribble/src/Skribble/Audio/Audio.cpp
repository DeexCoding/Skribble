#include "skpch.h"

#include "Audio.h"

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <thread>
#include <filesystem>

#include "AL/al.h"
#include "AL/alext.h"
#include "AL/../../src/alc/alcmain.h"
#include "alhelpers.h"

#define MINIMP3_IMPLEMENTATION
#include "minimp3.h"
#include "minimp3_ex.h"

#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

#include <libwav/wav.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Skribble
{
	static ALCdevice* audioDevice = nullptr;
	static mp3dec_t mp3d;

	static uint8_t* audioScratchBuffer;
	static uint32_t audioScratchBufferSize = 10 * 1024 * 1024;

	// Currently supported file formats
	enum class AudioFileFormat
	{
		None = 0,
		Ogg,
		MP3,
		Wav
	};

	static AudioFileFormat GetFileFormat(const std::string& filename)
	{
		std::filesystem::path path = filename;
		std::string extension = path.extension().string();

		if (extension == ".ogg")  return AudioFileFormat::Ogg;
		if (extension == ".mp3")  return AudioFileFormat::MP3;
		if (extension == ".wav")  return AudioFileFormat::Wav;

		SKRIBBLE_CORE_ERROR("Unknown audio file format!");
		SKRIBBLE_CORE_ASSERT(false, "Unknown audio file format!");

		return AudioFileFormat::None;
	}

	static ALenum GetOpenALFormat(uint32_t channels, uint32_t sampleSize)
	{
		// Note: sample size is always 2 bytes (16-bits) with
		// both the .mp3 and .ogg decoders that we're using
		
		if (channels == 1)
		{
			if (sampleSize == 2)
			{
				return AL_FORMAT_MONO16;
			}
			else if (sampleSize == 4)
			{
				return AL_FORMAT_MONO_FLOAT32;
			}
			else
			{
				SKRIBBLE_CORE_ERROR("Sample size not supported!");
				SKRIBBLE_CORE_ASSERT(false, "Sample size not supported!");
			}
		}
		else if (channels == 2)
		{
			if (sampleSize == 2)
			{
				return AL_FORMAT_STEREO16;
			}
			else if (sampleSize == 4)
			{
				return AL_FORMAT_STEREO_FLOAT32;
			}
			else
			{
				SKRIBBLE_CORE_ERROR("Sample size not supported!");
				SKRIBBLE_CORE_ASSERT(false, "Sample size not supported!");
			}
		}
		else
		{
			SKRIBBLE_CORE_ERROR("Channel ammount not supported!");
			SKRIBBLE_CORE_ASSERT(false, "Channel ammount not supported!");
		}

		SKRIBBLE_CORE_ERROR("Unknown OpenAL format!");
		SKRIBBLE_CORE_ASSERT(false, "Unknown OpenAL format!");

		return AL_NONE;
	}

	Ref<AudioSource> Audio::LoadAudioSourceOgg(const std::string& filename)
	{
		FILE* f = fopen(filename.c_str(), "rb");

		OggVorbis_File vf;

		if (ov_open_callbacks(f, &vf, NULL, 0, OV_CALLBACKS_NOCLOSE) < 0)
		{
			SKRIBBLE_CORE_ERROR("Could not open ogg stream");
		}

		// Useful info
		vorbis_info* vi = ov_info(&vf, -1);
		auto sampleSize = 2; //2 bytes per sample (I'm guessing...)
		auto sampleRate = vi->rate;
		auto channels = vi->channels;
		auto alFormat = GetOpenALFormat(channels, sampleSize); 

		uint64_t samples = ov_pcm_total(&vf, -1);
		float trackLength = (float)samples / (float)sampleRate; // in seconds
		uint32_t bufferSize = sampleSize * channels * (uint32_t)samples;

		SKRIBBLE_CORE_INFO("File Info - {0} : ", filename);
		SKRIBBLE_CORE_INFO("  Channels: {0}", channels);
		SKRIBBLE_CORE_INFO("  Sample Rate: {0}", sampleRate);
		SKRIBBLE_CORE_INFO("  Expected size: {0}", bufferSize);

		// TODO: Replace with Skribble::Buffer
		if (audioScratchBufferSize < bufferSize)
		{
			audioScratchBufferSize = bufferSize;
			delete[] audioScratchBuffer;
			audioScratchBuffer = new uint8_t[audioScratchBufferSize];
		}

		uint8_t* oggBuffer = audioScratchBuffer;
		uint8_t* bufferPtr = oggBuffer;
		int eof = 0;
		while (!eof)
		{
			int current_section;
			long length = ov_read(&vf, (char*)bufferPtr, 4096, 0, 2, 1, &current_section);
			bufferPtr += length;
			if (length == 0)
			{
				eof = 1;
			}
			else if (length < 0)
			{
				if (length == OV_EBADLINK)
				{
					SKRIBBLE_CORE_ERROR("Corrupt bitstream section!");
					SKRIBBLE_CORE_ASSERT(false, "Corrupt bitstream section!");
				}
			}
		}

		uint32_t size = (uint32_t)(bufferPtr - oggBuffer);
		SKRIBBLE_CORE_ASSERT(bufferSize == size, "Invalid size!");

		SKRIBBLE_CORE_TRACE("  Read {0} bytes", size);

		// Release file
		ov_clear(&vf);
		fclose(f);

		ALuint buffer;
		alGenBuffers(1, &buffer);
		alBufferData(buffer, alFormat, oggBuffer, size, sampleRate);

		Ref<AudioSource> result = CreateRef<AudioSource>((uint32_t)buffer, true, trackLength);
		alGenSources(1, &result->sourceHandle);
		alSourcei(result->sourceHandle, AL_BUFFER, buffer);

		if (alGetError() != AL_NO_ERROR)
		{
			SKRIBBLE_CORE_ERROR("Failed to setup sound source");
			SKRIBBLE_CORE_ASSERT(false, "Failed to setup sound source");
		}

		return result;
	}

	Ref<AudioSource> Audio::LoadAudioSourceMP3(const std::string& filename)
	{
		mp3dec_file_info_t info;
		int loadResult = mp3dec_load(&mp3d, filename.c_str(), &info, NULL, NULL);
		uint32_t size = (uint32_t)(info.samples * sizeof(mp3d_sample_t));

		auto sampleRate = info.hz;
		auto channels = info.channels;
		auto alFormat = GetOpenALFormat(channels, 2); // 2 bytes per sample (I'm guessing...)
		float lengthSeconds = size / (info.avg_bitrate_kbps * 1024.0f);

		ALuint buffer;
		alGenBuffers(1, &buffer);
		alBufferData(buffer, alFormat, info.buffer, size, sampleRate);

		Ref<AudioSource> result = CreateRef<AudioSource>((uint32_t)buffer, true, lengthSeconds);
		alGenSources(1, &result->sourceHandle);
		alSourcei(result->sourceHandle, AL_BUFFER, buffer);

		SKRIBBLE_CORE_INFO("File Info - {0} : ", filename);
		SKRIBBLE_CORE_INFO("  Channels: {0}", channels);
		SKRIBBLE_CORE_INFO("  Sample Rate: {0}", sampleRate);
		SKRIBBLE_CORE_INFO("  Size: {0} bytes", size);

		auto [mins, secs] = result->GetLengthMinutesAndSeconds();
		SKRIBBLE_CORE_INFO("  Length: {0}m {1}s", mins, secs);

		if (alGetError() != AL_NO_ERROR)
		{
			SKRIBBLE_CORE_TRACE("Failed to setup sound source");
		}

		return result;
	}

	Ref<AudioSource> Audio::LoadAudioSourceWav(const std::string& filename)
	{
		WavFile* wav = wav_open(filename.c_str(), WAV_OPEN_READ);

		const WavErr* err = wav_err();

		if (err->code != WAV_OK)
		{
			SKRIBBLE_CORE_ERROR("wav error: {0}", err->message);
			SKRIBBLE_CORE_ASSERT(false, "wav error: {0}", err->message);
		}

		// Useful info
		auto sampleSize = wav_get_sample_size(wav);
		auto sampleRate = wav_get_sample_rate(wav);
		auto channels = wav_get_num_channels(wav);
		auto alFormat = GetOpenALFormat((uint32_t)channels, (uint32_t)sampleSize);

		uint64_t samples = (uint64_t)wav_get_length(wav);
		float trackLength = (float)samples / (float)sampleRate; // in seconds
		//casting smaples (uint64_t) to uint32_t possible loss of data
		uint32_t bufferSize = (uint32_t)sampleSize * (uint32_t)channels * (uint32_t)samples;

		SKRIBBLE_CORE_INFO("File Info - {0} : ", filename);
		SKRIBBLE_CORE_INFO("  Channels: {0}", channels);
		SKRIBBLE_CORE_INFO("  Sample Rate: {0}", sampleRate);
		SKRIBBLE_CORE_INFO("  Expected size: {0}", bufferSize);

		// TODO: Replace with Skribble::Buffer
		if (audioScratchBufferSize < bufferSize)
		{
			audioScratchBufferSize = bufferSize;
			delete[] audioScratchBuffer;
			audioScratchBuffer = new uint8_t[audioScratchBufferSize];
		}

		wav_err_clear();
		uint8_t* wavBuffer = audioScratchBuffer;
		uint8_t* bufferPtr = wavBuffer;
		int eof = 0;
		while (!eof)
		{
			int framesRead = (int)wav_read(wav, (void*)bufferPtr, 4096 / sampleSize);
			long length = (long)(framesRead * sampleSize * channels);
			bufferPtr += length;
			if (framesRead < 4096 / sampleSize)
			{
				err = wav_err();

				if (err->code != WAV_OK)
				{
					SKRIBBLE_CORE_ERROR("wav error: {0}", err->message);
					SKRIBBLE_CORE_ASSERT(false, "wav error: {0}", err->message);
				}
				else
				{
					eof = 1;
				}
			}
		}

		uint32_t size = (uint32_t)(bufferPtr - wavBuffer);
		SKRIBBLE_CORE_ASSERT(bufferSize == size, "Invalid size!");

		SKRIBBLE_CORE_TRACE("  Read {0} bytes", size);

		// Release file
		wav_close(wav);

		ALuint buffer;
		alGenBuffers(1, &buffer);
		alBufferData(buffer, alFormat, wavBuffer, size, sampleRate);

		Ref<AudioSource> result = CreateRef<AudioSource>((uint32_t)buffer, true, trackLength);
		alGenSources(1, &result->sourceHandle);
		alSourcei(result->sourceHandle, AL_BUFFER, buffer);

		if (alGetError() != AL_NO_ERROR)
		{
			SKRIBBLE_CORE_ERROR("Failed to setup sound source");
			SKRIBBLE_CORE_ASSERT(false, "Failed to setup sound source");
		}

		return result;
	}

	void Audio::Initalize()
	{
		if (InitAL(audioDevice, nullptr, 0) != 0)
		{
			SKRIBBLE_CORE_ERROR("Audio device error!");
		}

		//PrintAudioDeviceInfo();

		mp3dec_init(&mp3d);

		audioScratchBuffer = new uint8_t[audioScratchBufferSize];

		// Init listener
		ALfloat listenerPos[] = { 0.0,0.0,0.0 };
		ALfloat listenerVel[] = { 0.0,0.0,0.0 };
		ALfloat listenerOri[] = { 0.0,0.0,-1.0, 0.0,1.0,0.0 };
		alListenerfv(AL_POSITION, listenerPos);
		alListenerfv(AL_VELOCITY, listenerVel);
		alListenerfv(AL_ORIENTATION, listenerOri);
	}

	Ref<AudioSource> Audio::LoadAudioSource(const std::string& filename)
	{
		auto format = GetFileFormat(filename);
		switch (format)
		{
		case AudioFileFormat::Ogg:  return LoadAudioSourceOgg(filename);
		case AudioFileFormat::MP3:  return LoadAudioSourceMP3(filename);
		case AudioFileFormat::Wav:  return LoadAudioSourceWav(filename);
		}

		SKRIBBLE_CORE_ERROR("Loading failed or unsupported file type");
		SKRIBBLE_CORE_ASSERT(false, "Loading failed or unsupported file type");
		return nullptr;
	}

	void Audio::Play(Ref<AudioSource> source)
	{
		alSourcePlay(source->sourceHandle);

		// TODO: current playback time and playback finished callback
		ALfloat offset;
		ALenum playState;
		alGetSourcei(source->sourceHandle, AL_SOURCE_STATE, &playState);
		alGetSourcef(source->sourceHandle, AL_SEC_OFFSET, &offset);
	}

	void Audio::Stop(Ref<AudioSource> source)
	{
		alSourceStop(source->sourceHandle);
	}

	AudioListener::AudioListener(glm::vec3 position, glm::vec3 rotation)
	{
		SetPosition(position);
		SetRotation(rotation);
	}

	AudioListener::~AudioListener()
	{
		SetPosition({ 0.0f, 0.0f, 0.0f });
		SetRotation({ 0.0f, 0.0f, 0.0f });
	}

	void AudioListener::SetGain(float gain)
	{
		this->gain = gain;
		alListenerf(AL_GAIN, gain);
	}

	void AudioListener::SetPosition(glm::vec3 position)
	{
		this->position = position;
		alListener3f(AL_POSITION, position.x, position.y, position.z);
	}

	void AudioListener::SetRotation(glm::vec3 rotation)
	{
		this->rotation = rotation;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { 0.0f, 0.0f, 0.0f });

		transform *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
		transform *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
		transform *= glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));

		glm::vec3 forward = transform * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		glm::vec3 upward = transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

		const ALfloat fwUp[] = { forward.x, forward.y, -forward.z, upward.x, upward.y, upward.z };
		alListenerfv(AL_ORIENTATION, fwUp);
	}

	AudioSource::AudioSource(uint32_t handle, bool loaded, float length)
		: bufferHandle(handle), loaded(loaded), totalDuration(length)
	{
	}

	AudioSource::~AudioSource()
	{
		alSourceStop(sourceHandle);

		alSourcei(sourceHandle, AL_BUFFER, 0);

		alDeleteBuffers(1, &bufferHandle);
		alDeleteSources(1, &sourceHandle);
	}

	void AudioSource::SetPosition(glm::vec3 position)
	{
		//alSource3f(sourceHandle, AL_VELOCITY, 0, 0, 0);

		//value_ptr might not work
		alSourcefv(sourceHandle, AL_POSITION, glm::value_ptr(position));
	}

	void AudioSource::SetGain(float gain)
	{
		this->gain = gain;

		alSourcef(sourceHandle, AL_GAIN, gain);
	}

	void AudioSource::SetPitch(float pitch)
	{
		this->pitch = pitch;

		alSourcef(sourceHandle, AL_PITCH, pitch);
	}

	void AudioSource::SetSpatial(bool spatial)
	{
		spatial = spatial;

		alSourcei(sourceHandle, AL_SOURCE_SPATIALIZE_SOFT, spatial ? AL_TRUE : AL_FALSE);
		alSourcei(sourceHandle, AL_SOURCE_RELATIVE, spatial ? AL_TRUE : AL_FALSE);
		alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	}

	void AudioSource::SetLoop(bool loop)
	{
		loop = loop;

		alSourcei(sourceHandle, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
	}

	std::pair<uint32_t, uint32_t> AudioSource::GetLengthMinutesAndSeconds() const
	{
		return { (uint32_t)(totalDuration / 60.0f), (uint32_t)totalDuration % 60 };
	}

	Ref<AudioSource> AudioSource::LoadFromFile(const std::string& file)
	{
		Ref<AudioSource> result = Audio::LoadAudioSource(file);
		return result;
	}
}