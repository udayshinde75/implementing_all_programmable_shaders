#include <glad/include/glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <graphics/Shader.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

float triangleData[] = {
   -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 
    0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f 
};

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Implementing all shaders", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize Glad\n";
        glfwTerminate();
        return -1;
    }

    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);
    std::cout << "Width : " << fbWidth << ", Height : " << fbHeight << "\n";

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), reinterpret_cast<void *>(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    Shader shader(
        "/Users/udayshinde/Desktop/OpenGLProjects/implementing_all_programmable_shaders/assets/shaders/vertexShaderSource.glsl",
        "/Users/udayshinde/Desktop/OpenGLProjects/implementing_all_programmable_shaders/assets/shaders/fragmentShaderSource.glsl"
    );

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        process_input(window);
        //glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);

        float time = glfwGetTime();
        GLfloat red[] = {(float)sin(time) * 0.5f + 0.5f, (float)cos(time) * 0.5f + 0.5f, 0.0f, 1.0f};

        glClearBufferfv(GL_COLOR, 0, red);

        shader.Use();
        glBindVertexArray(VAO);

        GLfloat attrib[] = {(float)sin(time) * 0.5f + 0.5f, (float)cos(time) * 0.5f + 0.5f, 0.0f, 0.0f};

        glVertexAttrib4fv(2, attrib);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        std::cout << "ESC pressed\n";
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }   
}