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

    while (pos_y <= chunks_in_row * chunk_side_length) {

        std :: vector <gradient> gradient_row;

        while (pos_x <= chunks_in_row * chunk_side_length) {
            gradient_row.emplace_back(pos_y + start_y, pos_x + start_x);
            pos_x += frequency;
        }

        gradients.push_back(gradient_row);
        pos_y += frequency;
    }

    // 
    // for (int i =0; i < gradients[0].size(); i++) {
    //     for (int k = 0; k < gradients[0].size(); k++) {
    //
    //         std :: cout << gradients[i][k].position.x << " ";
    //         std :: cout << gradients[i][k].position.y << std :: endl;
    //     }
    // }
}



void gradient_field :: shift_up() {

}


void gradient_field :: shift_down() {

}


void gradient_field :: shift_left() {

}


void gradient_field :: shift_right() {

}
