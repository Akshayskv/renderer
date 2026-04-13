#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const std::string& name);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    bool isOpen() const;
    void update();
private:
    GLFWwindow* m_handle;
    int m_width;
    int m_height;
    std::string m_name;
    static int s_instCount;
};

#endif