#define GL_GLEXT_PROTOTYPES
#define RINGS 32
#define SEGMENTS 32
#define RADIUS 4

#include "sun.hpp"
#include <iostream>
#include <math.h>
#include <GLFW/glfw3.h>


sun :: sun(glm :: vec3 sun_position,  glm :: vec3 sun_colour,    glm :: vec3 light_direction,
           glm :: vec3 light_ambient, glm :: vec3 light_diffuse, glm :: vec3 light_specular)
           : light(light_direction, light_ambient, light_diffuse, light_specular) {

    this -> sun_position = sun_position;
    this -> sun_colour = sun_colour;

    build_vertices();
    build_indices();
    set_buffers();
}


void sun :: build_vertices() {

    glm :: vec3 vertex_position;
    glm :: vec3 vertex_normal;

    float ring_angle, segment_angle;
    float pi = glm :: pi <float> ();

    for (int ring = 0; ring <= RINGS; ring++) {

        ring_angle = pi / 2 - ring * (pi / RINGS);

        for (int segment = 0; segment <= SEGMENTS; segment++) {

            segment_angle = segment * (2 * pi / SEGMENTS);

            vertex_position.x = RADIUS * cosf(segment_angle) * cosf(ring_angle);
            vertex_position.y = RADIUS * sinf(segment_angle) * cosf(ring_angle);
            vertex_position.z = RADIUS * sinf(ring_angle);

            sun_vertices.push_back(vertex_position.x);
            sun_vertices.push_back(vertex_position.y);
            sun_vertices.push_back(vertex_position.z);

            vertex_normal = glm :: normalize(vertex_position);

            sun_vertices.push_back(vertex_normal.x);
            sun_vertices.push_back(vertex_normal.y);
            sun_vertices.push_back(vertex_normal.z);

        }
    }
}


void sun :: build_indices() {

    int alpha, beta;

    for (int ring = 0; ring < RINGS; ring++) {
        alpha = ring * (SEGMENTS + 1);
        beta = alpha + SEGMENTS + 1;

        for (int segment = 0; segment < SEGMENTS; segment++, alpha++, beta++) {

            if (ring != 0) {
                sun_indices.push_back(alpha);
                sun_indices.push_back(beta);
                sun_indices.push_back(alpha + 1);
            }

            if (ring != (RINGS - 1)) {
                sun_indices.push_back(alpha + 1);
                sun_indices.push_back(beta);
                sun_indices.push_back(beta + 1);
            }
        }
    }
}


void sun :: set_buffers() {

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sun_vertices.size() * sizeof(float), sun_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sun_indices.size() * sizeof(unsigned int), sun_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    // normals not needed at this stage
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}
