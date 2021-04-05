#pragma once

// -- Core
#include "Aquarius/Core/Utility.h"
#include "Aquarius/Core/Application.h"
#include "Aquarius/Core/Assert.h"
#include "Aquarius/Core/Input.h"
#include "Aquarius/Core/Layer.h"
#include "Aquarius/Core/Log.h"
#include "Aquarius/Core/Window.h"

// -- Renderer
#include "Aquarius/Renderer/IndexBuffer.h"
#include "Aquarius/Renderer/OrthographicCamera.h"
#include "Aquarius/Renderer/QuadTexCoords.h"
#include "Aquarius/Renderer/Renderer.h"
#include "Aquarius/Renderer/Shader.h"
#include "Aquarius/Renderer/SpriteSheet.h"
#include "Aquarius/Renderer/BitmapFont.h"
#include "Aquarius/Renderer/Texture.h"
#include "Aquarius/Renderer/VertexBuffer.h"
#include "Aquarius/Renderer/VertexArray.h"

// -- Events
#include "Aquarius/Events/Event.h"
#include "Aquarius/Events/EventHandler.h"
#include "Aquarius/Events/KeyboardEvent.h"
#include "Aquarius/Events/MouseEvent.h"
#include "Aquarius/Events/WindowEvent.h"

#include <easylogging++.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <stb_image.h>
