file(GLOB_RECURSE BOIDS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(Boids ${BOIDS_SOURCES})
target_link_libraries(Boids PRIVATE Jellyfish3D X11)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/Examples/Boids)
set_target_properties(Boids PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
