#include <jellyfish/Jellyfish3D.hpp>

Renderer::Renderer()
{
    m_shader = Shader("bin/shaders/default_vertex.glsl", "bin/shaders/default_fragment.glsl");
}

void Renderer::draw(Object obj, Camera camera) //! should recive a scene !
{
    // Retrieving the mesh from global resources
    Mesh mesh = assets->meshes[obj.getMeshId()];
    Material material = assets->materials[obj.getMaterialId()];

    m_shader.use();

    // Seting camera transforms unifomrs
    m_shader.setMat4("uView", camera.getViewMatrix());
    m_shader.setMat4("uProjection", camera.getProjectionMatrix());

    // seting the material uniforms
    material.setUniforms(m_shader, obj);

    mesh.bindBuffer();
    glDrawElements(GL_TRIANGLES, mesh.getNIndices(), GL_UNSIGNED_INT, 0);

    //glDrawElements(GL_LINE_LOOP, mesh.getNIndices(), GL_UNSIGNED_INT, 0);
}