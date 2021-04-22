#include "input.h"
#include <steam/steam_api.h>
#include "../log/log.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
void Input::setup() {

//    if(SteamAPI_Init()) {
//    
//        log(SUCCESS, "Steam API started.");
//
//        if(SteamInput()->Init()) {
//
//            log(SUCCESS, "Successfully initiated steamInput!");
//            const char *name = SteamFriends()->GetPersonaName();
//            log(INFO, "Player name: " + (std::string)name); 
//
//            int xInputSlot = 0; 
//             inputHandle = SteamInput()->GetControllerForGamepadIndex(xInputSlot);
//

//            ESteamInputType inputType = SteamInput()->GetInputTypeForHandle(inputHandle);
//                
//            switch(inputType) {
//                case k_ESteamInputType_Unknown:
//                    log(SUCCESS, "Unknown controller detected."); 
//                    break; 
//                case k_ESteamInputType_SteamController:
//                    log(SUCCESS, "SteamController detected."); 
//                    break; 
//                case k_ESteamInputType_XBox360Controller:
//                    log(SUCCESS, "X-Box 360 controller detected."); 
//                    break; 
//                case k_ESteamInputType_XBoxOneController:
//                    log(SUCCESS, "X-Box One controller detected.");
//                    break; 
//                case k_ESteamInputType_GenericGamepad:
//                    log(SUCCESS, "GenericGamepad detected!"); 
//                    break; 
//                case k_ESteamInputType_SwitchProController:
//                    log(SUCCESS, "Switch procontroller detected!"); 
//                default:
//                    log(SUCCESS, "A controller is detected."); 
//                    break; 
//            }
//
//        } else {
//            log(ERROR, "Failed to init Steam Input."); 
//        }
//    }
//    else {
//
//        log(ERROR, "Failed to initialize steam api."); 
//    }
};

void Input::update() {


    int present = glfwJoystickPresent(GLFW_JOYSTICK_2);

    if(present == 1) {

        int axisCount; 
        const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &axisCount);
        leftStick.x = abs(axes[0]) > 0.1f ? axes[0] : 0.0f; 
        leftStick.y = abs(axes[1]) > 0.1f ? axes[1] : 0.0f; 
        rightStick.x = abs(axes[2]) > 0.1f ? axes[2] : 0.0f;  
        rightStick.y = abs(axes[3]) > 0.1f ? axes[3] : 0.0f; 
    }
};