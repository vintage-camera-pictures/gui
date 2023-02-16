#ifndef GUI_RENDER_HEADER
#define GUI_RENDER_HEADER

#include "platform.hpp"

namespace app {

struct application_state {
    bool show_demo_window{true};
    bool show_another_window{false};
    float clear_color[3] = {0.1f, 0.1f, 0.1f};
};

void render(gui::platform& platform, application_state& state);

}

#endif