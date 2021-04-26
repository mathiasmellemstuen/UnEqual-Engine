#ifndef SHARED_LIB
#define SHARED_LIB
    #if defined(__linux__)
        #define DLLEXPORT 
    #else
        #ifdef BUILD_SHARED_LIB
            #define DLLEXPORT __declspec(dllexport)
        #else
            #define DLLEXPORT __declspec(dllimport)
        #endif
    #endif
#endif