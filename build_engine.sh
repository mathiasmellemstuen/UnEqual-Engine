#!/bin/sh
ALL_CPP=$(find "$(cd src/; pwd)" | grep .cpp)
g++ -std=c++17 -c -fPIC -DGLAD_GLAPI_EXPORT -DGLAPI_EXPORT_BUILD -I./include glad.c $ALL_CPP -Wl,--copy-dt-needed-entries -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -L./ -lglfw -lfreetype
g++ -shared -o libUnEqualEngine.so *.o -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -L./ -lglfw -lfreetype 