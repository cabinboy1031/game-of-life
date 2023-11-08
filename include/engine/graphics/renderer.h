#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <engine/core.h>
#include <qlibc/qlibc.h>
#include <engine/util/transform.h>
#include <cimgui.h>
#include <sokol_gfx.h>
#include <cglm/cglm.h>


#define SHADERS_MAX 8

struct v_ortho_camera_s {
    mat4 view_proj;
    vec2 position, min, max;
};

typedef struct v_renderer_s{
    GLFWwindow* window;
    sg_pass_action *renderpass;
    qvector_t *rendercomponents;
} v_renderer_s;

// Render component, attach this to your actors
typedef struct v_rendercomponent_s {
    sg_pipeline pip;
    sg_buffer buffer;
    sg_bindings bind;
    void (*draw)(struct v_rendercomponent_s* component, void* actor);

    v_renderer_s* renderer;
    void* actor;
} v_rendercomponent_s;

typedef struct v_rendercomponent_desc_s {
    sg_bindings bind;
    sg_pipeline_desc *pip_desc;
    void (*draw)(struct v_rendercomponent_s* component, void* actor);

    void* actor;
} v_rendercomponent_desc_s;

v_rendercomponent_s* v_rendercomponent_create(v_renderer_s* renderer, v_rendercomponent_desc_s* desc);


v_renderer_s* renderer_init();
void renderer_delete(v_renderer_s*);
void renderer_update(v_renderer_s*);
void renderer_prepare(v_renderer_s*,sg_pass pass);
void renderer_set_camera(v_renderer_s*, struct v_ortho_camera_s camera);
void renderer_push_camera(v_renderer_s*);
void renderer_pop_camera(v_renderer_s*);
void renderer_set_view_proj(v_renderer_s*);
void renderer_use_shader(v_renderer_s*);
