find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)


set(GUI_HEADER_FILES
    application.hpp
)

set(GUI_SOURCE_FILES
    application.cpp
    gui.cpp
)


add_executable(${PROJECT_NAME} 
    ${GUI_HEADER_FILES}
    ${GUI_SOURCE_FILES}
)


target_link_libraries(${PROJECT_NAME} 
    PRIVATE glad::glad
    PRIVATE glfw
    PRIVATE imgui::imgui
)

target_compile_definitions(${PROJECT_NAME} PRIVATE CMAKE_EXPORT_COMPILE_COMMANDS=1)


