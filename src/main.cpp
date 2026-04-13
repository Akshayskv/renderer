#include <iostream>

#include <glad/gl.h>
#include "window.h"


int main() {

    Window w(800, 800, "renderer");
    while(w.isOpen()) {
        w.update();
    }
    
    return 0;
}