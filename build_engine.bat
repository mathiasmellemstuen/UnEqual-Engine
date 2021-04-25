@echo off
cd src/
set objs=
for /R %%f in (*.cpp) do call set objs=%%objs%% %%f
cd ..
g++ -std=c++17 -c -DBUILD_SHARED_LIB -DGLAD_GLAPI_EXPORT -DGLAD_GLAPI_EXPORT_BUILD -I./include glad.c %objs% -L./lib -lglfw3dll -lfreetype
g++ -shared -o UnEqualEngine.dll *.o -Wl,--out-implib,UnEqualEngine.a -L./lib -lglfw3dll -lfreetype