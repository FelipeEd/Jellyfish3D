#pragma once

// Forward declaration to hide GLFW from public API
struct GLFWwindow;

extern unsigned int WIDTH;
extern unsigned int HEIGHT;

// For now handles opengl init stuff
class Display
{
private:
    GLFWwindow *m_window;
    void processInput();

public:
    Display();
    ~Display();

    // Window control
    bool shouldClose() const;
    void swapBuffers();
    void pollEvents();
    
    // Rendering control
    void setClearColor(float r, float g, float b, float a = 1.0f);
    void clear();
    void clearColor();
    void clearDepth();
    void flush();
    
    // avoid exposing this to users
    GLFWwindow *getWindow() const { return m_window; }
};
