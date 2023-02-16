#include "application.hpp"
#include "render.hpp"   // app::application_state and app::render

int main(int, char**)
{
    gui::application<app::application_state> application("Welcome", app::render);
    app::application_state state;    
    application.run(state);

    return 0;
}
