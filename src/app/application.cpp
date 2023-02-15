#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "application.hpp"

#include <stdexcept>
#include <string>


namespace gui_font {
    #include "Roboto-Regular.embed"
}


namespace {
static void glfw_error_callback(int error, const char* description) {
    const std::string error_message = "GLFW Error " + std::to_string(error) + description;
    throw std::runtime_error(error_message);
}
}


namespace gui {

window::window(const char* title)
{
#if defined(__APPLE__)
    // GL 3.2 + GLSL 150
    version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif
 
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    glfw_window = glfwCreateWindow(900, 600, title, nullptr, nullptr);
    if (glfw_window == nullptr) {
        throw std::runtime_error("Unable to create GLFW window");
    }

    glfwMakeContextCurrent(glfw_window);
    glfwSwapInterval(1); 

    // tie window context to glad opengl functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))  
		throw std::runtime_error("Unable to context to OpenGL");

}

window::~window()
{
    if (glfw_window != nullptr) {
        glfwDestroyWindow(glfw_window);
    }
}

const char* window::glsl_version() const {
    return version.c_str();
}

GLFWwindow* window::get() const {
    return glfw_window;
}


application::application() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        throw std::runtime_error("Unable to initialise GLFW");
    }
}

application::~application() {
    glfwTerminate();
}

backend::backend(const window& w) {
    ImGui_ImplGlfw_InitForOpenGL(w.get(), true);
    ImGui_ImplOpenGL3_Init(w.glsl_version());    
}

backend::~backend() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();    
}

context::context() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& imgui_io = ImGui::GetIO(); 
    imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    imgui_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    imgui_io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    ImGuiStyle& style = ImGui::GetStyle();
    if (imgui_io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImFontConfig fontConfig;
    fontConfig.FontDataOwnedByAtlas = false;
    ImFont* robotoFont = imgui_io.Fonts->AddFontFromMemoryTTF((void*)gui_font::g_RobotoRegular, 
                                                        sizeof(gui_font::g_RobotoRegular), 
                                                        20.0f, 
                                                        &fontConfig);
    imgui_io.FontDefault = robotoFont;


}

context::~context() {
    ImGui::DestroyContext();
}

ImGuiIO& context::io() const {
    return ImGui::GetIO();
}

}