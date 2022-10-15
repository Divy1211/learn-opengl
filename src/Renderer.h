#pragma once

#ifdef PROD
    #define Assert(x);
    #define GLCALL(x) x;
#else
    #define ASSERT(x) if ((!x)) __debugbreak();
    #define GLCALL(x) clearGlErrors(); x; checkGlErrors(#x, __FILE__, __LINE__);
#endif

void errorCallback(int error, const char* description);

void clearGlErrors();

void checkGlErrors(const char* func, const char* file, int line);