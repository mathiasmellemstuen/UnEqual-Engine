#include "../graphics/renderer.h"
#include "../input/input.h"
class Object {
    public:
        void setup(Renderer* renderer, Input* input);
    private: 
        Renderer* renderer; 
        Input* input; 
};