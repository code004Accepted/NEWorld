#pragma once
//Types/constants define
#include <cstdint>
#include <thread>
#include <mutex>
typedef unsigned char blockprop;
typedef unsigned char Brightness;
typedef unsigned int TextureID;
typedef unsigned short Block;
typedef unsigned short item;
typedef unsigned int VBOID;
typedef int vtxCount;
typedef int SkinID;
typedef uint64_t ChunkID;
typedef unsigned int onlineid;
typedef std::mutex* Mutex_t;
typedef std::thread* Thread_t;
typedef unsigned int(*ThreadFunc_t)(void* param);
#define ThreadFunc unsigned int