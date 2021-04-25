#ifndef SHARED_LIB
#define SHARED_LIB
#ifdef BUILD_SHARED_LIB
    #define DLLEXPORT __declspec(dllexport)
#else
    #define DLLEXPORT __declspec(dllimport)
#endif
#endif