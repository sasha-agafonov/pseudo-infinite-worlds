#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <GLFW/glfw3.h>
#include "shader.hpp"
#include "camera.hpp"
#include "sun.hpp"
#include "terrain.hpp"

class renderer {

public:
    renderer(GLFWwindow* window);

    void setup_scene();
    void render_scene();

    shader* happy_shader;
    shader* light_shader;

    camera* happy_camera;
    sun* friendly_sun;
    terrain* polite_terrain;

    GLFWwindow* window;
    //unsigned int  vsh, fsh, shader_pro;
    unsigned int light_vao;
    unsigned int* texture_input;
    int width, height;
};

#endif
