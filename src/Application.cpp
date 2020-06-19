#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

#include "Application.h"

#define PRINT(x) std::cout << x << std::endl;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 960, "Mandelbrot C++", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!status)
    {
        PRINT("Error initialising Glad! Status: " << status);
    }

    // During init, enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    float vertices[8] = {
        -1.0f,  1.0f,
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f
    };

    unsigned int vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    unsigned int vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int iboID;
    glGenBuffers(1, &iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    std::string vertexShader = ParseShaderFromFile("assets/shaders/vert.glsl");

    std::string fragmentShader = ParseShaderFromFile("assets/shaders/frag.glsl");

    unsigned int programID = glCreateProgram();
    unsigned int vertShaderObj = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragShaderObj = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vertexSrc = vertexShader.c_str();
    glShaderSource(vertShaderObj, 1, &vertexSrc, nullptr);
    glCompileShader(vertShaderObj);

    ErrorHandleShader(vertShaderObj);

    const char* fragSrc = fragmentShader.c_str();
    glShaderSource(fragShaderObj, 1, &fragSrc, nullptr);
    glCompileShader(fragShaderObj);

    ErrorHandleShader(fragShaderObj);
    
    glAttachShader(programID, vertShaderObj);
    glAttachShader(programID, fragShaderObj);
    glLinkProgram(programID);
    glValidateProgram(programID);
    glUseProgram(programID);

    double basePanningSpeed = 0.0125;
    double currentPanningSpeed = 0.0125;
    double zoomSpeed = 1.05;

    // Uniforms
    const float color = 0.0f;
    int colorLocation = glGetUniformLocation(programID, "u_Color");
    glUniform1fv(colorLocation, 1, &color);

    const float maxIter = 100.0f;
    int iterLocation = glGetUniformLocation(programID, "u_MaxIter");
    glUniform1fv(iterLocation, 1, &maxIter);

    vec2 camera = {
        0.0, 0.0
    };
    int cameraLocation = glGetUniformLocation(programID, "u_CameraPos");
    glUniform2d(cameraLocation, camera.x, camera.y);

    double cameraZoom =  1 / 1.0;
    int cameraZoomLocation = glGetUniformLocation(programID, "u_CameraZoom");
    glUniform1dv(cameraZoomLocation, 1, &cameraZoom);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Camera Movement
        if (IsKeyPressed(window, GLFW_KEY_D)) {
            camera.add(currentPanningSpeed, 0.0);
        }
        if (IsKeyPressed(window, GLFW_KEY_A)) {
            camera.add(-currentPanningSpeed, 0.0);
        }
        if (IsKeyPressed(window, GLFW_KEY_W)) {
            camera.add(0.0, currentPanningSpeed);
        }
        if (IsKeyPressed(window, GLFW_KEY_S)) {
            camera.add(0.0, -currentPanningSpeed);
        }
        if (IsKeyPressed(window, GLFW_KEY_Z)) {
            cameraZoom = cameraZoom * (1 / zoomSpeed); // Update the zoomAmount
            currentPanningSpeed = basePanningSpeed * cameraZoom; // Update camera panning speed
        }
        if (IsKeyPressed(window, GLFW_KEY_X)) {
            cameraZoom = cameraZoom * zoomSpeed; // Update the zoomAmount
            currentPanningSpeed = basePanningSpeed * cameraZoom; // Update camera panning speed
        }

        glClear(GL_COLOR_BUFFER_BIT); // clear the framebuffer

        glUniform2d(cameraLocation, camera.x, camera.y);
        glUniform1dv(cameraZoomLocation, 1, &cameraZoom);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //Draw our square

        glfwSwapBuffers(window); // swap the color buffers
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void ErrorHandleShader(GLuint& shader)
{
    // Error handle vertex shader
    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        GLchar* log = (GLchar*)malloc(length);
        glGetShaderInfoLog(shader, length, &length, log);
        PRINT(log);
        free(log);
        glDeleteShader(shader);
    }
}

std::string ParseShaderFromFile(const char* filename)
{
    std::ifstream in(filename, std::ios::in);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }
    else
    {
        PRINT("Error parsing shader!");
        return NULL;
    }
}

bool IsKeyPressed(GLFWwindow* window, int keycode)
{
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}