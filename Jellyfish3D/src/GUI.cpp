#include <GUI.hpp>

GUI::~GUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUI::init(GLFWwindow *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void GUI::startFrame(const std::string &windowName)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin(windowName.c_str());
}

void GUI::endFrame()
{
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::sliderFloat(const std::string &variableName, float &a, float min, float max)
{
    ImGui::SliderFloat(variableName.c_str(), &a, min, max);
}

void GUI::sliderInt(const std::string &variableName, int &a, int min, int max)
{
    ImGui::SliderInt(variableName.c_str(), &a, min, max);
}

bool GUI::button(const std::string &buttonName)
{
    return ImGui::Button(buttonName.c_str());
}

void GUI::text(const std::string &text)
{
    ImGui::Text(text.c_str());
}
void GUI::checkbox(const std::string &label, bool &value)
{
    ImGui::Checkbox(label.c_str(), &value);
}

void GUI::separator()
{
    ImGui::Separator();
}

bool GUI::collapsingHeader(const std::string &label)
{
    return ImGui::CollapsingHeader(label.c_str());
}