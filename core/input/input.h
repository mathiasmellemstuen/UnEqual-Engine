#ifndef INPUT
#define INPUT

#include <string>
#include <steam/steam_api.h>

struct AnalogValuePair {
    float x; 
    float y; 
};

class Input {
    public:
        AnalogValuePair leftStick; 
        AnalogValuePair rightStick;
        void setup();
        void update(); 
};
#endif