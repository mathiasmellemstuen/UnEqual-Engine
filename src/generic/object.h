#include "../graphics/renderer.h"
#include "../input/input.h"
#include "../sharedlib.h"

class DLLEXPORT Object {
    public:
        void setup(Renderer* renderer, Input* input);
    private: 
        Renderer* renderer; 
        Input* input; 
};