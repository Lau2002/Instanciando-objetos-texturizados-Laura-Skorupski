
#include <iostream>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sprite.h"

const GLint WIDTH = 800, HEIGHT = 600;
glm::mat4 matrix = glm::mat4(1);

void mouse(double mx, double my) {
    double dx = mx - WIDTH / 2;
    double dy = my - HEIGHT / 2;

    matrix = glm::translate(glm::mat4(1), glm::vec3(dx, dy, 0));
}


int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

#pragma region Basic Setup
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Aplicacao de Texturas - Laura Skorupski", nullptr, nullptr);


    if (window == nullptr) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD." << std::endl;
        return EXIT_FAILURE;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#pragma endregion

    const char* vertex_shader =
        "#version 410\n"
        "layout ( location = 0 ) in vec3 vPosition;"
        "layout ( location = 1 ) in vec3 vColor;"
        "layout ( location = 2 ) in vec2 vTexture;"
        "uniform mat4 proj;"
        "uniform mat4 matrix;"
        "out vec2 text_map;"
        "out vec3 color;"
        "void main() {"
        "    color = vColor;"
        "    text_map = vTexture;"
        "    gl_Position = proj * matrix * vec4 ( vPosition, 1.0);"
        "}";

    const char* fragment_shader =
        "#version 410\n"
        "in vec2 text_map;"
        "in vec3 color;"
        "uniform sampler2D basic_texture;"
        "out vec4 frag_color;"
        "void main(){"
        "   frag_color = texture(basic_texture, text_map);"
        "}";

    int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    int shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);


    GLfloat vertices[] = {
        // Positions           // Colors          // Texture Coords
        0.0f,   0.0f,  0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  // Bottom-left
        WIDTH,  0.0f,  0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // Bottom-right
        WIDTH, HEIGHT, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // Top-right
        0.0f,  HEIGHT, 0.0f,   1.0f, 1.0f, 0.0f,  0.0f, 1.0f   // Top-left
    };


    GLfloat vertices2[] = {
        // Positions            // Colors           // Texture Coords
        50.0f,  360.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // Bottom-left
        150.0f, 360.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // Bottom-right
        50.0f,  460.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,  // Top-left
        150.0f, 460.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f   // Top-right
    };

    GLfloat vertices3[] = {
        // Positions            // Colors           // Texture Coords
        450.0f, 360.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // Bottom-left
        550.0f, 360.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // Bottom-right
        450.0f, 460.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,  // Top-left
        550.0f, 460.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f   // Top-right
    };

    GLfloat vertices4[] = {
        // Positions            // Colors           // Texture Coords
        650.0f, 360.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // Bottom-left
        750.0f, 360.0f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,  // Bottom-right
        650.0f, 460.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,  // Top-left
        750.0f, 460.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f   // Top-right
    };

    GLfloat scale = 3.0f; 

    GLfloat vertices5[] = {
        // Positions                             // Colors           // Texture Coords
        60.0f  *  scale, 54.0f * scale, 0.0f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // Bottom-left
        160.0f *  scale, 54.0f * scale, 0.0f,    1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom-right
        60.0f  *  scale, 154.0f * scale, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // Top-left
        160.0f *  scale, 154.0f * scale, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f  // Top-right
    };

    GLfloat scale2 = 1.8f;

    GLfloat vertices6[] = {
        // Positions                             // Colors           // Texture Coords
        280.0f * scale2, 30.0f * scale2, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // Bottom-left
        380.0f * scale2, 30.0f * scale2, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom-right
        280.0f * scale2, 130.0f * scale2, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // Top-left
        380.0f * scale2, 130.0f * scale2, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f  // Top-right
    };

    glm::mat4 proj = glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);

    Sprite sprite1(vertices, sizeof(vertices) / sizeof(vertices[0]), "background.png", proj);
    Sprite sprite2(vertices2, sizeof(vertices2) / sizeof(vertices2[0]), "Anchor.png", proj);
    Sprite sprite3(vertices3, sizeof(vertices3) / sizeof(vertices3[0]), "Chest.png", proj);
    Sprite sprite4(vertices4, sizeof(vertices4) / sizeof(vertices4[0]), "Pearl.png", proj);
    Sprite sprite5(vertices5, sizeof(vertices5) / sizeof(vertices5[0]), "Mast.png", proj);
    Sprite sprite6(vertices6, sizeof(vertices6) / sizeof(vertices6[0]), "Mermaid.png", proj);


    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

#pragma region Input Handling

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
#pragma endregion

        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int screenWidth, screenHeight;
        glfwGetWindowSize(window, &screenWidth, &screenHeight);
        glViewport(0, 0, screenWidth, screenHeight);

        glUseProgram(shader_programme);
        glUniformMatrix4fv(glGetUniformLocation(shader_programme, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
        glUniformMatrix4fv(glGetUniformLocation(shader_programme, "matrix"), 1, GL_FALSE, glm::value_ptr(matrix));

        sprite1.render(true);
        sprite2.render(false);
        sprite3.render(false);
        sprite4.render(false);
        sprite5.render(false);
        sprite6.render(false);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return EXIT_SUCCESS;
}
