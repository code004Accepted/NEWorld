#pragma once
#define NEWORLD_USE_WINAPI
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

#ifdef _MSC_VER
#include <filesystem>
namespace filesystem = std::experimental::filesystem;
#elif defined(__APPLE__)
#include <boost/filesystem>
namespace filesystem = boost::filesystem;
#else
#include <filesystem>
namespace filesystem = std::filesystem;
#endif
