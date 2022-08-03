#define GL_GLEXT_PROTOTYPES

#include "renderer.hpp"
#include "shader.hpp"
#include "stb_image.h"
#include "extern.hpp"
#include <iostream>
#include <math.h>
#include <glm/ext.hpp>

#define CHUNKS_X 5
#define CHUNKS_Y 5
#define CHUNK_SIDE_LENGTH 86


renderer :: renderer(GLFWwindow* window) {
    this -> window = window;
}


void renderer :: setup_scene() {

    happy_shader = new shader("./vertex_shader.glsl", "./fragment_shader.glsl");
    light_shader = new shader("./light_vertex_shader.glsl", "./light_fragment_shader.glsl");

    glm :: ivec3 chunk_parameters(CHUNKS_X, CHUNKS_Y, CHUNK_SIDE_LENGTH);
    glm :: vec3 look_from((CHUNKS_X ) * (CHUNK_SIDE_LENGTH / 2.f), 40.f, 1.5 * (CHUNKS_Y ) * (CHUNK_SIDE_LENGTH / 2.f));
    glm :: vec3 look_at((CHUNKS_X ) * (CHUNK_SIDE_LENGTH / 2.f), 40.f, 0.f);
    glm :: vec3 look_up(0.f, 1.f, 0.f);

    polite_terrain = new terrain(chunk_parameters, glm :: vec3 (0.f, 0.f ,0.f));
    happy_camera = new camera(look_from, look_at, look_up, CHUNK_SIDE_LENGTH);

    glm :: vec3 sun_position = happy_camera -> look_from + glm :: vec3(48.f, 32.f, 128.f);

    friendly_sun = new sun(sun_position,
                           // sun colour
                           glm :: vec3(1.f, 0.8f, 1.f),
                           // light colour
                           glm :: vec3(1.f, 1.f, 1.f),
                           // light direction
                          -sun_position);



    happy_camera -> polite_terrain = polite_terrain;

    // glGenVertexArrays(1, &vao);
    // glBindVertexArray(vao);
    // // create vbo
    // glGenBuffers(1, &vbo);
    // // select vbo
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // // load vbo
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vex), vex, GL_STATIC_DRAW);
    //
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
    // glEnableVertexAttribArray(0);
    //
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    // light cube
    // glGenVertexArrays(1, &light_vao);
    // glBindVertexArray(light_vao);
    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    glEnable(GL_MULTISAMPLE);

}

void renderer :: render_scene() {

    glClearColor(0.6f, 0.7f, 0.8f, 0.8f);
    glEnable(GL_DEPTH_TEST);
    //glShadeModel(GL_FLAT);
    // glEnable(GL_NORMALIZE);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);

    happy_shader -> use_program();

    unsigned int uniform_projection = glGetUniformLocation(happy_shader -> program_id, "projection");
    unsigned int uniform_view = glGetUniformLocation(happy_shader -> program_id, "view");
    unsigned int uniform_model = glGetUniformLocation(happy_shader -> program_id, "model");
    unsigned int uniform_light_colour = glGetUniformLocation(happy_shader -> program_id, "light_colour");
    unsigned int uniform_object_colour = glGetUniformLocation(happy_shader -> program_id, "object_colour");
    unsigned int uniform_light_position = glGetUniformLocation(happy_shader -> program_id, "light_position");
    unsigned int uniform_view_position = glGetUniformLocation(happy_shader -> program_id, "view_position");

    glm :: mat4 model_mx;
    glm :: mat4 view_mx;
    glm :: mat4 projection_mx;

    glm :: vec3 light_pos(2.f, 0.f, 4.f);
    glm :: vec3 light_colour(1.0f, 1.0f, 1.0f);
    glm :: vec3 object_colour(0.1f, 0.5f, 0.2f);

    glUniform3fv(uniform_light_colour, 1, glm :: value_ptr(light_colour));
    glUniform3fv(uniform_object_colour, 1, glm :: value_ptr(object_colour));

    light_shader -> use_program();

    unsigned int uniform_projection_light = glGetUniformLocation(light_shader -> program_id, "projection");
    unsigned int uniform_view_light = glGetUniformLocation(light_shader -> program_id, "view");
    unsigned int uniform_model_light = glGetUniformLocation(light_shader -> program_id, "model");

    float saved_time;

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glm :: vec3 view_position = happy_camera -> look_from;

        float current_time = glfwGetTime() * 42;
        //model_mx = glm :: rotate(model_mx, current_time * glm :: radians(50.0f), glm :: vec3(0.f, 1.f, 0.f));

        if (extern_movement_mode == AUTO_FORWARD) view_mx = happy_camera -> auto_move_forward(current_time);
        else if (extern_movement_mode == AUTO_BACKWARDS) view_mx = happy_camera -> auto_move_backwards(current_time);
        else view_mx = happy_camera -> get_view_mx(current_time);

        //view_mx = glm :: translate(view_mx ,glm :: vec3(0.f, 0.f, -40.f));
        happy_camera -> process_position();

        model_mx = glm :: mat4(1.f);
        //model_mx = glm :: translate(model_mx, polite_terrain -> chunk_translation);

        happy_shader -> use_program();

        projection_mx = glm :: mat4(1.f);
        projection_mx = glm :: perspective(glm :: radians(45.f), (float)extern_width / (float)extern_height, 0.1f, 800.f);

        // glm :: vec3 sun_position = glm ::vec3(0.f, 0.f, -22.f);
        glm :: vec3 sun_position = view_position;
        sun_position.x += 48.f;
        sun_position.y += 32.f;
        sun_position.z -= 128.f;

        glUniform3fv(uniform_light_position, 1, glm :: value_ptr(sun_position));
        glUniform3fv(uniform_view_position, 1, glm :: value_ptr(view_position));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm :: value_ptr(model_mx));
        glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm :: value_ptr(view_mx));
        glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm :: value_ptr(projection_mx));



        for (int i = 0; i < polite_terrain -> chunks.size(); i++) {
            for (int k = 0; k < polite_terrain -> chunks[0].size(); k++) {
                polite_terrain -> chunks[i][k].draw();
            }
        }


        //
        // {
        //     glBindVertexArray(polite_terrain -> chunks[i].vao);
        //     glDrawElements(GL_TRIANGLES, polite_terrain -> chunks[i].chunk_indices.size(), GL_UNSIGNED_INT, 0);
        // }



        light_shader -> use_program();

        // model_mx = glm :: mat4(1.f);
        // model_mx = glm :: translate(model_mx, sun_position);
        // model_mx = glm :: translate(model_mx, glm :: vec3(2.f, 2.f, 2.f));
        // model_mx = glm :: scale(model_mx, glm :: vec3(8.f, 8.f, 8.f));
        //
        // glUniformMatrix4fv(uniform_model_light, 1, GL_FALSE, glm :: value_ptr(model_mx));
        // glUniformMatrix4fv(uniform_view_light, 1, GL_FALSE, glm :: value_ptr(view_mx));
        // glUniformMatrix4fv(uniform_projection_light, 1, GL_FALSE, glm :: value_ptr(projection_mx));
        //
        // glBindVertexArray(light_vao);
        // glDrawArrays(GL_TRIANGLES, 0, 36);




        // light_shader -> use_program();

        model_mx = glm :: mat4(1.f);
        model_mx = glm :: translate(model_mx, sun_position);
        // model_mx = glm :: scale(model_mx, glm :: vec3(8.f, 8.f, 8.f));

        glUniformMatrix4fv(uniform_model_light, 1, GL_FALSE, glm :: value_ptr(model_mx));
        glUniformMatrix4fv(uniform_view_light, 1, GL_FALSE, glm :: value_ptr(view_mx));
        glUniformMatrix4fv(uniform_projection_light, 1, GL_FALSE, glm :: value_ptr(projection_mx));

        glBindVertexArray(friendly_sun -> vao);
        glDrawElements(GL_TRIANGLES, friendly_sun -> sun_indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
