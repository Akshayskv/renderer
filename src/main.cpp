#include <iostream>

#include "window.h"
#include "vertexarray.h"
#include "vertexbuffer.h"

int main() {

    Window w {800, 600, "renderer"};
    
    VertexBuffer<VertexB> buffer{{{0.0f, 0.5f, 0.0f}, {-0.5f, -0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}}};
    VertexArray varray;
    varray.addlayout<VertexB>(buffer);
    
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    
    while(w.isOpen()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        w.update();
    }
    
    return 0;
}