add_library(glad STATIC glad/src/glad.c)
target_include_directories(glad PUBLIC glad/include)

file(GLOB IMGUI_SOURCES imgui/*.cpp)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC imgui)
target_compile_definitions(imgui PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)
target_link_libraries(imgui PUBLIC glfw glad)

file(GLOB STB_SOURCES stbi/*.cpp)
add_library(stbi STATIC ${STB_SOURCES})
target_include_directories(stbi PUBLIC stbi)
