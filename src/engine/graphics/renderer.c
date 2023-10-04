#include "engine/graphics/renderer.h"


v_renderer_s* v_renderer_init(char* title, int width, int height){
    v_renderer_s* renderer = malloc(sizeof(v_renderer_s));
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    renderer->window = glfwCreateWindow(width, height, title, 0, 0);

    glfwMakeContextCurrent(renderer->window);
    glfwSwapInterval(1);


    return renderer;
}

void v_renderer_delete(v_renderer_s* renderer){
    sg_shutdown();
    glfwTerminate();
    free(renderer);
};

void v_renderer_submit_pipeline(v_renderer_s *renderer,sg_pipeline_desc *desc){
    sg_pipeline pip= sg_make_pipeline(desc);
    qvector_addlast(renderer->pipelines,&pip);
}
