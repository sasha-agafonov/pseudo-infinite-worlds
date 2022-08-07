#define GL_GLEXT_PROTOTYPES

#include "renderer.hpp"
#include "shader.hpp"
#include "stb_image.h"
#include "extern.hpp"
#include <iostream>
#include <math.h>
#include <glm/ext.hpp>
#include <iterator>

#define CHUNKS_X 5
#define CHUNKS_Y 5
#define CHUNK_SIDE_LENGTH 50


renderer :: renderer(GLFWwindow* window) {
    this -> window = window;
}


void renderer :: setup_scene() {

    setup_shaders();
    setup_terrain();
    setup_camera();
    setup_lights();
    setup_states();

}



void renderer :: setup_camera() {

    glm :: vec3 look_from((CHUNKS_X ) * (CHUNK_SIDE_LENGTH / 2.f), 30.f, (CHUNKS_Y ) * (CHUNK_SIDE_LENGTH / 2.f));
    glm :: vec3 look_at((CHUNKS_X ) * (CHUNK_SIDE_LENGTH / 2.f), 30.f, 0.f);
    glm :: vec3 look_up(0.f, 1.f, 0.f);
    happy_camera = new camera(look_from, look_at, look_up, CHUNK_SIDE_LENGTH);
    happy_camera -> polite_terrain = polite_terrain;

}


void renderer :: setup_terrain() {

    polite_terrain = new terrain(glm :: ivec3(CHUNKS_X, CHUNKS_Y, CHUNK_SIDE_LENGTH), glm :: vec3 (0.f, 0.f ,0.f));

}


void renderer :: setup_states() {

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    glClearColor(0.6f, 0.8f, 0.8f, 1.f);

}


void renderer :: setup_lights() {

    glm :: vec3 sun_position = happy_camera -> look_from + glm :: vec3(48.f, 32.f, 128.f);

                           // sun position, sun colour, light direction
    friendly_sun = new sun(sun_position, glm :: vec3(1.f, 0.8f, 1.f), - sun_position,
                           // ambient light, diffuse light, specular light
                           glm :: vec3(1.f, 1.f, 1.f), glm :: vec3(1.f, 1.f, 1.f), glm :: vec3(1.f, 1.f, 1.f));

}


void renderer :: setup_shaders() {

    happy_shader = new shader("./vertex_shader.glsl", "./geometry_shader.glsl", "./fragment_shader.glsl");
    light_shader = new shader("./light_vertex_shader.glsl", "./light_fragment_shader.glsl");
}


void renderer :: render_scene() {

    happy_shader -> use_program();

    unsigned int uniform_projection = glGetUniformLocation(happy_shader -> program_id, "projection");
    unsigned int uniform_view = glGetUniformLocation(happy_shader -> program_id, "view");
    unsigned int uniform_model = glGetUniformLocation(happy_shader -> program_id, "model");
    //unsigned int uniform_light_colour = glGetUniformLocation(happy_shader -> program_id, "light_colour");
    unsigned int uniform_object_colour = glGetUniformLocation(happy_shader -> program_id, "object_colour");
    //unsigned int uniform_light_position = glGetUniformLocation(happy_shader -> program_id, "light_position");
    unsigned int uniform_view_position = glGetUniformLocation(happy_shader -> program_id, "view_position");


    unsigned int uniform_light_dir = glGetUniformLocation(happy_shader -> program_id, "direction");
    unsigned int uniform_light_amb = glGetUniformLocation(happy_shader -> program_id, "ambient");
    unsigned int uniform_light_diff = glGetUniformLocation(happy_shader -> program_id, "diffuse");
    unsigned int uniform_light_spec = glGetUniformLocation(happy_shader -> program_id, "specular");

    glm :: mat4 model_mx;
    glm :: mat4 view_mx;
    glm :: mat4 projection_mx;

    glm :: vec3 light_pos(2.f, 0.f, 4.f);
    glm :: vec3 light_colour(1.0f, 1.0f, 1.0f);
    glm :: vec3 object_colour(0.1f, 0.5f, 0.2f);

    glm :: vec3 ambient(0.1f, 0.1f, 0.1f);
    glm :: vec3 diffuse(0.4f, 0.4f, 0.4f);
    glm :: vec3 specular(0.6f, 0.6f, 0.6f);
    glm :: vec3 direction(2.f, -1.f, 20.f);


    glUniform3fv(uniform_light_dir, 1, glm :: value_ptr(glm :: vec3(1.f, -1.f, 1.f)));
    glUniform3fv(uniform_light_amb, 1, glm :: value_ptr(ambient));
    glUniform3fv(uniform_light_diff, 1, glm :: value_ptr(diffuse));
    glUniform3fv(uniform_light_spec, 1, glm :: value_ptr(specular));
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

        //glUniform3fv(uniform_light_position, 1, glm :: value_ptr(sun_position));
        glUniform3fv(uniform_view_position, 1, glm :: value_ptr(view_position));
        glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm :: value_ptr(model_mx));
        glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm :: value_ptr(view_mx));
        glUniformMatrix4fv(uniform_projection, 1, GL_FALSE, glm :: value_ptr(projection_mx));

        polite_terrain -> draw();


  //
  //       for(list <list<char *> >::iterator outer=moves.begin();outer!=moves.end();outer++) {
  //
  //           for(list<char *>::iterator inner=outer.begin();inner!=outer.end();inner++)
  //     {
  //
  //     }
  // }


        // for(auto i1 = polite_terrain -> chunks.begin(); i1!=polite_terrain -> chunks.end();i1++)
        // {
        //     // list <int> & list2 = *i1;
        //     for(auto j = list2.begin();j!=list2.end();j++)
        //       {
        //         cout<<*j<<" ";
        //       }
        //     cout<<endl;
        // }

        // for (polite_terrain -> chunks_row  = polite_terrain -> chunks.begin();
        //      polite_terrain -> chunks_row != polite_terrain -> chunks.end();
        //      polite_terrain -> chunks_row ++) {
        //
        //      for (polite_terrain -> chunks_col  = polite_terrain -> chunks_row.begin();
        //           polite_terrain -> chunks_col != polite_terrain -> chunks_row.end();
        //           polite_terrain -> chunks_col ++) {
        //
        //
        //           }
        //      }

        // for (auto i = 0; i < polite_terrain -> chunks.size(); i++) {
        //     for (auto k = 0; k < polite_terrain -> chunks[i].size(); k++) {
        //         k.draw();
        //     }
        // }
        // for (int i = 0; i < polite_terrain -> chunks.size(); i++) {
        //     for (int k = 0; k < polite_terrain -> chunks[i].size(); k++) {
        //         polite_terrain -> chunks[i][k].draw();
        //     }
        // }


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
