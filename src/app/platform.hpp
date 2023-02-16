#ifndef GUI_PLATFORM_CLASS_HEADER
#define GUI_PLATFORM_CLASS_HEADER

#include <imgui.h>     // ImGuiIO
#include <imgui_impl_glfw.h>   // GLFWwindow

#include <string>

namespace gui {

class window {
    GLFWwindow* glfw_window;
    std::string version;
public:
    window(const char* title);
    ~window();
    const char* glsl_version() const;
    GLFWwindow* get() const;
};

class initialiser {
public:
    initialiser();
    ~initialiser();
};


class backend {
public:
    backend(const window& w);
    ~backend();
};


class context {
public:
    context();
    ~context();
    ImGuiIO& io() const;
};


class platform {
public:
    float clear_color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
private:    
    initialiser i;
    window w;
    context c;
    backend b;
public:
    platform(const char* title);
    ~platform() = default;

    context& get_context() { return c; }
    window& get_window() {return w; }
};

}

#endif