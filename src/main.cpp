#include <iostream>
#include <GLFW/glfw3.h>

int main() {

    glfwInit();
    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}