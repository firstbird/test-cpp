
#pragma once
// #include <wayland-client-protocol.h>
#include "wayland-client-protocol.h"

// https://github.com/krh/weston/blob/master/src/screenshooter.c#L36
struct screenshooter {
	struct wl_object base;
	struct weston_compositor *ec;
	struct wl_global *global;
	struct wl_client *client;
	struct weston_process process;
	struct wl_listener destroy_listener;
};

class ScreenShot {
public:
	static ScreenShot *s_pInstance;
	static const wl_output_listener output_listener;
	ScreenShot* getInstance();
	void deleteInstance();
	static void output_handle_geometry(void *data,
				    struct wl_output *wl_output,
				    int x,
				    int y,
				    int physical_width,
				    int physical_height,
				    int subpixel,
				    const char *make,
				    const char *model,
				    int transform);
	static void output_handle_mode(void *data,
				struct wl_output *wl_output,
				uint32_t flags,
				int width,
				int height,
				int refresh);
	static void output_handle_done(void *data,
				struct wl_output *wl_output);
	static void output_handle_scale(void *data,
				 struct wl_output *wl_output,
				 int factor);
	static void output_handle_info(void *data,
				struct wl_output *wl_output,
				int id,
				const char *name,
				struct wl_array *extension);
	static void handle_global(void *data, struct wl_registry *registry,
			   uint32_t name, const char *interface, uint32_t version);
	static void handle_global_remove(void *data, struct wl_registry *registry, uint32_t name);

private:
	ScreenShot() = default;
	~ScreenShot() = default;
	ScreenShot(const ScreenShot&) = delete;
	ScreenShot &operator=(const ScreenShot &) = delete;
};