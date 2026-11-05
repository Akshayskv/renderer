#ifndef WINDOW_H
#define WINDOW_H

#include <string>

struct GLFWwindow;

class Window {
public:
    Window(int width, int height, const std::string& name);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    bool isOpen() const;
    void update();
private:
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
private:
    GLFWwindow* m_handle;
    int m_width;
    int m_height;
    std::string m_name;
    static int s_instCount;
};

#endif