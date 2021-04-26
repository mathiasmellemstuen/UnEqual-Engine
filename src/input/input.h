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
        void addAnalogListener(std::function<void(float* value, int maxCount)> listener);
        void addDigitalListener(std::function<void(bool* value, int maxCount)> listener);
        void removeAnalogListener(std::function<void(bool* value, int maxCount)> listener);
        void removeDigitalListener(std::function<void(bool* value, int maxCount)> listener);
    private:
        const float analogValueCutoffValue = 0.15f;
        std::vector<std::function<void(float* value, int maxCount)>> analogListeners; 
        std::vector<std::function<void(bool* value, int maxCount)>> digitalListeners; 
};
#endif