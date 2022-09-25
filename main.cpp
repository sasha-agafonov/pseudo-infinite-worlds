#define GLFW_INCLUDE_NONE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <GL/glu.h>
#include <iostream>
#include <math.h>
#include "renderer.hpp"
#include "extern.hpp"


int extern_width = 640;
int extern_height = 480;
int extern_polygon_mode = FILL;
int extern_movement_mode = FULL_STOP;
int extern_anti_aliasing = MSAA_4X;
int extern_transformation = ROTATE;
int extern_cull_face = FRONT;


void GLAPIENTRY MessageCallback(GLenum source,
                                GLenum type,
                                GLuint id,
                                GLenum severity,
                                GLsizei length,
                                const GLchar* message,
                                const void* userParam) {

  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

    glViewport(0, 0, width, height);

    extern_width = width;
    extern_height = height;

    std :: cout << "framebuffer callback!" << std :: endl;
}


void error_callback(int error, const char* description) {
    std :: cerr << "error callback!" << std :: endl;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    // exit
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);

    // polygon mode
    if (key == GLFW_KEY_F && action == GLFW_PRESS && extern_polygon_mode == FILL) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        extern_polygon_mode = WIREFRAME;
    }
    else if (key == GLFW_KEY_F && action == GLFW_PRESS && extern_polygon_mode == WIREFRAME) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        extern_polygon_mode = FILL;
    }

    // movement mode
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && extern_movement_mode == AUTO_BACKWARDS) extern_movement_mode = FULL_STOP;
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && extern_movement_mode == FULL_STOP) extern_movement_mode = AUTO_FORWARD;
    else if (key == GLFW_KEY_SPACE && action == GLFW_PRESS && extern_movement_mode == AUTO_FORWARD) extern_movement_mode = AUTO_BACKWARDS;

    // anti-aliasing
    if (key == GLFW_KEY_R && action == GLFW_PRESS && extern_anti_aliasing == OFF) {
        extern_anti_aliasing = MSAA_4X;
        glEnable(GL_MULTISAMPLE);
    }
    else if (key == GLFW_KEY_R && action == GLFW_PRESS && extern_anti_aliasing == MSAA_4X) {
        extern_anti_aliasing = OFF;
        glDisable(GL_MULTISAMPLE);
    }

    // transformations
    if (key == GLFW_KEY_E && action == GLFW_PRESS && extern_transformation == NONE) extern_transformation = ROTATE;
    else if (key == GLFW_KEY_E && action == GLFW_PRESS && extern_transformation == ROTATE) extern_transformation = NONE;

    // cull face
    if (key == GLFW_KEY_C && action == GLFW_PRESS && extern_cull_face == DISABLED) {
        extern_cull_face = FRONT;
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
    }
    else if (key == GLFW_KEY_C && action == GLFW_PRESS && extern_cull_face == FRONT) {
        extern_cull_face = BACK;
        //glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    }
    else if (key == GLFW_KEY_C && action == GLFW_PRESS && extern_cull_face == BACK) {
        extern_cull_face = DISABLED;
        glDisable(GL_CULL_FACE);
        //glCullFace(GL_FRONT);
    }
}


int main(void) {

    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(640, 480, "ihatewindowssomuch", NULL, NULL);
    if (!window) exit(EXIT_FAILURE);

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    renderer* bad_renderer = new renderer(window);

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    bad_renderer -> setup_scene();
    bad_renderer -> render_scene();

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
    return 0;
}
