#include "engine/interface/input.h"
#include "engine/util/log.h"
#include <stdio.h>

struct v_input_reg_s {
    button_input_desc_s key_buttons[GLFW_KEY_LAST + 1];
    button_input_desc_s mouse_buttons[GLFW_MOUSE_BUTTON_LAST + 1];
    mouse_input_s mouse;
} input_registry;

/**
 * Used by input callbacks to run input calls found in the registry
 **/
void v_input_run(button_input_s input){
    if(input.pressed == GLFW_PRESS){
        VGE_CORE_LOG_INFO("Button pressed: %d",input.key);
    }
    if(input.pressed == GLFW_REPEAT){
        VGE_CORE_LOG_INFO("Button held: %d",input.key);
    }
    if(input.pressed == GLFW_RELEASE){
        VGE_CORE_LOG_INFO("Button released: %d",input.key);
    }
    size_t size;
    button_input_desc_s button;

    if(input.mode == INPUT_BUTTON_KEY){
        button = input_registry.key_buttons[input.key];

    }
    if(input.mode == INPUT_BUTTON_MOUSE){
        button = input_registry.mouse_buttons[input.key];
    }

    if(button.func == 0){
        return;
    }

    if(button.ignore_hold && input.pressed){
        //TODO: Make an event using this func instead of running it immediately
        button.func(0);
    }
}

//**
// GLFW Callbacks
//*/
//
void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    button_input_s input = (button_input_s){
        .key = key,
        .pressed = action,
        .mode = INPUT_BUTTON_KEY,};

    v_input_run(input);
}

void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    button_input_s input = (button_input_s){
        .key = button,
        .pressed = action,
        .mode = INPUT_BUTTON_MOUSE,};

    v_input_run(input);

}

void glfw_cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    double newdX = input_registry.mouse.posX - xpos;
    double newdY = input_registry.mouse.posY - ypos;
    input_registry.mouse = (mouse_input_s){
        .posX = xpos,
        .posY = ypos,
        .dX = newdX,
        .dY = newdY,
    };
}

/**
 * API functions
 **/

void v_input_init(GLFWwindow* window){
    for(int i = 0; i < GLFW_KEY_LAST; i++){
        input_registry.key_buttons[i] = (button_input_desc_s){.key = GLFW_KEY_UNKNOWN, .func = 0};
    }
    for(int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++){
        input_registry.mouse_buttons[i] = (button_input_desc_s){.key = -1, .func = 0};
    }

    glfwSetMouseButtonCallback(window, glfw_mouse_button_callback);
    glfwSetKeyCallback(window, glfw_key_callback);
    glfwSetCursorPosCallback(window, glfw_cursor_position_callback);

    if(glfwRawMouseMotionSupported()){
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
}

void v_input_destroy(){
}

void v_input_submit(button_input_desc_s){

}

bool input_run(button_input_s* input){
    switch(input->mode){
        case INPUT_BUTTON_KEY:
            return input_key_run(input);
            break;
        case INPUT_BUTTON_MOUSE:
            return input_mouse_run(input);
            break;
        default:
            printf("Sorry, this input mode has not been implemented yet :^)");
            return false;
    }
    return false;
}

bool input_key_run(button_input_s* input){
    /**
    if(input->ignore_hold && input->pressed){
        if(IsKeyUp(input->key)){
            input->pressed = false;
        }
        return false;
    }

    if(IsKeyDown(input->key)){
        input->pressed = true;
        return true;
    }
    if(IsKeyUp(input->key)){
        input->pressed = false;
        return false;
    }
    **/
    return false;
}

bool input_mouse_run(button_input_s* input){
    /**
    if(input->ignore_hold && input->pressed){
        if(IsMouseButtonUp(input->key)){
            input->pressed = false;
        }
        return false;
    }

    if(IsMouseButtonDown(input->key)){
        input->pressed = true;
        return true;
    }
    if(IsMouseButtonUp(input->key)){
        input->pressed = false;
        return false;
    }
    */
    return false;
}
