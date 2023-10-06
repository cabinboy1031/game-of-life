#include "engine/interface/input.h"
#include "engine/util/log.h"
#include <stdio.h>

/**
 * The input system struct, all input should go through this
 **/
struct p_input_event_system_s{
    qvector_t* subjects;
    v_mouse_input_s mouse;
} input_system;

// GLFW callback predefinitions
void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void glfw_cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

////////////////////
// public system functions
////////////////////
void v_input_init(GLFWwindow* window){
    qvector_t* subjects = qvector(0, sizeof(v_input_component_s), QVECTOR_THREADSAFE | QVECTOR_RESIZE_DOUBLE);

    input_system.subjects = subjects;
    input_system.mouse = (v_mouse_input_s){0.0f};

    glfwSetMouseButtonCallback(window, glfw_mouse_button_callback);
    glfwSetKeyCallback(window, glfw_key_callback);
    glfwSetCursorPosCallback(window, glfw_cursor_position_callback);

    if(glfwRawMouseMotionSupported()){
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
}

void v_input_destroy(){
    qvector_free(input_system.subjects);
}

v_mouse_input_s v_input_get_mouse(){
    v_mouse_input_s mouse = input_system.mouse;
    return (v_mouse_input_s){mouse.posX, mouse.posY, mouse.dX, mouse.dY};
}

////////////////////
// private system functions
////////////////////
/**
 * Used by input callbacks to run input calls found in the registry
 **/
void p_input_submit(v_input_s input){
    if(input.state == GLFW_PRESS){
        VGE_CORE_LOG_INFO("Button pressed: %d",input.key);
    }
    if(input.state == GLFW_REPEAT){
        VGE_CORE_LOG_INFO("Button held: %d",input.key);
    }
    if(input.state == GLFW_RELEASE){
        VGE_CORE_LOG_INFO("Button released: %d",input.key);
    }

    for(int i = 0; i < qvector_size(input_system.subjects); i++){
        v_input_subject_s* subject = qvector_getat(
            input_system.subjects,
            i,
            false);
        bool handled = false;

        for(int i = 0; i < qvector_size(subject->keys); i++){
            int *key = qvector_getat(subject->keys, i, false);
            if(*key == input.key){
                handled = v_input_component_run(subject->component,input);
            }
        }
        // To prevent other subjects from taking this input
        // (if one has already handled it),
        // we simply drop the input if a run function returns true
        // we will let individual functions decide whether a key is handled or not

        // NOTE: this means the order of subjects matters,
        // it might be a good idea to have a priority for input observers
        if(handled == true) { break; }
    }

    // If no subject is found, just drop the input

}

////////////////////
// public input component functions
////////////////////

v_input_component_s* v_input_component_init(void* actor){
    v_input_component_s* input_component = malloc(sizeof(input_component));
    // actors and controllers will be allocated somewhere else
    input_component->actor = actor;

    input_component->commands = qvector(
        0,
        sizeof(v_button_input_desc_s),
        QVECTOR_THREADSAFE|QVECTOR_RESIZE_EXACT);

    return input_component;
}

void v_input_component_connect(v_input_component_s* input,void* controller){
    if(input->controller != 0){
        // FIXME: if controller has a pointer to the component(it probably will),
        // then the controller will need to either be deallocated
        // or have its pointer set to null as well.
        // Given that the controller is *by design* a different struct,
        // we cant really use the same function for this
        //
        // A good fix is probably to make an intermediate controller_interface with the
        // needed connect() and disconnect() functions
        //
        // ... eh. ill do that later,
        // just gotta remember to do that when i wanna rebind keys
        input->controller = 0;
    }

    input->controller = controller;
}

void v_input_component_register(v_input_component_s* component, v_button_input_desc_s* desc){
    qvector_addlast(component->commands, desc);

    v_input_subject_watch_key(component->controller, &desc->key);
}

bool v_input_component_run(v_input_component_s* component,v_input_s input){
    bool handled = false;
    for(int i = 0; i < qvector_size(component->commands); i++){
        v_button_input_desc_s *button = qvector_getat(component->commands, i, false);
        if(button->key == input.key){
            handled = button->func(input,component->actor);
        }
    }
    return handled;
}

void v_input_component_destroy(v_input_component_s* input){
    input->actor = 0;
    input->controller = 0;
    qvector_free(input->commands);
    free(input);
}

////////////////////
// public input subject functions
////////////////////
v_input_subject_s *v_input_subject_init(){
    v_input_subject_s* subject = malloc(sizeof(v_input_subject_s));
    subject->keys = qvector(0,sizeof(int),QVECTOR_THREADSAFE);

    return subject;
}

void v_input_subject_submit(v_input_subject_s* subject,v_input_component_s* component){
    subject->component = component;

    for(int i = 0; i < qvector_size(component->commands); i++){
        int *key = qvector_getat(component->commands, i, false);
        v_input_subject_watch_key(subject,key);
    }

    qvector_addlast(input_system.subjects, subject);
}

void v_input_subject_watch_key(v_input_subject_s* subject, int *key){
    qvector_addlast(subject->keys, key);
}

void v_input_subject_clear_watchlist(v_input_subject_s* subject){
    qvector_clear(subject->keys);
}

void v_input_subject_destroy(v_input_subject_s* subject){
    qvector_free(subject->keys);
    subject->component = 0;
    free(subject);
}

////////////////////
// GLFW Callbacks
////////////////////
void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    v_input_s input = (v_input_s){
        .key = key,
        .state = action,
        .mode = INPUT_BUTTON_KEY,};

    p_input_submit(input);
}

void glfw_mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    v_input_s input = (v_input_s){
        .key = button,
        .state = action,
        .mode = INPUT_BUTTON_MOUSE,};

    p_input_submit(input);

}

void glfw_cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    double newdX = input_system.mouse.posX - xpos;
    double newdY = input_system.mouse.posY - ypos;
    input_system.mouse = (v_mouse_input_s){
        .posX = xpos,
        .posY = ypos,
        .dX = newdX,
        .dY = newdY,
    };
}
