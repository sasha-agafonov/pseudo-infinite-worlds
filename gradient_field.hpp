#ifndef GRADIENT_FIELD_HPP
#define GRADIENT_FIELD_HPP

#include "gradient.hpp"
#include <vector>

class gradient_field {

    public:

        gradient_field(int start_x, int start_y, int chunks_in_row, int chunk_side_length, int frequency, float amplitude);

        void shift_up();
        void shift_down();
        void shift_left();
        void shift_right();

        float get_height(int pos_x, int pos_y);
        float perlin_noise(float point_x, float point_y);
        float smoothstep(float vec_1, float vec_2, float weight);
        float distance_scalar_product(int ix, int iy, float x, float y);

        float map_to_field_x(int point);
        float map_to_field_y(int point);
        // float map_y(int point);

        int positive_mod(int dividend, int divisor);

        std :: vector <std :: vector <gradient>> gradients;

    private:

        void initialise_gradients();

        int field_side_length;
        int start_x;
        int start_y;
        int chunks_in_row;
        int chunk_side_length;
        int frequency;
        float amplitude;
};


#endif
