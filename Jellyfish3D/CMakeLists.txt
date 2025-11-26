file(GLOB_RECURSE JELLYFISH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE JELLYFISH_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_library(Jellyfish3D STATIC ${JELLYFISH_SOURCES} ${JELLYFISH_HEADERS})

target_include_directories(Jellyfish3D PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include
)

target_compile_definitions(Jellyfish3D PUBLIC 
    GLFW_INCLUDE_NONE
    GLM_ENABLE_EXPERIMENTAL
)

target_link_libraries(Jellyfish3D PUBLIC
    glfw
    glm::glm
    glad
    imgui
    stbi
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(Jellyfish3D PRIVATE -g -Wall -Wextra)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(Jellyfish3D PRIVATE -O3 -DNDEBUG)
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})
