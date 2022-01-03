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
    // Setting the material uniforms
    material.setUniforms(m_shader);

    // Seting camera transforms unifomrs
    m_shader.setMat4("uView", camera.getViewMatrix());
    m_shader.setMat4("uProjection", camera.getProjectionMatrix());

    // Setting the object transformations
    m_shader.setMat4("uScale", obj.getScaleMatrix());
    m_shader.setMat4("uRotate", obj.getRotateMatrix());
    m_shader.setMat4("uTranslate", obj.getTranslateMatrix());

    mesh.bindBuffer();
    if (mesh.getNIndices() > 0)
        glDrawElements(GL_TRIANGLES, mesh.getNIndices(), GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_TRIANGLES, 0, mesh.getNVertex());
    //glDrawElements(GL_LINE_LOOP, mesh.getNIndices(), GL_UNSIGNED_INT, 0);
}