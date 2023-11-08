#pragma once
#include "engine/graphics/renderer.h"
#include "engine/util/asset.h"
#include "cglm/cglm.h"

typedef struct v_sprite_s {
    v_transform_s transform;
    vec4 color;

    struct v_rendercomponent_s* render_component;
} v_sprite_s;

void sprite_draw(v_rendercomponent_s* renderer, void* actor);

v_sprite_s* v_sprite_create(v_renderer_s* renderer){
    v_sprite_s* sprite = malloc(sizeof(v_sprite_s));

    float vertices[] = {
    // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    v_asset_s* vertex = v_assetmanager_get("assets/shaders/sprite_v.glsl");
    v_asset_s* frag = v_assetmanager_get("assets/shaders/sprite_f.glsl");


    sprite = &(v_sprite_s){
        .transform = {
            .translation = 0.0f,
            .rotation = {0.0f},
            .scale = {1.0f},
        },
        .color = {1.0f},
        .render_component = v_rendercomponent_create(
            renderer,
            &(v_rendercomponent_desc_s){
                .bind.vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc){
                    .data = SG_RANGE(vertices),
                    .label = "vertices"
                    }),
                .pip_desc = &(sg_pipeline_desc){
                    .shader = sg_make_shader(&(sg_shader_desc){
                                    .vs.source = vertex->data,
                                    .fs.source = frag->data,
                                }),
                            .layout= {
                                .attrs = {
                                    [0].format = SG_VERTEXFORMAT_FLOAT2,
                                    [1].format = SG_VERTEXFORMAT_FLOAT2,
                                },
                            }
                        },
                .draw = sprite_draw,
        }),
    };

    return sprite;
}

void sprite_draw(v_rendercomponent_s* component, void* actor){
    v_sprite_s* sprite = (v_sprite_s*)actor;

    sg_apply_pipeline(component->pip);
    sg_apply_bindings(&component->bind);
    sg_draw(0,3,1);
}

void v_sprite_delete(v_sprite_s* sprite){
    free(sprite);
}
