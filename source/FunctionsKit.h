#pragma once
#include "StdInclude.h"
#include "Typedefs.h"
#include <chrono>
extern double stretch;

//常用函数
std::vector<std::string> split(const std::string& str, const std::string& pattern);

inline void UITrans(double x, double y) {
    glTranslated(x*stretch, y*stretch, 0);
}
inline void UITrans(int x, int y) {
    glTranslated((static_cast<double>(x))*stretch, (static_cast<double>(y))*stretch, 0);
}
inline void UIVertex(double x, double y) {
    glVertex2d(x*stretch, y*stretch);
}
inline void UIVertex(int x, int y) {
    glVertex2i(static_cast<int>(x*stretch), static_cast<int>(y*stretch));
}

extern unsigned int g_seed;
inline int fastRand() {
    g_seed = (214013 * g_seed + 2531011);
    return (g_seed >> 16) & 0x7FFF;
}
inline void fastSrand(int seed) { g_seed = seed; }
std::vector<std::string> split(const std::string& str, const std::string& pattern);
inline double rnd() { return (double)fastRand() / (RAND_MAX + 1); }
inline int RoundInt(double d) { return int(floor(d + 0.5)); }

inline std::string itos(int i) {
    std::stringstream ss;
    ss << i;
    return ss.str();
}

inline bool beginWith(const std::string& str, const std::string& begin) {
    if (str.size() < begin.size()) return false;
    return str.substr(0, begin.size()) == begin;
}

inline void DebugWarning(const std::string& msg) {
    printf("[Debug][Warning]%s\n", msg.c_str());
}

inline void DebugError(const std::string& msg) {
    printf("[Debug][Error]%s\n", msg.c_str());
}

template<class T> 
inline void conv(const std::string& str, T& ret) {
    std::stringstream s(str);
    s >> ret;
}

template<class T> 
inline T clamp(T x, T min, T max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline double timer() {
    auto duri = std::chrono::steady_clock::now().time_since_epoch();
    return static_cast<double>(duri.count()) / decltype(duri)::period::den;
}
#ifdef NEWORLD_USE_WINAPI
inline unsigned int MByteToWChar(wchar_t* dst, const char* src, unsigned int n) {
    int res = MultiByteToWideChar(CP_UTF8, 0, src, n, dst, n);
    return res;
}
inline unsigned int WCharToMByte(char* dst, const wchar_t* src, unsigned int n) {
    return WideCharToMultiByte(CP_UTF8, 0, src, n, dst, n * 2, nullptr, nullptr);
}
#else
inline unsigned int MByteToWChar(wchar_t* dst, const char* src, unsigned int n) { size_t res; mbstowcs_s(&res, dst, n, src, _TRUNCATE); return res; }
#endif
inline Mutex_t MutexCreate() { return new std::mutex; }
inline void MutexDestroy(Mutex_t _hMutex) { delete _hMutex; }
inline void MutexLock(Mutex_t _hMutex) { _hMutex->lock(); }
inline void MutexUnlock(Mutex_t _hMutex) { _hMutex->unlock(); }
inline Thread_t ThreadCreate(ThreadFunc_t func, void* param) { return new std::thread(func, param); }
inline void ThreadWait(Thread_t _hThread) { _hThread->join(); }
inline void ThreadDestroy(Thread_t _hThread) { delete _hThread; }
inline unsigned int wstrlen(const wchar_t* wstr) { return wcslen(wstr); }
inline int Distancen(int ix, int iy, int iz, int x, int y, int z)//计算距离的平方
{
    return (ix - x)*(ix - x) + (iy - y)*(iy - y) + (iz - z)*(iz - z);
}