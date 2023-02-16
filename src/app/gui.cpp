#include "application.hpp"

struct application_state {
    bool show_demo_window{true};
    bool show_another_window{false};
    float clear_color[3] = {0.1f, 0.1f, 0.1f};
};

void render(gui::platform& platform, application_state& state) {

    // 1. Show the big demo window 
    if (state.show_demo_window)
        ImGui::ShowDemoWindow(&state.show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &state.show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &state.show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", state.clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (state.show_another_window)
    {
        ImGui::Begin("Another Window", &state.show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me"))
            state.show_another_window = false;
        ImGui::End();
    }
}



int main(int, char**)
{
    application_state as;
    gui::application<application_state> application("Welcome", render); 

    ImGui::StyleColorsDark();

    gui::platform& p = application.get_platform();
    p.clear_color[0] = 0.2f;
    p.clear_color[1] = 0.2f;
    p.clear_color[2] = 0.2f;
    p.clear_color[3] = 1.0f;

    application.run(as);

    return 0;
}
