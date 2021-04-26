#ifndef INPUT
#define INPUT

#include <string>
#include <glm/vec2.hpp>
#include <vector>
#include <functional>
#include <map>

#include "../sharedlib.h"

class DLLEXPORT Input {
    public:
        void update();
    private:
        const float analogValueCutoffValue = 0.15f;
        const unsigned char* buttons;
        std::map<int, std::function<void(float value)>> analogListeners; 
        std::map<int, std::function<void(bool value)>> digitalListeners;
        void addAnalogListener(int analogTrigger, std::function<void(float value)> listener);
        void addDigitalListener(int digitalButton, std::function<void(float value)> listener);
        void removeAnalogListener(std::function<void(float value)> listener);
        void removeDigitalListener(std::function<void(float value)> listener);
};
#endif