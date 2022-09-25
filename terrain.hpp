#ifndef TERRAIN_HPP
#define TERRAIN_HPP
#define CHUNKS 1

#include <vector>
#include <list>
#include <array>
#include <iterator>
#include "chunk.hpp"
#include "gradient_field.hpp"

class terrain {

    public:

        terrain(glm :: ivec3 chunk_parameters, glm :: vec3 observer_position);

        void initialise_chunks();
        void initialise_gradients();
        //void initialise_chunk_layout(int chunks_x, int chunks_y);
        void update_scene(glm :: ivec2 position_change);
        void draw();

        float get_terrain_height(int pos_x, int pos_y);
        float perlin_noise(int pos_x, int pos_y);

        int num_chunks;
        int chunks_x;
        int chunks_y;
        int chunk_side_length;
        int chunk_selector_x;
        int chunk_selector_y;

        std :: vector <gradient_field> gradient_fields;
        std :: vector <std :: vector <chunk>> chunks;

};

#endif
