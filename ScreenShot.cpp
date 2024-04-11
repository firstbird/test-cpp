#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <wayland-client.h>
#include <wayland-egl.h>
#include <Bitmap.h>
// #include "BitmapNode.h"
// #include "CafBitmap.h"
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include "ScreenShot.hpp"

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include "log.hpp"
#define LOG_TAG "ScreenCapture"

using namespace yunos::gui;
// using namespace v8;

#define DEF_MAX_OUTPUT_INDEX 10
#define DEF_MAX_NAME_LENGTH 64

struct output_t {
    struct wl_output *m_pOutput;
    uv_loop_t *m_pLoop;
    unsigned int m_uiWidth;
    unsigned int m_uiHeight;
    int m_id;
    int m_iOffsetX;
    int m_iOffsetY;
    int m_iTransform;
    char m_strName[DEF_MAX_NAME_LENGTH];
};

struct display_t {
    struct wl_display *mDisplay;
    struct wl_registry *mRegistry;
    struct screenshooter *mScreenShooter;
    struct wl_output *mOutput;  
    struct output_t mOutputList[DEF_MAX_OUTPUT_INDEX];
    int mOutputCount;
};

const wl_registry_listener ScreenShot::registry_listener = {
    ScreenShot::handle_global,
    ScreenShot::handle_global_remove
};
struct display_t *ScreenShot::display;
// Persistent<Function> ScreenShot::constructor;
int ScreenShot::displayHandleCount = 0;
uint8_t* ScreenShot::mData = nullptr;
int ScreenShot::mWidth = 0;
int ScreenShot::mHeight = 0;
int ScreenShot::mStride = 0;
int ScreenShot::mBpp = 0;
PIXEL_FORMAT ScreenShot::mFmt = PIXEL_FORMAT_RGBA;

void ScreenShot::output_handle_geometry(void *data,
                        struct wl_output *wl_output,
                        int x,
                        int y,
                        int physical_width,
                        int physical_height,
                        int subpixel,
                        const char *make,
                        const char *model,
                        int transform )
{
    struct output_t* pOutput = static_cast<struct output_t*>( wl_output_get_user_data(wl_output) );

    if ( pOutput && wl_output == pOutput->m_pOutput ) {
        pOutput->m_iOffsetX = x;
        pOutput->m_iOffsetY = y;
        pOutput->m_iTransform = transform;
    }
}

ScreenShot *ScreenShot::s_pInstance = NULL;

ScreenShot* ScreenShot::getInstance()
{
    if (s_pInstance == NULL)
    {
        s_pInstance = new ScreenShot();
        s_pInstance->createDisplay();
    }

    return s_pInstance;
}

void ScreenShot::deleteInstance()
{
    if (s_pInstance != NULL)
    {
        delete s_pInstance;
        s_pInstance = NULL;
    }
}

void ScreenShot::output_handle_mode(void *data,
                    struct wl_output *wl_output,
                    uint32_t flags,
                    int width,
                    int height,
                    int refresh)
{
    struct output_t* pOutput = static_cast<struct output_t*>( wl_output_get_user_data(wl_output) );

    if ( pOutput && wl_output == pOutput->m_pOutput && (flags & WL_OUTPUT_MODE_CURRENT) ) {
        LOG_D( "output_handle_mode: output: %p, width: %d, height: %d\n", wl_output, width, height );
        if ( pOutput->m_iTransform == WL_OUTPUT_TRANSFORM_90 ||
            pOutput->m_iTransform == WL_OUTPUT_TRANSFORM_270 ) {
            pOutput->m_uiWidth = height;
            pOutput->m_uiHeight = width;
        } else {
            pOutput->m_uiWidth = width;
            pOutput->m_uiHeight = height;
        }
    }
}

void ScreenShot::output_handle_done( void *data,
                    struct wl_output *wl_output )
{
    // LOG_D( __func__ );
}

void ScreenShot::output_handle_scale( void *data,
                    struct wl_output *wl_output,
                    int factor )
{
    // LOG_D( __func__ );
}

void ScreenShot::output_handle_info(void *data,
                    struct wl_output *wl_output,
                    int id,
                    const char *name,
                    struct wl_array *extension )
{
    struct output_t* pOutput = static_cast<struct output_t*>( wl_output_get_user_data(wl_output) );

    // LOG_D("output_handle_info: output: %p, id: %d, name: %s", 
    //         wl_output,
    //         id,
    //         name );

    if ( pOutput && wl_output == pOutput->m_pOutput ) {
        pOutput->m_id = id;
        strncpy( pOutput->m_strName, name, DEF_MAX_NAME_LENGTH - 1 );
    }
}

const struct wl_output_listener ScreenShot::output_listener = {
	
    ScreenShot::output_handle_geometry,
    ScreenShot::output_handle_mode,
    ScreenShot::output_handle_done,
    ScreenShot::output_handle_scale,
    ScreenShot::output_handle_info
};

void ScreenShot::handle_global(void *data, struct wl_registry *registry,
        uint32_t name, const char* interface, uint32_t version)
{
    display = (struct display_t*)(data);
    if ( strcmp(interface, "wl_output") == 0 ) {
        // LOG_D( "catch wl_output %d", name );

        struct wl_output *output = (struct wl_output *)wl_registry_bind(registry, name, &wl_output_interface, 3 );

        if ( display->mOutput == NULL ) {
            display->mOutput = output;
        }

        int index = findOutputIndex( output );
        if ( -1 == index ) {
            index = display->mOutputCount;   
            display->mOutputCount++;
            if ( display->mOutputCount > DEF_MAX_OUTPUT_INDEX ) {
                display->mOutputCount = DEF_MAX_OUTPUT_INDEX;
            }
        }
        if ( index >= DEF_MAX_OUTPUT_INDEX ) {
            // LOG_E("catch wl_output beyond expectations, ignore this %d!", name);

            return;
        }
        display->mOutputList[index].m_pOutput = output;
        wl_output_add_listener( display->mOutputList[index].m_pOutput, &output_listener, &display->mOutputList[index] );
    } else if ( strcmp( interface, "screenshooter" ) == 0 ) {
        // LOG_D( "catch screenshooter %d", name );

        display->mScreenShooter = (struct screenshooter*)wl_registry_bind(registry, name, &screenshooter_interface, 1);
    } else {
        ; // not care
    }
}

void ScreenShot::handle_global_remove(void* data, struct wl_registry *registry, uint32_t name) {
    /* XXX: unimplemented */
}

void ScreenShot::createDisplay() {
    // LOG_E(__func__);
    MM_LOGI("createDisplay begin");
    displayHandleCount++;
    if (display != NULL) {
        return;
    }
    display = (struct display_t*)malloc(sizeof *display);
    assert(display);
    if (display == NULL) {
        ALLOC_FAIL;
    }
    memset( display->mOutputList, 0, sizeof( output_t ) * DEF_MAX_OUTPUT_INDEX );
    display->mOutputCount = 0;
    MM_LOGI("createDisplay done");
}

bool ScreenShot::connectDisplay() {
    // LOG_E(__func__);

    MM_LOGI("connectDisplay begin");
    if (display == NULL) {
        return false;
    }
    display->mDisplay = wl_display_connect(NULL);
    if (display->mDisplay == NULL) {
        displayHandleCount--;
        free(display);
        display = NULL;
        return false;
    }
    MM_LOGI("connectDisplay wl_display_get_registry");
    display->mOutput = NULL;
    display->mRegistry = wl_display_get_registry(display->mDisplay); 
    wl_registry_add_listener(display->mRegistry, &registry_listener, display);
    wl_display_dispatch(display->mDisplay);
    wl_display_roundtrip(display->mDisplay);
    MM_LOGI("connectDisplay done");
    return true;
}

void ScreenShot::releaseDisplay() {
    // LOG_E(__func__);
    if (display == NULL) {
        return;
    }
    displayHandleCount--;
    if (displayHandleCount <= 0) {
        wl_registry_destroy(display->mRegistry);
        wl_display_flush(display->mDisplay);
        wl_display_disconnect(display->mDisplay);

        releaseOutputList();
        free(display);
        display = NULL;
    }
}

int ScreenShot::findOutputIndex( int id )
{
    if ( !display || id < 0 ) return -1;

    for ( int index = 0; index < display->mOutputCount; ++index ) {
        if ( id == display->mOutputList[index].m_id ) {
            return index;
        }
    }

    return -1; 
}

int ScreenShot::findOutputIndex( struct wl_output *output )
{
    if ( !display || !output ) return -1;

    for ( int index = 0; index < display->mOutputCount; ++index ) {
        if ( output == display->mOutputList[index].m_pOutput ) {
            return index;
        }
    }

    return -1; 
}

void ScreenShot::initializeOutputList()
{
    // only call when initialize
    // LOG_D(__func__);

    display->mOutputCount = 0;
    
    for ( uint ui = 0; ui < DEF_MAX_OUTPUT_INDEX; ++ui ) {
        display->mOutputList[ui].m_pOutput = NULL;
        display->mOutputList[ui].m_pLoop = NULL;
        display->mOutputList[ui].m_uiWidth = 0;
        display->mOutputList[ui].m_uiHeight = 0;
        display->mOutputList[ui].m_iOffsetX = 0;
        display->mOutputList[ui].m_iOffsetY = 0;
        display->mOutputList[ui].m_id = -1;
        memset( display->mOutputList[ui].m_strName, 0, DEF_MAX_NAME_LENGTH );
    } 
}

void ScreenShot::releaseOutputList()
{
    // LOG_D(__func__);
    
    for ( uint ui = 0; ui < display->mOutputCount; ++ui ) {
        display->mOutputList[ui].m_pOutput = NULL;

        if ( display->mOutputList[ui].m_pLoop ) {
            int ret = uv_loop_close( display->mOutputList[ui].m_pLoop );
            if ( UV_EBUSY == ret ) {
                // LOG_E("releaseOutputList uv_loop_close error with pending handles");
            }

            free( display->mOutputList[ui].m_pLoop );
            display->mOutputList[ui].m_pLoop = NULL;
        }

        display->mOutputList[ui].m_id = -1;
        memset( display->mOutputList[ui].m_strName, 0, DEF_MAX_NAME_LENGTH );
    }
    display->mOutputCount = 0;
}

std::vector<RGBVec> ScreenShot::captureScreenByID(int id)
{
    
    std::vector<RGBVec> res;
    int index = findOutputIndex( id );
    MM_LOGI("captureScreenByID id %d, index: %d", id, index);

    if ( -1 == index ) {
        return res;
        // args.GetReturnValue().SetNull();
    } else {
        Bitmap *bm = new Bitmap(display->mDisplay,
                                display->mScreenShooter,
                                display->mOutputList[index].m_pOutput,
                                display->mOutputList[index].m_uiWidth, 
                                display->mOutputList[index].m_uiHeight, NULL );
        bm->captureScreen();

        MM_LOGI( "captureScreenByID %d, id: %d, name: %s, (%d, %d)", 
            index,
            display->mOutputList[index].m_id,
            display->mOutputList[index].m_strName,
            display->mOutputList[index].m_uiWidth,
            display->mOutputList[index].m_uiHeight
        );

        void* vaddr = NULL;
        int stride = 0;
        // bitmap应该只是做拷贝
        bm->acquireScreenCaptureContent(&vaddr, &stride);
        if ( !bm->isSecureMode() ) {
            // Local<Object> v8bitmap = caf2::CafBitmap::NewInstance(args);
            // caf2::CafBitmap* cafBitmap = caf2::CafBitmap::Unwrap<caf2::CafBitmap>(v8bitmap);
            // caf2::Bitmap* bitmap = cafBitmap->getBitmap();
            // bool ans = bitmap->initBitmap( display->mOutputList[index].m_uiWidth, 
            //                                 display->mOutputList[index].m_uiHeight, 
            //                                 PIXEL_FORMAT_RGBA );
            // if (ans) {
            //     bitmap->setData((uint8_t*)vaddr, stride * 4);
            //     bitmap->convertEndin();
            // } else {
            //     args.GetReturnValue().SetNull();
            // }
            resize(display->mOutputList[index].m_uiWidth, 
                                            display->mOutputList[index].m_uiHeight, 
                                            PIXEL_FORMAT_RGBA);
            setData((uint8_t*)vaddr, stride * 4);
            convertEndin();
            // uint8_t* buffer = (uint8_t*)vaddr;
            MM_LOGI("captureScreenByID success id %d, index: %d, %X %X %X", id, index, *mData, *(mData + 1), *(mData + 2));
            std::vector<RGBVec> primaryColors = ColorPicker::getInstance()->getQuantColors(mData, stride * 4);
            MM_LOGI("captureScreenByID getQuantColors size: %d", primaryColors.size());
            // ImageColorCollector::RespResult colorRes = ImageColorCollector::colorCollecting(nullptr, stride * 4, display->mOutputList[index].m_uiWidth, display->mOutputList[index].m_uiHeight);
            // MM_LOGI("captureScreenByID colorCollecting code: %d, msg: %s, res: %s", colorRes.code, colorRes.codeMsg.c_str(), colorRes.data.c_str());
            int count = 0;
            for (auto it = primaryColors.rbegin(); it != primaryColors.rend(); ++it) {
                MM_LOGI("captureScreenByID getQuantColors2 r: %d, g: %d, b: %d, count: %d", (*it).r, (*it).g, (*it).b, count);
                if (count < 4) {
                    res.push_back(*it);
                    count++;
                } else {
                    break;
                }
            }
        } else {
            MM_LOGE("captureScreenByID error id %d, index: %d", id, index);
            // args.GetReturnValue().SetNull();
        }

        bm->releaseScreenCaptureContent(vaddr);
        delete bm;
    }
    return res;
}

void ScreenShot::captureScreenByIDAsync(int id)
{
    int index = findOutputIndex( id );
    if ( -1 == index ) {
        // LOG_E( "captureScreenByIDAsync faild with error id: %d", id );

        return;
    }
}