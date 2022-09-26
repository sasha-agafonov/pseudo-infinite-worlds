#define GL_GLEXT_PROTOTYPES
#include "chunk.hpp"
#include "terrain.hpp"
#include <iostream>
#include <GLFW/glfw3.h>

#define GRADIENTS_PER_SIDE 2.f
#define SEED 53122


chunk :: chunk(int chunk_side_length, int chunk_start_x, int chunk_start_y, terrain* polite_terrain) {

    this -> vertices_per_side = chunk_side_length + 1;
    this -> polite_terrain = polite_terrain;

    build_vertices(chunk_start_x, chunk_start_y);
    build_indices();
    set_buffers();
}


void chunk :: build_vertices(int chunk_start_x, int chunk_start_y) {

    this -> chunk_start.x = chunk_start_x;
    this -> chunk_start.y = chunk_start_y;

    float tp  = 0 ;

    build_gradients(chunk_start.x, chunk_start.y);

    float aligner = (float)(GRADIENTS_PER_SIDE - 1) / (float)(vertices_per_side - 1);

    for (int vertex_y = chunk_start.y; vertex_y < chunk_start.y + vertices_per_side; vertex_y++) {

        for (int vertex_x = chunk_start.x; vertex_x < chunk_start.x + vertices_per_side; vertex_x++) {

            // right-handed from now on
            vertices.push_back(vertex_y);
            //tp = polite_terrain -> some_meth();
            //vertices.push_back(12 *  perlin_noise(vertex_y * aligner, vertex_x * aligner));


            vertices.push_back(polite_terrain -> get_terrain_height(vertex_y, vertex_x));
            //vertices.push_back(0.f);
            vertices.push_back(vertex_x);

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


void chunk :: build_gradients(int position_x, int position_y) {


    int side_length = vertices_per_side - 1;
    float incrementer = (float)(side_length) / (GRADIENTS_PER_SIDE - 1);
    //std :: cout << "inc: " << incrementer << std :: endl;
    std :: vector <glm :: vec2> gradient_row;
    //std :: cout << "gradients:" << std :: endl;

    //std :: vector<T>().swap(gradients);
    gradients.clear();

    for (float gradient_y = chunk_start.y; gradient_y <= chunk_start.y + side_length; gradient_y += incrementer) {

        for (float gradient_x = chunk_start.x; gradient_x <= chunk_start.x + side_length; gradient_x += incrementer) {

            //std :: cout << "(" << gradient_y << ", " << gradient_x << ")";

            //glm :: vec2 test = get_gradient((int)gradient_x, (int)gradient_y);
            gradient_row.push_back(get_gradient((int)gradient_y, (int)gradient_x));


        }
        //std :: cout << std ::endl;

        gradients.push_back(gradient_row);
        //std :: cout << "over " << std :: endl;
    }
    int m = 0;
    for (int i = 0; i < gradients.size(); i++) {
        for (int j = 0; j < gradients[0].size(); j++) {
            m++;
        }
    }
    //std :: cout << "grads per chu: " << m << std ::endl;
    //std :: cout << "hangup " << std :: endl;
}


float chunk :: perlin_noise(float point_x, float point_y) {

    int x0 = (int)floor(point_x);
    int x1 = x0 + 1;
    int y0 = (int)floor(point_y);
    int y1 = y0 + 1;

    float sx = point_x - (float)x0;
    float sy = point_y - (float)y0;
    float n0, n1, ix0, ix1, value;

    n0 = dotGridGradient(x0, y0, point_x, point_y);
    n1 = dotGridGradient(x1, y0, point_x, point_y);
    ix0 = smoothstep(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, point_x, point_y);
    n1 = dotGridGradient(x1, y1, point_x, point_y);
    ix1 = smoothstep(n0, n1, sx);

    value = smoothstep(ix0, ix1, sy);
    return value;

}


float chunk :: smoothstep(float vec_1, float vec_2, float weight) {

    if (weight < 0.f) return vec_1;
    if (weight > 1.f) return vec_2;

    return (vec_2 - vec_1) * ((weight * (weight * 6 - 15) + 10) * weight * weight * weight) + vec_1;
}



float chunk :: dotGridGradient(int ix, int iy, float x, float y) {
    // Get gradient from integer coordinates
    glm :: vec2 gradient = get_gradient(ix, iy);

    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx * gradient.x + dy * gradient.y);
}


glm :: vec2 chunk :: get_gradient(int ix, int iy) {
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; // rotation width
    unsigned a = ix, b = iy;
    a *= 3284157443; b ^= a << s | a >> w-s;
    b *= 1911520717; a ^= b << s | b >> w-s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1));
    glm :: vec2 gradient(cos(random), sin(random));
    return gradient;
}
