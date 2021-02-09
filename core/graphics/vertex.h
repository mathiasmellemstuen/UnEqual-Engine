#ifndef VERTEX
#define VERTEX

#include "../MathUtilities/DataStructure/vector.h"

struct Vertex {
    MathUtilities::DataStructure::Vector<3, int> position;
    MathUtilities::DataStructure::Vector<3, int> normal; 
    MathUtilities::DataStructure::Vector<2, int> textureCoordinates;
};

#endif