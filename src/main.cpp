#include <iostream>

#include "window.h"


int main() {

    Window w(800, 600, "renderer");
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    while(w.isOpen()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        w.update();
    }
    
    return 0;
}