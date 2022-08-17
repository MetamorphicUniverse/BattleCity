#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer/Shader_Program.h"
#include "Resources/ResourcesManager.h"


GLfloat point[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat color[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

// Vertex shader
const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 1.0);"
"}";

// Fragment shader
const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color, 1.0);"
"}";

// GLFW Mine Window size
int g_windowSizeX = 640;
int g_windowSizeY = 480;

//### Callbacks:

// GLFW Window resize callback
void glfwWindowSizeCallback(GLFWwindow* window, int width, int height) {
    g_windowSizeX = width;
    g_windowSizeY = height;
    glViewport(0, 0, g_windowSizeX, g_windowSizeY);
}

// GLFW Key callback
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

//#############################################################################
//                             /\  /\   /_\  | |\ |                     *******
//                            /  \/  \ /   \ | | \|                     *******
//#############################################################################
std::string gamePath;
int main(int argc, char** argv)
{
    if (argc > 0) {
        std::cout << argv[0] << std::endl;
        gamePath = argv[0];
    }
    setlocale(0, "");


    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "GLFWInit failed!!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window;
    window = glfwCreateWindow(g_windowSizeX, g_windowSizeY, "Battle City", nullptr, nullptr);
    if (!window)
    {
        std::cout << "glfwCreateWindow() failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
    glfwSetKeyCallback(window, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Initialization of GLAD
    if (!gladLoadGL())
    {
        std::cout << "Error! Can't load GLAD!" << std::endl;
        return 1;
    }

    //std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;


    glClearColor(0.5, 1, 0.8, 1);

    ////### Create and compile shaders programs:
    //
    //// Vertex sader
    //GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vs, 1, &vertex_shader, nullptr);
    //glCompileShader(vs);

    //// Fragment shader
    //GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fs, 1, &fragment_shader, nullptr);
    //glCompileShader(fs);

    //// Attaching shaders programs to drivers
    //GLuint shader_program = glCreateProgram();
    //glAttachShader(shader_program, vs);
    //glAttachShader(shader_program, fs);
    //glLinkProgram(shader_program);

    //glDeleteShader(vs);
    //glDeleteShader(fs);

    {
        ResourcesManager resourceManager(gamePath);
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.vert", "res/shaders/fragment.frag");
        if (!pDefaultShaderProgram) {
            std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
            return -1;
        }
        /*std::string vertexShader(vertex_shader);
        std::string fragmentShader(fragment_shader);

        Renderer::Shader_Program alfa(vertex_shader, fragment_shader);
        if (!alfa.IsCompiled())
        {
            std::cerr << "Error. Can't create shader program" << std::endl;
            return -1;
        }*/

        //### Crate GL Virtual Buffer Objects:
        // Vertex virtual bsuffer object
        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        // Color Virtual Buffer Object
        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

        // Virtual Arrays Object
        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);


            pDefaultShaderProgram->use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);




            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }

    glfwTerminate();
	return 0;
}