#pragma once
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include <qlibc/qlibc.h>

////////////////////
// General Input Functions
////////////////////
/**
 * @brief Initializes input callbacks.
 **/
void v_input_init(GLFWwindow* window);

/**
 * @brief input destructor
 * */
void v_input_destroy();

////////////////////
// Input Data
////////////////////

/**
 * Represents a 'real' input emitted from callbacks.
 * */
typedef struct v_input_s {
    int key; // the keycode of the defined input
    enum input_mode {INPUT_BUTTON_KEY, INPUT_BUTTON_MOUSE} mode;

    int state; // holds whether a button is pressed, held, or released
    int err; // contains error messages
} v_input_s;

/**
 * Represents a predefined set of rules to handle input
*/
typedef struct v_button_input_desc_s {
    int key;
    enum input_mode  mode; // What device is this input coming from?
    bool (*func)(v_input_s input,void* ctx); // the callback when the key is pressed
} v_button_input_desc_s;

/**
 * Represents the current mouse position and state.
 **/
typedef struct v_mouse_input_s {
    double posX, posY;
    double dX, dY;
} v_mouse_input_s;

/**
 * @brief Get mouse data.
 **/
v_mouse_input_s v_input_get_mouse();

////////////////////
// Input Component
////////////////////
/**
 * the component struct which connects an input controller to its target
 * actor is the parent the component is connected to.
 * controller is anything that calls input_component_run()
 **/
typedef struct v_input_component_s{
    void* actor;
    void* controller;
    qvector_t* commands;
} v_input_component_s;

/**
 * @brief initialize a new input component and connect it to its game object
 * @param actor the parent object
 */
v_input_component_s* v_input_component_init(void* actor);

/**
 * Connect the input component to its new controller
 * If a controller is already connected, switch it to the new controller
 **/
void v_input_component_connect(v_input_component_s*,void* controller);

/**
 * @brief adds a key-action relationship to the component
 * making the component run functions from a key press on the actor
 */
void v_input_component_register(v_input_component_s*, v_button_input_desc_s*);

/**
 * @brief runs the function in the component associated with the given input
 * @param v_input_s the key data of the component
 * @return whether or not the function should handle
 */
bool v_input_component_run(v_input_component_s*,v_input_s);

/**
 * @brief component destructor
 * @note This doesnt deallocate the actor or controller, those should be freed elsewhere.
 **/
void v_input_component_destroy(v_input_component_s*);


////////////////////
// Input Event Subject
////////////////////

/**
 * The input system works by having a private event loop which iterates over
 * an array of subjects.
 *
 * The subject holds an input component which holds all the callbacks.
 * The subject also holds a list of keys that the callbacks ask for.
 *
 * If an input event matches any of the keys in the list,
 * then input_component_run() is called.
 **/
typedef struct v_input_subject_s{
    qvector_t* keys;
    v_input_component_s* component;
} v_input_subject_s;

/**
 * @brief Create a new subject
 **/
v_input_subject_s *v_input_subject_init();

/**
 * @brief connect an input component to the subject and add it to the event loop
 **/
void v_input_subject_submit(v_input_subject_s*,v_input_component_s*);

/**
 * @brief add a new key the subject should look for
 **/
void v_input_subject_watch_key(v_input_subject_s*, int*);

/**
 * @brief clear the key watch list, useful for rebinding keys mid-game
 **/
void v_input_subject_clear_watchlist(v_input_subject_s*);

/**
 * @brief subject destructor
 **/
void v_input_subject_destroy(v_input_subject_s* subject);
