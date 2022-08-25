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

        std :: vector <std :: vector <gradient>> gradients;

    private:

        void initialise_gradients();

        int start_x;
        int start_y;
        int chunks_in_row;
        int chunk_side_length;
        int frequency;
        float amplitude;
};


#endif
