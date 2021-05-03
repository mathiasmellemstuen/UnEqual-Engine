#include "../graphics/mesh.h"
#include <vector>
#include <glm/vec3.hpp>

#include "../sharedlib.h"

Mesh DLLEXPORT icosahedron(); 
Mesh DLLEXPORT sphere(int passes);
Mesh DLLEXPORT calculateIcosahedronRounding(Mesh from);
