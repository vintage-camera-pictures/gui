#ifndef GUI_APPLICATION_CLASS_HEADER
#define GUI_APPLICATION_CLASS_HEADER


#include <GLFW/glfw3.h> 
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

class application {
public:
    application();
    ~application();
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

}

#endif