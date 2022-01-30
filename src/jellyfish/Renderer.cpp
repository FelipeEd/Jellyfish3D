#include <jellyfish/Jellyfish3D.hpp>

Renderer::Renderer()
{
    if (pbr)
    {
        m_objectShader = Shader("bin/shaders/pbr_vertex.glsl", "bin/shaders/pbr_fragment.glsl");
    }
    else
    {
        m_objectShader = Shader("bin/shaders/default_vertex.glsl", "bin/shaders/default_fragment.glsl");
    }

    m_lightShader = Shader("bin/shaders/light_vertex.glsl", "bin/shaders/light_fragment.glsl");
    m_skyboxShader = Shader("bin/shaders/skybox_vertex.glsl", "bin/shaders/skybox_fragment.glsl");
}

Renderer::~Renderer()
{
    m_objectShader.Delete();
    m_lightShader.Delete();
    m_skyboxShader.Delete();
}

void Renderer::drawObjects(Scene &scene, App &app)
{
    Camera *cam = scene.getActiveCam();

    m_objectShader.use();
    m_objectShader.setFloat("uTime", app.getTime());

    // Seting camera transforms unifomrs
    m_objectShader.setMat4("uView", cam->getViewMatrix());
    m_objectShader.setMat4("uProjection", cam->getProjectionMatrix());

    // For all objects in the scene
    for (int i = 0; i < scene.m_object.size(); i++)
    {
        Mesh mesh = app.assets.meshes[scene.m_object[i].getMeshId()];
        Material material = app.assets.materials[scene.m_object[i].getMaterialId()];

        skybox.setUniforms(m_objectShader);
        material.setUniforms(m_objectShader);

        m_objectShader.setBool("uIsBoid", scene.m_object[i].isBoids);

        // Setting the object transformations
        m_objectShader.setMat4("uModel", scene.m_object[i].getModelMatrix());

        // Set camera pos
        if (pbr)
        {
            m_objectShader.setVec3("uCamPos", cam->transform.position);

            for (int j = 0; j < scene.m_lights.size(); j++)
            {
                m_objectShader.setVec3("lightPositions[" + std::to_string(j) + "]", scene.m_lights[j].transform.position);
                m_objectShader.setVec3("lightColors[" + std::to_string(j) + "]", scene.m_lights[j].getColor());
            }
        }

        mesh.bindBuffer();

        glDrawArrays(GL_TRIANGLES, 0, mesh.getNVertex());
        mesh.unbindBuffer();
    }
}

void Renderer::drawLights(Scene &scene, App &app)
{
    Camera *cam = scene.getActiveCam();

    m_lightShader.use();

    // Seting camera transforms unifomrs
    m_lightShader.setMat4("uView", cam->getViewMatrix());
    m_lightShader.setMat4("uProjection", cam->getProjectionMatrix());

    // For all lights in the scene
    for (int i = 0; i < scene.m_lights.size(); i++)
    {

        // Retrieving the mesh from global resources
        Mesh mesh = app.assets.meshes[scene.m_lights[i].getMeshId()];

        m_lightShader.use();
        m_lightShader.setVec4("uColor", glm::vec4(scene.m_lights[i].getColor(), 1.0f));
        // Setting transformations
        m_lightShader.setMat4("uModel", scene.m_lights[i].getModelMatrix());

        mesh.bindBuffer();

        glDrawArrays(GL_TRIANGLES, 0, mesh.getNVertex());
        mesh.unbindBuffer();
    }
}

void Renderer::drawSkybox(Scene &scene, App &app)
{
    Camera *cam = scene.getActiveCam();

    m_skyboxShader.use();

    glDepthFunc(GL_LEQUAL);                                                      // change depth function so depth test passes when values are equal to depth buffer's content
    m_skyboxShader.setMat4("uView", glm::mat4(glm::mat3(cam->getViewMatrix()))); // remove translation from the view matrix
    m_skyboxShader.setMat4("uProjection", cam->getProjectionMatrix());
    //m_skyboxShader.setInt();

    skybox.bindBuffer();
    m_skyboxShader.setInt("uTexSkybox", 5);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS);
}

void Renderer::draw(Scene &scene, App &app)
{

    drawObjects(scene, app);
    drawLights(scene, app);
    if (toggleSkybox)
        drawSkybox(scene, app);
}

void Renderer::switchWireframeMode()
{
    wireframeMode = !wireframeMode;

    if (wireframeMode)
    {
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glEnable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void Renderer::switchSkybox()
{
    toggleSkybox = !toggleSkybox;
}