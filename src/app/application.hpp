#ifndef GUI_APPLICATION_CLASS_HEADER
#define GUI_APPLICATION_CLASS_HEADER

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "platform.hpp"

#include <functional>

namespace gui {

template <typename state>
class application {
    platform p;
    GLFWwindow* window;
    ImGuiIO& io;
    int display_w;
    int display_h;
    typedef std::function<void(platform&, state&)> render_function;
    render_function do_render;
public:
    application(const char* title,
                render_function renderer)
    : p(title)
    , window(p.get_window().get())
    , io(p.get_context().io())
    , do_render(renderer)
    {    
    }
    ~application() = default;

    void run(state& s) {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            do_render(p, s);

            // Rendering
            ImGui::Render();
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            const float red = p.clear_color[0] * p.clear_color[3];
            const float green = p.clear_color[1] * p.clear_color[3];
            const float blue = p.clear_color[2] * p.clear_color[3];
            const float alpha = p.clear_color[3];
            glClearColor(red, green, blue, alpha);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }

            glfwSwapBuffers(window);
        }
    }

    platform& get_platform() {return p;}
};

}

#endif