#include "input.h"
#include "../log/log.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <glm/vec2.hpp>
#include <vector>
#include <map>

void Input::addAnalogListener(int analogTrigger, std::function<void(float value)> listener) {

    for(std::map<int,std::function<void(float value)>>::iterator it = analogListeners.begin(); it != analogListeners.end(); ++it) {
        if((it->second)* == listener*)
            
    }
};
void Input::addDigitalListener(int digitalButton, std::function<void(float value)> listener) {

};
void Input::removeAnalogListener(std::function<void(float value)> listener) {

};
void Input::removeDigitalListener(std::function<void(float value)> listener) {

};
void Input::update() {
    int present = glfwJoystickPresent(GLFW_JOYSTICK_2);
    if(present == 1) {

        int axisCount; 
        const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &axisCount);

        for(int i = 0; i < axisCount; i++) {

            float value = abs(axes[i]) > analogValueCutoffValue ? axes[0] - analogValueCutoffValue : 0.0f;
            for(std::map<int,std::function<void(float value)>>::iterator it = analogListeners.begin(); it != analogListeners.end(); ++it) {
                if(it->first == i) {
                    it->second(value);
                }
            }
        }

        int buttonCount; 
        buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_2, &buttonCount);
    }
};