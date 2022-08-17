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

    void setup_camera();
    void setup_lights();
    void setup_terrain();
    void setup_shaders();
    void setup_states();
    void setup_scene();
    void setup_static_uniforms();
    void setup_dynamic_uniforms();


    void render_scene();


    shader* happy_shader;
    //shader* unhappy_shader;
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
