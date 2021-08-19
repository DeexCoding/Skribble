#pragma once

//The engine API

//Core
#include "Skribble/Core/Application.h"
#include "Skribble/Core/Layer.h"
#include "Skribble/Core/Debug.h"
#include "Skribble/Core/Random.h"

//Events
#include "Skribble/Events/Event.h"
#include "Skribble/Events/ApplicationEvent.h"
#include "Skribble/Events/KeyEvent.h"
#include "Skribble/Events/MouseEvent.h"

//Input
#include "Skribble/Core/Input.h"
#include "Skribble/Core/Keycode.h"
#include "Skribble/Core/Mousecode.h"

//Debug
#include "Skribble/Debug/Instrumentor.h"

//Rendering
#include "Skribble/Render/Renderer.h"
#include "Skribble/Render/Batch2D.h"

#include "Skribble/Render/VertexBuffer.h"
#include "Skribble/Render/IndexBuffer.h"
#include "Skribble/Render/VertexArray.h"
#include "Skribble/Render/Shader.h"
#include "Skribble/Render/Texture.h"
#include "Skribble/Render/Font.h"

#include "Skribble/Render/OrthographicCamera.h"
#include "Skribble/OrthographicCameraController.h"

//Audio
#include "Skribble/Audio/Audio.h"

//Maths
#include "Skribble/Maths/Color.h"
#include "Skribble/Maths/Vector.h"

//Other
#include "Skribble/Core/Time.h"