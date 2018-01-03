#pragma once
#define NEWORLD_USE_WINAPI
#define NERDMODE1
#define _USE_MATH_DEFINES

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <cassert>
#include <math.h>
#include <memory>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

//GLFW
#define GLFW_DLL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
