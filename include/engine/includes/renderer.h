#pragma once

//#define OSX
#define WINDOWS

#include "engine/includes/utils.h"

#define GLEW_STATIC
#ifdef WINDOWS
#include <GL/glew.h>
#endif
#include <SFML/OpenGL.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "engine/renderer/GLInterface.h"
