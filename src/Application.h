#pragma once

void ErrorHandleShader(GLuint& shader);
bool IsKeyPressed(GLFWwindow* window, int key);


std::string ParseShaderFromFile(const char* filename);

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}

// CAMERA
struct vec2
{
    double x, y;

    vec2(double x, double y)
        : x(x), y(y) {}

    void add(const double& x, const double& y)
    {
        this->x += x;
        this->y += y;
    }
};