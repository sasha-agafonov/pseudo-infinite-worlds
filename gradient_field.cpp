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

    field_side_length = field_len;
}


float gradient_field :: get_height(int pos_x, int pos_y) {

    float mapped_x = map_to_field_x(pos_x);
    float mapped_y = map_to_field_y(pos_y);

    //std :: cout << "pos_X: " <<mapped_x << " pos_y: " << mapped_y << std :: endl;

    //std :: cout << "perlin: " << amplitude * perlin_noise(mapped_x, mapped_y) << std :: endl;
    //return amplitude * perlin_noise(mapped_x, mapped_y);
    return 0;
}


float gradient_field :: smoothstep(float vec_1, float vec_2, float weight) {

    if (weight < 0.f) return vec_1;
    if (weight > 1.f) return vec_2;

    return (vec_2 - vec_1) * ((weight * (weight * 6 - 15) + 10) * weight * weight * weight) + vec_1;
}


float gradient_field :: distance_scalar_product(int ix, int iy, float x, float y) {

    // distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    glm :: vec2 gradient = gradients[ix][iy].component;

    // scalar product
    return (dx * gradient.x + dy * gradient.y);
}


float gradient_field :: perlin_noise(float point_x, float point_y) {

    int x0 = (int)floor(point_x);
    int x1 = x0 + 1;
    int y0 = (int)floor(point_y);
    int y1 = y0 + 1;

    float sx = point_x - (float)x0;
    float sy = point_y - (float)y0;
    float n0, n1, ix0, ix1;

    n0 = distance_scalar_product(x0, y0, point_x, point_y);
    n1 = distance_scalar_product(x1, y0, point_x, point_y);
    ix0 = smoothstep(n0, n1, sx);

    n0 = distance_scalar_product(x0, y1, point_x, point_y);
    n1 = distance_scalar_product(x1, y1, point_x, point_y);
    ix1 = smoothstep(n0, n1, sx);

    return smoothstep(ix0, ix1, sy);

}



float gradient_field :: map_to_field_x(int point) {
    return (float)(point - start_x) / (float)field_side_length;

    // int mapped_pos = positive_mod(point, field_side_length);
    // mapped_pos /= field_side_length;
    // std :: cout << mapped_pos << "   <---pos" << std :: endl;
    // return (float)mapped_pos * ((float)field_side_length / (float)frequency);
    // potentialy simpler: return mapped_pos / (float) freq

}


float gradient_field :: map_to_field_y(int point) {
    return (float)(point - start_y) / (float)field_side_length;
    // int mapped_pos = positive_mod(point, field_side_length);
    // mapped_pos /= field_side_length;
    // std :: cout << mapped_pos << "   <---pos" << std :: endl;
    // return (float)mapped_pos * ((float)field_side_length / (float)frequency);
    // potentialy simpler: return mapped_pos / (float) freq

}



int gradient_field :: positive_mod(int dividend, int divisor) {
    return (dividend % divisor + divisor) % divisor;
}

// todo
void gradient_field :: shift_up() {}
void gradient_field :: shift_down() {}
void gradient_field :: shift_left() {}
void gradient_field :: shift_right() {}
