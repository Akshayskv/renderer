#include <iostream>
#include <chrono>
#include "window.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "shader.h"
#include "texture.h"
#include "camera.h"

Window w {800, 600, "renderer"};

void update(Camera&, const float&);

int main() {

    try{
        Camera mycam{(float)w.getWidth() / (float)w.getHeight()};
        Shader mysh("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
        VertexBuffer<TexturedVertex> cubeVertices{{
            //     X      Y      Z      U     V
            // Front (+Z)
            { -0.5f, -0.5f,  0.5f,  0.0f, 0.0f },
            {  0.5f, -0.5f,  0.5f,  1.0f, 0.0f },
            {  0.5f,  0.5f,  0.5f,  1.0f, 1.0f },
            { -0.5f,  0.5f,  0.5f,  0.0f, 1.0f },

            // Back (-Z)
            {  0.5f, -0.5f, -0.5f,  0.0f, 0.0f },
            { -0.5f, -0.5f, -0.5f,  1.0f, 0.0f },
            { -0.5f,  0.5f, -0.5f,  1.0f, 1.0f },
            {  0.5f,  0.5f, -0.5f,  0.0f, 1.0f },

            // Right (+X)
            {  0.5f, -0.5f,  0.5f,  0.0f, 0.0f },
            {  0.5f, -0.5f, -0.5f,  1.0f, 0.0f },
            {  0.5f,  0.5f, -0.5f,  1.0f, 1.0f },
            {  0.5f,  0.5f,  0.5f,  0.0f, 1.0f },

            // Left (-X)
            { -0.5f, -0.5f, -0.5f,  0.0f, 0.0f },
            { -0.5f, -0.5f,  0.5f,  1.0f, 0.0f },
            { -0.5f,  0.5f,  0.5f,  1.0f, 1.0f },
            { -0.5f,  0.5f, -0.5f,  0.0f, 1.0f },

            // Top (+Y)
            { -0.5f,  0.5f,  0.5f,  0.0f, 0.0f },
            {  0.5f,  0.5f,  0.5f,  1.0f, 0.0f },
            {  0.5f,  0.5f, -0.5f,  1.0f, 1.0f },
            { -0.5f,  0.5f, -0.5f,  0.0f, 1.0f },

            // Bottom (-Y)
            { -0.5f, -0.5f, -0.5f,  0.0f, 0.0f },
            {  0.5f, -0.5f, -0.5f,  1.0f, 0.0f },
            {  0.5f, -0.5f,  0.5f,  1.0f, 1.0f },
            { -0.5f, -0.5f,  0.5f,  0.0f, 1.0f },
        }};

        IndexBuffer cubeIndices = {{          
            0,  1,  2,   2,  3,  0,   // front
            4,  5,  6,   6,  7,  4,   // back
            8,  9, 10,  10, 11,  8,   // right
            12, 13, 14,  14, 15, 12,   // left
            16, 17, 18,  18, 19, 16,   // top
            20, 21, 22,  22, 23, 20,   // bottom
   
        }};
        
        mycam.setPosition({0.0f, 0.0f, 0.0f});

        VertexArray varray;
        varray.addlayout<TexturedVertex>(cubeVertices, cubeIndices);
        Texture bricktex{"../assets/textures/container.jpg"};
        mysh.bind();        
        bricktex.bind();

        int unifomLoc = mysh.getUniformLocation("u_Viewprojection");
        mysh.setUniformMatrix4f(unifomLoc, mycam.getViewProjection());
        glEnable(GL_DEPTH_TEST);

        glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

        auto lastFrameTime = std::chrono::high_resolution_clock::now();
        
        while(w.isOpen()) {
            auto currentFrameTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsedTime = lastFrameTime - currentFrameTime;

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            lastFrameTime = currentFrameTime;
            float dt = elapsedTime.count();

            mycam.setAspectRatio((float)w.getWidth() / (float)w.getHeight());
            update(mycam, dt);
            mysh.setUniformMatrix4f(unifomLoc, mycam.getViewProjection());

            varray.bind();
            glDrawElements(GL_TRIANGLES, cubeIndices.getCount(), GL_UNSIGNED_INT, 0);
            varray.unbind();
            w.update();
        }
        
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    return 0;
}

void update(Camera& cam, const float& dt) {
    if(w.isKeyPressed(KeyCodes::KEY_W)) cam.move({0.0f, 0.0f, -1.0f}, dt);
    else if(w.isKeyPressed(KeyCodes::KEY_A)) cam.move({-1.0f, 0.0f, 0.0f}, dt);
    else if(w.isKeyPressed(KeyCodes::KEY_S)) cam.move({0.0f, 0.0f, 1.0f}, dt);
    else if(w.isKeyPressed(KeyCodes::KEY_D)) cam.move({1.0f, 0.0f, 0.0f}, dt);
}