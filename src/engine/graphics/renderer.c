#include "engine/graphics/renderer.h"
#include "engine/util/asset.h"

v_rendercomponent_s* v_rendercomponent_create(v_renderer_s* renderer, v_rendercomponent_desc_s* desc){
    v_rendercomponent_s *component = malloc(sizeof(v_rendercomponent_s));

    component->bind = desc->bind;
    component->pip = sg_make_pipeline(desc->pip_desc);
    component->draw = desc->draw;
    component->actor = desc->actor;
    component->renderer = renderer;

    qvector_addlast(renderer->rendercomponents, component);

    return component;
}

v_renderer_s* renderer_init(){
    VGE_CORE_LOG_INFO("Initializing renderer...");
    v_renderer_s* renderer = malloc(sizeof(v_renderer_s));
    renderer->rendercomponents = qvector(0, sizeof(v_rendercomponent_s),QVECTOR_THREADSAFE);


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    renderer->window = glfwCreateWindow(640, 480, "Sokol Triangle GLFW", 0, 0);
    glfwMakeContextCurrent(renderer->window);
    glfwSwapInterval(1);

    sg_setup(&(sg_desc){
            .logger.func = slog_func
        });

    simgui_setup(&(simgui_desc_t){
        .logger = slog_func
    });

    // asset preloading
    v_assetmanager_load("assets/shaders/sprite_v.glsl");
    VGE_LOG_INFO("Vertex shader loaded:{}",v_assetmanager_get("assets/shaders/sprite_v.glsl")->filepath);
    v_assetmanager_load("assets/shaders/sprite_f.glsl");
    VGE_LOG_INFO("Fragment shader loaded:{}",v_assetmanager_get("assets/shaders/sprite_f.glsl")->filepath);


    return renderer;
}

void renderer_delete(v_renderer_s* renderer){

    glfwTerminate();
    free(renderer);
}

void renderer_update(v_renderer_s* renderer){
    int cur_width, cur_height;
    glfwGetFramebufferSize(
        renderer->window,
        &cur_width,
        &cur_height);
    const sg_pass_action *pass_action = renderer->renderpass;
    sg_begin_default_pass(pass_action, cur_width, cur_height);
    for(int i = 0; i < qvector_size(renderer->rendercomponents); i++){
        v_rendercomponent_s *component = qvector_getat(renderer->rendercomponents, i, false);
        component->draw(component,component->actor);
    }
    sg_end_pass();
    sg_commit();
    glfwSwapBuffers(renderer->window);
    glfwPollEvents();
}

void renderer_prepare(v_renderer_s* renderer,sg_pass pass){

}

void renderer_set_camera(v_renderer_s* renderer, struct v_ortho_camera_s camera){

}

void renderer_push_camera(v_renderer_s*);
void renderer_pop_camera(v_renderer_s*);
void renderer_set_view_proj(v_renderer_s*);
void renderer_use_shader(v_renderer_s*);
