#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm/detail/func_trigonometric.hpp"
#include "glm/glm/detail/type_mat.hpp"
#include "glm/glm/detail/type_vec.hpp"
#include "shader_s.hpp"
#include <iostream>
#include <regex>
#include <sys/types.h>
#include "stb_image/stb_image.h"
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "camera.hpp"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera;
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

glm::vec3 direction;
float lastX = 400, lastY = 300;
float yaw = -90.0f, pitch = 0.f;
bool firstMouse = true;

float ratio = 0.2;

void processInput(GLFWwindow *window);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouse_callback);  
    
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    
    
    glEnable(GL_DEPTH_TEST);

    //data
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 
        0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, 
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, 
        -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 
        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 
        0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, 
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),    
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), 
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   
        glm::vec3(-1.3f, 1.0f, -1.5f)
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
   
    // positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  

    // texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1); 

    shaderProgram.use();
    shaderProgram.setInt("texture", 0);
    shaderProgram.setInt("texture2", 1);

    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)SCR_WIDTH / float(SCR_HEIGHT), 0.1f, 100.f);
    shaderProgram.setMat4("projection", projection);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        shaderProgram.setFloat("ratio", ratio);

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 

        // main rendering loop
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // camera/view transformation
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);

        glm::mat4 view = camera.GetViewMatrix();
        shaderProgram.setMat4("view", view);

        // render boxes
        glBindVertexArray(VertexArrayObject);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 0.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vertex_buffer_object);
    glDeleteVertexArrays(1, &VertexArrayObject);
    glfwDestroyWindow(window);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window){
    float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        if(ratio<1.0) {ratio += 0.01;} 
        else {ratio=1.0;} 
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if(ratio>0.0)ratio -= 0.01; 
        else {ratio = 0.0;} 
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { camera.ProcessKeyboard(FORWARD, deltaTime); }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { camera.ProcessKeyboard(LEFT, deltaTime); }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { camera.ProcessKeyboard(BACKWARD, deltaTime); }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { camera.ProcessKeyboard(RIGHT, deltaTime); }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { camera.ProcessKeyboard(UP, deltaTime); }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { camera.ProcessKeyboard(DOWN, deltaTime); }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset, true);
}