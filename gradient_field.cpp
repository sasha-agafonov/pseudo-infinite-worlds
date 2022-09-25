#include "gradient_field.hpp"
#include <iostream>

gradient_field :: gradient_field(int start_x, int start_y, int chunks_in_row, int chunk_side_length, int frequency, float amplitude) {

    this -> start_x = start_x;
    this -> start_y = start_y;
    this -> chunk_side_length = chunk_side_length;
    this -> chunks_in_row = chunks_in_row;
    this -> frequency = frequency;
    this -> amplitude = amplitude;

    initialise_gradients();
}


void gradient_field :: initialise_gradients() {

    int pos_x = 0;
    int pos_y = 0;
    int field_len = chunks_in_row * chunk_side_length + 2 * frequency;

    while (pos_y < field_len) {

        std :: vector <gradient> gradient_row;

        while (pos_x <= field_len) {

            gradient_row.emplace_back(pos_y + start_y, pos_x + start_x);
            pos_x += frequency;
        }

        gradients.push_back(gradient_row);
        pos_y += frequency;
        pos_x = 0;
    }
}


void gradient_field :: shift_up() {
    //for (auto& row : gradients) for (auto& gradient : gradients) gradient.reload();

}


void gradient_field :: shift_down() {

}


void gradient_field :: shift_left() {

}


void gradient_field :: shift_right() {

}
