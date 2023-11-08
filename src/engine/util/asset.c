#include "engine/util/asset.h"
#include "engine/util/log.h"
#include "sokol_log.h"
#include "qlibc/qlibc.h"
#define SOKOL_FETCH_IMPL
#include "sokol_fetch.h"

#define MAX_FILE_SIZE (1024*1024)
static uint8_t buffer[MAX_FILE_SIZE];

struct {
    qhashtbl_t *assets;
} asset_manager;

static void assetmanager_callback(const sfetch_response_t* response){
    if(response->fetched){
        const void* ptr = response->data.ptr;
        size_t num_bytes = response->data.size;

        v_asset_s asset = (v_asset_s){
        .data = (char*)ptr,
        .data_size = num_bytes,
        .filepath = response->path,
        };

        qhashtbl_put(asset_manager.assets,
                     response->path,
                     ptr,
                     sizeof(v_asset_s));
    }

    if(response->finished){

        if(response->failed){
            if(response->error_code == SFETCH_ERROR_FILE_NOT_FOUND){
                VGE_CORE_LOG_ERROR("File not found: {}", response->path);
            }
        }
    }
}

void v_assetmanager_init(){
    asset_manager.assets = qhashtbl(
        0,
        QHASHTBL_THREADSAFE);

    sfetch_setup(&(sfetch_desc_t){
            .logger.func = slog_func,
        });
}

void v_assetmanager_load(const char* filepath){
    sfetch_send(&(sfetch_request_t){
            .path = filepath,
            .callback = assetmanager_callback,
            .buffer = buffer,
        });
}

v_asset_s* v_assetmanager_get(const char* filepath){
    size_t size = sizeof(v_asset_s);
    v_asset_s* asset;
    if(qhashtbl_get(asset_manager.assets, filepath, &size, false)){
        v_assetmanager_load(filepath);
        return qhashtbl_get(asset_manager.assets, filepath, &size, false);
    }

    return qhashtbl_get(asset_manager.assets, filepath, &size, false);
}

void v_assetmanager_delete(){
    qhashtbl_free(asset_manager.assets);
}
