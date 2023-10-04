#pragma once
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include <qlibc/qlibc.h>

/**
 * Represents a predefined set of rules for an input
*/
typedef struct button_input_desc_s {
    int key;
    bool ignore_hold;
    enum input_mode {INPUT_BUTTON_KEY, INPUT_BUTTON_MOUSE} mode; // Descriptor for the which run function to use when detecting input
    void (*func)(void* ctx);
} button_input_desc_s;

/**
 * Represents a 'real' input emitted from callbacks.
 * */
typedef struct button_input_s {
    int key; // the keycode of the defined input
    enum input_mode mode;
    bool ignore_hold;

    int pressed; // shows if a button is pressed, held, or released
    int err; // contains error messages
} button_input_s;

/**
 * Represents the current mouse position and state.
 **/
typedef struct mouse_input_s {
    int posX, posY;
    int dX, dY;
} mouse_input_s;

/**
 * Initializes input callbacks.
 **/
void v_input_init(GLFWwindow* window);

/**
 * Resets input state to null.
 * */
void v_input_destroy();

/**
 * Submit inputs with their associated function.
 **/
void v_input_submit(button_input_desc_s);

/**
 * Get mouse data.
 **/
mouse_input_s v_input_get_mouse();

/**
 * @brief generic command for input events
 * requires input_mode to be defined
 *
 * @return true if the function should run
 */
bool input_run(button_input_s*);

/** key_input_s -> bool
 * returns whether or not a function should run
 */
bool input_key_run(button_input_s*);

/** key_input_s -> bool
 * returns whether or not a function should run
 */
bool input_mouse_run(button_input_s*);
