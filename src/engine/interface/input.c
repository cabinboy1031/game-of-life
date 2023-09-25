#include <engine/interface/input.h>
#include <raylib.h>
#include <stdio.h>

bool input_run(key_input_s* input){
    switch(input->mode){
        case INPUT_KEY:
            input_key_run(input);
            break;
        case INPUT_MOUSE:
            input_mouse_run(input);
            break;
        default:
            printf("Sorry, this input mode has not been implemented yet :^)");  
    }
}

bool input_key_run(key_input_s* input){
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
}

bool input_mouse_run(key_input_s* input){
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
}