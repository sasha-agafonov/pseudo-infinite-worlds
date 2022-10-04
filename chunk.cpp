#define GL_GLEXT_PROTOTYPES
#include "chunk.hpp"
#include "terrain.hpp"
#include <iostream>
#include <GLFW/glfw3.h>

#define GRADIENTS_PER_SIDE 2.f
#define SEED 53122


chunk :: chunk(int chunk_side_vertices, int chunk_start_x, int chunk_start_y, terrain* polite_terrain) {

    this -> vertices_per_side = chunk_side_vertices;
    this -> polite_terrain = polite_terrain;

    build_vertices(chunk_start_x, chunk_start_y);
    build_indices();
    set_buffers();
}



void chunk :: print_info() {

    std :: cout << std :: endl;
    std :: cout << "start.x = " << chunk_start.x << " start.y = " << chunk_start.y << std :: endl;
    std :: cout << "side len = " << (vertices_per_side - 1) << std :: endl;
    std :: cout << "gpos.x = " << global_pos.x << " gpos.y = " << global_pos.y << std :: endl;
    std :: cout << "distance = " << distance;
    std :: cout << "lod = " << lod << std :: endl;

}


void chunk :: build_vertices(int chunk_start_x, int chunk_start_y) {

    this -> chunk_start.x = chunk_start_x;
    this -> chunk_start.y = chunk_start_y;
    this -> global_pos.x = chunk_start.y - ((vertices_per_side - 1) / 2);
    this -> global_pos.y = chunk_start.x - ((vertices_per_side - 1) / 2);

    for (int vertex_y = chunk_start.y; vertex_y < chunk_start.y + vertices_per_side; vertex_y++) {

        for (int vertex_x = chunk_start.x; vertex_x < chunk_start.x + vertices_per_side; vertex_x++) {

            vertices.push_back(vertex_y);
            vertices.push_back(polite_terrain -> get_terrain_height(vertex_y, vertex_x));
            vertices.push_back(vertex_x);

            // normals
            vertices.push_back(0.f);
            vertices.push_back(1.f);
            vertices.push_back(0.f);
        }
    }
}


void chunk :: build_indices() {

    for (int index_y = 0; index_y < vertices_per_side - 1; index_y++) {

        for (int index_x = 0; index_x < vertices_per_side - 1; index_x++) {

            indices.push_back(index_x + (index_y) * vertices_per_side);
            indices.push_back(index_x + (index_y) * vertices_per_side + 1);
            indices.push_back(index_x + (index_y + 1) * vertices_per_side);

            indices.push_back(index_x + (index_y) * vertices_per_side + 1);
            indices.push_back(index_x + (index_y + 1) * vertices_per_side + 1);
            indices.push_back(index_x + (index_y + 1) * vertices_per_side);
        }
    }
}


void chunk :: set_buffers() {

    // generate buffers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // bind vertex array
    glBindVertexArray(vao);

    // bind and initialise vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    // bind and initialise element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // set vertex attributes

    // vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);

    // vertex normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind vertex array
    glBindVertexArray(0);

}


void chunk :: draw() {

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}


void chunk :: update_vertices(int shift_x, int shift_y) {

    vertices.clear();
    build_vertices(chunk_start.x + shift_x, chunk_start.y + shift_y);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    void *vbo_pointer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(vbo_pointer, vertices.data(), sizeof(float) * vertices.size());
    glUnmapBuffer(GL_ARRAY_BUFFER);

}


void chunk :: update_distance(glm :: vec2 observer_pos) {

    distance = glm :: distance(global_pos, observer_pos);

    set_lod();

}


void chunk :: set_lod() {

    if (distance < 0) {
        std :: cerr << "negative distance to one of the chunks detected!" << std :: endl;
        exit(1);
    }

    // 16 * 16 = 256
    // 8 * 8
    // 4 4
    // 2 2
    // 1 1

    if (distance >= 0 && distance < 64) lod = 0;
    else if (distance >= 64 && distance < 256) lod = 1;
    else if (distance >= 256 && distance < 512) lod = 2;
    else if (distance >= 512 && distance < 1024) lod = 3;
    else lod = 4;

}
