#pragma once
#include <sokol_gfx.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <qlibc/qlibc.h>

typedef struct v_renderer_s {
    GLFWwindow* window;
    qvector_t* pipelines;
    sg_bindings bindings;
    sg_pass_action pass_action;
} v_renderer_s;

v_renderer_s* v_renderer_init(char* title, int width, int height);
void v_renderer_delete(v_renderer_s* renderer);

/**
 * register new shader resources
 **/
void v_renderer_submit_shader(v_renderer_s*,sg_shader_desc*);

/**
 * register new pipeline resources
 **/
void v_renderer_submit_pipeline(v_renderer_s*,sg_pipeline_desc*);

/**
 * register new binding to actually draw the vertex buffer
 **/
void v_renderer_submit_bindings(v_renderer_s*, sg_bindings bind);
