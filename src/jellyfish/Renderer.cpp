#include <jellyfish/Jellyfish3D.hpp>

Renderer::Renderer()
{
    m_shader = Shader("bin/shaders/default_vertex.glsl", "bin/shaders/default_fragment.glsl");
}

void Renderer::draw(Scene scene)
{
    Camera *cam = scene.getActiveCam();

    // For all objects in the scene
    for (int i = 0; i < scene.m_object.size(); i++)
    {
        // Retrieving the mesh from global resources
        Mesh mesh = assets->meshes[scene.m_object[i].getMeshId()];
        Material material = assets->materials[scene.m_object[i].getMaterialId()];

        m_shader.use();
        // Setting the material uniforms
        material.setUniforms(m_shader);

        // Seting camera transforms unifomrs
        m_shader.setMat4("uView", cam->getViewMatrix());
        m_shader.setMat4("uProjection", cam->getProjectionMatrix());

        // Setting the object transformations
        m_shader.setMat4("uScale", scene.m_object[i].getScaleMatrix());
        m_shader.setMat4("uRotate", scene.m_object[i].getRotateMatrix());
        m_shader.setMat4("uTranslate", scene.m_object[i].getTranslateMatrix());

        mesh.bindBuffer();
        if (mesh.getNIndices() > 0)
            glDrawElements(GL_TRIANGLES, mesh.getNIndices(), GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(GL_TRIANGLES, 0, mesh.getNVertex());
        //glDrawElements(GL_LINE_LOOP, mesh.getNIndices(), GL_UNSIGNED_INT, 0);
    }
}