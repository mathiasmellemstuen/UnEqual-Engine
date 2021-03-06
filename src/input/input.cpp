#include "input.h"
#include "../log/log.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <glm/vec2.hpp>
#include <vector>
#include <map>
#include <algorithm>

void Input::setJoystickDevice(int device) {
    joystickDevice = device - 1;
    log(WARNING, "SET_JOYSTICK_DEVICE -- This feature is not fully developed."); 
}
void Input::addAnalogListener(std::function<void(float* values, int maxCount)> listener) {
    analogListeners.push_back(listener); 
};
void Input::addDigitalListener(std::function<void(bool* values, int maxCount)> listener) {
    digitalListeners.push_back(listener); 
};

void Input::removeAnalogListener(std::function<void(bool* value, int maxCount)> listener) {

};
void Input::removeDigitalListener(std::function<void(bool* value, int maxCount)> listener) {

};
void Input::update() {
    int present = glfwJoystickPresent(joystickDevice);
    if(present == 1) {

        int axisCount; 
        const float *axes = glfwGetJoystickAxes(joystickDevice, &axisCount);

        float values[axisCount]; 

        for(int i = 0; i < axisCount; i++) {
            values[i] = abs(axes[i]) > analogValueCutoffValue ? axes[i] - analogValueCutoffValue : 0.0f; 
        }

        for(int i = 0; i < analogListeners.size(); i++) {
            analogListeners.at(i)(values, axisCount); 
        }

        int buttonCount; 
        const unsigned char* buttons = glfwGetJoystickButtons(joystickDevice, &buttonCount);

        bool buttonValues[buttonCount]; 

        for(int i = 0; i < buttonCount; i++) {
            buttonValues[i] = buttons[i] == GLFW_PRESS ? true : false; 
        }

        for(int i = 0; i < digitalListeners.size(); i++) {
            digitalListeners.at(i)(buttonValues, buttonCount); 
        }
    }
};