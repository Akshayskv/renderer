#include "window.h"

#include <iostream>

int Window::s_instCount = 0;

Window::Window(int width, int height, const std::string& name) : m_width(width), m_height(height), m_name(name) {
    if(s_instCount == 0) {
        if(!glfwInit()) 
            std::cout << "glfw init error" << std::endl;
    }

    m_handle = glfwCreateWindow(m_width, m_height, m_name.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_handle);
    s_instCount++;
}

Window::~Window() {
    glfwDestroyWindow(m_handle);
    s_instCount--;
    if(s_instCount == 0) {
        glfwTerminate();
    }
}

bool Window::isOpen() const {
    if(m_handle == nullptr) {
        std::cout << "Error: No valid window was created" << std::endl;
        return false;
    }
    return !glfwWindowShouldClose(m_handle);
}

void Window::update() {
    if(m_handle == nullptr) {
        std::cout << "Error: No valid window was created" << std::endl;
        return;
    }

    glfwSwapBuffers(m_handle);
    glfwPollEvents();
}