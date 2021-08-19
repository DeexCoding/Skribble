#pragma once

#include <iostream>
#include <string>

#include "Skribble/Core/Core.h"

#include <glm/glm.hpp>

namespace Skribble
{
	class AudioListener
	{
	public:
		AudioListener() = default;
		AudioListener(glm::vec3 position, glm::vec3 rotation);
		~AudioListener();

		float GetGain() { return gain; }
		void SetGain(float gain);

		glm::vec3 GetPosition() { return position; }
		void SetPosition(glm::vec3 position);

		glm::vec3 GetRotation() { return rotation; }

		/// <summary>
		/// Very expensive
		/// </summary>
		/// <param name="rotation"></param>
		void SetRotation(glm::vec3 rotation);

	private:
		float gain = 1.0f;
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };

	};

	class AudioSource
	{
	public:
		AudioSource() = default;
		AudioSource(uint32_t handle, bool loaded, float length);
		~AudioSource();
		
		bool IsLoaded() { return loaded; };

		void SetPosition(glm::vec3 position);
		void SetGain(float gain);
		void SetPitch(float pitch);
		void SetSpatial(bool spatial);
		void SetLoop(bool loop);

		std::pair<uint32_t, uint32_t> GetLengthMinutesAndSeconds() const;

		static Ref<AudioSource> LoadFromFile(const std::string& file);

	private:
		

		uint32_t bufferHandle = 0;
		uint32_t sourceHandle = 0;
		bool loaded = false;
		bool spatial = false;

		float totalDuration = 0.0f; //seconds

		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		float gain = 1.0f;
		float pitch = 1.0f;
		bool loop = false;

		friend class Audio;
	};

	class Audio
	{
	public:
		static void Initalize();

		static Ref<AudioSource> LoadAudioSource(const std::string& filepath);
		static void Play(Ref<AudioSource> source);
		static void Stop(Ref<AudioSource> source);

	private:
		static Ref<AudioSource> LoadAudioSourceOgg(const std::string& filename);
		static Ref<AudioSource> LoadAudioSourceMP3(const std::string& filename);
		static Ref<AudioSource> LoadAudioSourceWav(const std::string& filename);
		
	};
}