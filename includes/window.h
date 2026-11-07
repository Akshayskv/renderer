#ifndef WINDOW_H
#define WINDOW_H

#include <string>

struct GLFWwindow;

enum class KeyCodes {
    KEY_W = 87,
    KEY_A = 65,
    KEY_S = 83,
    KEY_D = 68
};

class Window {
public:
    Window(int width, int height, const std::string& name);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    bool isOpen() const;
    bool isKeyPressed(KeyCodes code) const;
    void update();
    int getWidth() const;
    int getHeight() const;
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