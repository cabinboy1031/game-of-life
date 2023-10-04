#pragma once
#include <stdbool.h>

/**
 * Represents a predefined set of rules for an input
*/
typedef struct key_input_s {
    int key; // the keycode of the defined input
    bool ignore_hold;
    enum input_mode {INPUT_KEY, INPUT_MOUSE} mode; // Descriptor for the which run function to use when detecting input
    
    bool pressed; // will always default to false, true if key is pressed.
    int err; // contains error messages
} key_input_s;

/**
 * @brief generic command for input events
 * requires input_mode to be defined
 *
 * @return true if the function should run
 */
bool input_run(key_input_s*);

/** key_input_s -> bool
 * returns whether or not a function should run
 */
bool input_key_run(key_input_s*);

/** key_input_s -> bool
 * returns whether or not a function should run
 */
bool input_mouse_run(key_input_s*);
