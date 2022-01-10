#include <jellyfish/Jellyfish3D.hpp>

Renderer::Renderer()
{
    if (pbr)
    {
        m_shader = Shader("bin/shaders/pbr_vertex.glsl", "bin/shaders/pbr_fragment.glsl");
    }
    else
    {
        m_shader = Shader("bin/shaders/default_vertex.glsl", "bin/shaders/default_fragment.glsl");
    }

    m_lightShader = Shader("bin/shaders/light_vertex.glsl", "bin/shaders/light_fragment.glsl");
}

void Renderer::draw(Scene scene)
{
    Camera *cam = scene.getActiveCam();

    m_shader.use();
    // Seting camera transforms unifomrs
    m_shader.setMat4("uView", cam->getViewMatrix());
    m_shader.setMat4("uProjection", cam->getProjectionMatrix());

    // For all objects in the scene
    for (int i = 0; i < scene.m_object.size(); i++)
    {
        // Retrieving the mesh from global resources
        Mesh mesh = assets->meshes[scene.m_object[i].getMeshId()];
        Material material = assets->materials[scene.m_object[i].getMaterialId()];

        ;
        material.setUniforms(m_shader);

        // Setting the object transformations
        m_shader.setMat4("uScale", scene.m_object[i].getScaleMatrix());
        m_shader.setMat4("uRotate", scene.m_object[i].getRotateMatrix());
        m_shader.setMat4("uTranslate", scene.m_object[i].getTranslateMatrix());

        // Set camera pos
        if (pbr)
        {
            m_shader.setVec3("uCamPos", cam->m_transform.getPosition());

            for (int j = 0; j < scene.m_lights.size(); j++)
            {
                m_shader.setVec3("lightPositions[" + std::to_string(j) + "]", scene.m_lights[j].m_transform.getPosition());
                m_shader.setVec3("lightColors[" + std::to_string(j) + "]", scene.m_lights[j].getColor());
            }
        }

        mesh.bindBuffer();
        if (mesh.getNIndices() > 0)
            glDrawElements(GL_TRIANGLES, mesh.getNIndices(), GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(GL_TRIANGLES, 0, mesh.getNVertex());
        //glDrawElements(GL_LINE_LOOP, mesh.getNIndices(), GL_UNSIGNED_INT, 0);
    }

    m_lightShader.use();
    // Seting camera transforms unifomrs
    m_lightShader.setMat4("uView", cam->getViewMatrix());
    m_lightShader.setMat4("uProjection", cam->getProjectionMatrix());

    // For all lights in the scene
    for (int i = 0; i < scene.m_lights.size(); i++)
    {

        // Retrieving the mesh from global resources
        Mesh mesh = assets->meshes[scene.m_lights[i].getMeshId()];
        //Material material = assets->materials[scene.m_lights[i].getMaterialId()];

        m_lightShader.use();
        //material.setUniforms(m_lightShader);
        m_lightShader.setVec4("uColor", glm::vec4(scene.m_lights[i].getColor(), 1.0f));
        // Setting the object transformations
        m_lightShader.setMat4("uScale", scene.m_lights[i].getScaleMatrix());
        m_lightShader.setMat4("uRotate", scene.m_lights[i].getRotateMatrix());
        m_lightShader.setMat4("uTranslate", scene.m_lights[i].getTranslateMatrix());

        mesh.bindBuffer();
        if (mesh.getNIndices() > 0)
            glDrawElements(GL_TRIANGLES, mesh.getNIndices(), GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(GL_TRIANGLES, 0, mesh.getNVertex());
        //glDrawElements(GL_LINE_LOOP, mesh.getNIndices(), GL_UNSIGNED_INT, 0);
    }
}