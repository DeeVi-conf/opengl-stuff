#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_s.hpp"
#include <iostream>
#include <regex>
#include <sys/types.h>
#include "stb_image/stb_image.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float ratio = 0.2;


void processInput(GLFWwindow *window){
    for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; key++) {
        if (glfwGetKey(window, key) == GLFW_PRESS) {
            switch (key) {
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(window, true);
                    break;
                case GLFW_KEY_UP:
                    if(ratio<1.0) {ratio += 0.01;} else {ratio=1.0;}
                    //std::cout<<"Up key pressed\n";
                    break;
                case GLFW_KEY_DOWN:
                    if(ratio>0.0)ratio -= 0.01; else {ratio = 0.0;}
                    //std::cout<<"Down key pressed\n";
                    break;
                default:
                    break;
            }
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

uint NewTexture(const char* path){
    uint texture;
    std::regex jpgPattern(R"(.*\.(jpg|jpeg|bmp|tga)$)", std::regex::icase);
    std::regex pngPattern(R"(.*\.png$)", std::regex::icase);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    //stbi_set_flip_vertically_on_load(true);
    unsigned char *data =
        stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        if (std::regex_match(path, jpgPattern)){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }else if (std::regex_match(path, pngPattern)) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
      std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    //data
    float vertices[] = {
    // positions                        // colors                       // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,   // First Triangle
        1, 2, 3    // Second Triangle
    };

    uint texture = NewTexture("resources/container.jpg");
    uint texture2 = NewTexture("resources/awesomeface.png");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    Shader shaderProgram("shaders/vertexShader.vs","shaders/fragmentShader.fs");


    // Main Initialization
    unsigned int vertex_buffer_object;
    glGenBuffers(1, &vertex_buffer_object);
    unsigned int VertexArrayObject;
    glGenVertexArrays(1, &VertexArrayObject); 
    uint EBO;
    glGenBuffers(1, &EBO);

    // 1. bind Vertex Array Object
    glBindVertexArray(VertexArrayObject);
    // 2. copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1); 

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2); 

    shaderProgram.use();
    shaderProgram.setInt("texture", 0);
    shaderProgram.setInt("texture2", 1);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        shaderProgram.use();
        shaderProgram.setInt("texture", 0);
        shaderProgram.setInt("texture2", 1);
        processInput(window);
        //std::cout<<ratio<<"\n";
        shaderProgram.setFloat("ratio", ratio);

        // main rendering loop
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VertexArrayObject);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertex_buffer_object);
    glDeleteVertexArrays(1, &VertexArrayObject);
    //glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

