#ifndef CHUNK_HPP
#define CHUNK_CPP

#include <vector>
#include <glm/ext.hpp>

class chunk {

    public:

        chunk(int chunk_side_length, int chunk_start_x, int chunk_start_y);

        void update_vertices(int chunk_start_x, int chunk_start_y);
        void build_vertices(int chunk_start_x, int chunk_start_y);
        void build_gradients(int chunk_start_x, int chunk_start_y);
        void build_indices();
        void set_buffers();
        float dotGridGradient(int ix, int iy, float x, float y);

        glm :: vec2 get_gradient(int ,int );
        void draw();
        float perlin_noise(float position_x, float position_y);
        float smoothstep(float vec_1, float vec_2, float weight);


        int vertices_per_side;
        unsigned int vao, vbo, ebo;
        glm :: vec2 chunk_start;
        std :: vector <float> vertices;
        std :: vector <unsigned int> indices;
        std :: vector <std :: vector <glm :: vec2>> gradients;
        std :: vector <std :: vector <glm :: vec2>> gradients_2;

};

#endif
