#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <GL/gl.h>

#include <vector>
#include <list>
#include <array>
#include <iterator>

#include "chunk.hpp"
#include "gradient_field.hpp"
#include "dynamic_indices.hpp"

class chunk;

class terrain {

    public:

        terrain(glm :: ivec3 chunk_parameters, glm :: vec3 observer_position);
        terrain(int terrain_side_chunks, int chunk_side_vertices, glm :: vec3 camera_position);

        void update_scene(glm :: ivec2 position_change);
        void draw();

        float get_terrain_height(float pos_x, float pos_y);
        float perlin_noise(float pos_x, float pos_y);
        float fractional_bm(float pos_x, float pos_y);

        int num_chunks;
        int chunks_x;
        int chunks_y;
        int chunk_side_length;


        int terrain_side_chunks;
        int chunk_side_vertices;
        int chunk_selector_x;
        int chunk_selector_y;
        int det_levels;


        //std :: vector <GLuint> element_ids;

        //std :: vector <std :: vector <std ::vector>>> element_buffers;
        std :: vector <gradient_field> gradient_fields;
        std :: vector <std :: vector <chunk>> chunks;


        float get_max_height();
        float get_min_height();

    private:

        void build_chunks();
        void build_gradient_fields();
        void build_indices();
        void set_buffers();

        GLuint vertex_array;
        std :: vector <GLuint> index_buffers;
        std :: vector <std :: vector <std ::vector <GLuint>>> indices;

};

#endif
