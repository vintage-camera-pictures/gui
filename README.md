# GUI

Minimalistic Wrapper for a Dear ImGui application using GLFW3, GLAD and OpenGL inspired by [Walnut](https://github.com/TheCherno/Walnut.git) written by Yan Chernikov.

Following the principles of IMGUI (Immediate Mode GUI), the state is owned by the client code and is passed to the renderer for each frame. The `gui::platform` and `gui::application` classes are wrappers that hide implementation details of Dear ImGui/GLFW3/glad and OpenGL and use the RAII technique to make the C code slightly safer.

# Disclaimer

The code in this repository is not production-ready software. It comes with no support or guarantees whatsoever.

# How to use the code

Here are the steps:

1. Create a structure to hold your state. We'll call it `application_state`, you can call it differently if you like.

1. Write the `render` function with the following signature:

```C
void render(gui::platform& platform, application_state& state);
```

This is your usual Dear ImGui rendering code that you start with `ImGui::Begin` and end with `ImGui::End`

1. Instantiate `gui::application<application_state>` object, passing the main window title and the render function to the constructor.

```C
    gui::application<application_state> application("Welcome", render);
```

1. Create an instance of `application_state` and change the default values if required.

```C
    application_state state;
```

1. Start the application

```C
    application.run(state)
```

# Example

The `render.hpp` and `render.cpp` files provide an example of the user code. It is adopted from the brilliant [Dear ImGui demo](https://github.com/ocornut/imgui/blob/master/examples/example_glfw_opengl3/main.cpp). Please note that the original demo does not use `glad`. If you choose to use it, insert the following code before calling any OpenGL functions:

```C++
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		// Fatal error loading OpenGL
```
