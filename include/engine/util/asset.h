#pragma once
#include <engine/core.h>

typedef struct v_asset_s {
    void* data;
    size_t data_size;
    const char* filepath;
} v_asset_s;


void v_assetmanager_init();
void v_assetmanager_load(const char* filepath);
v_asset_s* v_assetmanager_get(const char* filepath);
void v_assetmanager_delete();
