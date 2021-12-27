#include <jellyfish/Jellyfish3D.hpp>

Renderer::Renderer()
{
    m_shader = Shader("bin/shaders/default_vertex.glsl", "bin/shaders/default_fragment.glsl");
}

void Renderer::draw(Object obj)
{
    // Retrieving the mesh from global resources
    Mesh mesh = assets->meshes[obj.getMeshId()];
    Material material = assets->materials[obj.getMaterialId()];

    m_shader.use();
    material.setUniforms(m_shader);
    mesh.bindBuffer();

    glDrawElements(GL_TRIANGLES, mesh.getNIndices(), GL_UNSIGNED_INT, 0);
}