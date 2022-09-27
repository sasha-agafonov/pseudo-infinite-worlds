#include "gradient_field.hpp"
#include <iostream>

gradient_field :: gradient_field(int start_x, int start_y, int chunks_in_row, int chunk_side_length, int frequency, float amplitude) {

    this -> field_start_x = start_x;
    this -> field_start_y = start_y;
    this -> chunk_side_len = chunk_side_length;
    this -> chunks_per_row = chunks_in_row;
    this -> frequency = frequency;
    this -> amplitude = amplitude;

    initialise_gradients();
    //print_field();
}

// rwrtdis
void gradient_field :: initialise_gradients() {

    int terrain_len = chunks_per_row * chunk_side_len;
    // int field_len = terrain_len /

    for (int pos_x = 0; pos_x <= terrain_len + frequency; pos_x += frequency) {

        std :: vector <gradient> gradient_row;

        for (int pos_y = 0; pos_y <= terrain_len + frequency; pos_y += frequency) {
            gradient_row.emplace_back(field_start_y + pos_y, field_start_x + pos_x);
        }

        gradients.push_back(gradient_row);
    }

    field_side_len = gradients[0][gradients.size() - 1].position.x - gradients[0][0].position.x;
    gradients_per_side = gradients.size();
    //
    // if (gradients.size() < 2 || gradients[0].size() < 2) {
    //
    // }

    // = chunks_in_row * chunk_side_length;

    // while (pos_x <= chunks_in_row * chunk_side_length || side_gradients < 2) {
    //
    //     side_gradients++;
    //
    //     std :: vector <gradient> gradient_row;
    //
    //     while (pos_y <= chunks_in_row * chunk_side_length || side_gradients < 2) {
    //
    //         gradient_row.emplace_back(start_y + pos_y, start_x + pos_x);
    //         pos_y += frequency;
    //     }
    //
    //     gradients.push_back(gradient_row);
    //     pos_x += frequency;
    //     pos_y = 0;
    // }
}



void gradient_field :: print_field() {


    std :: cout << "estimated terrain len size: " << chunks_per_row * chunk_side_len << " x " << chunks_per_row * chunk_side_len  << std :: endl;
    std :: cout << "estimated g-field size: " << gradients.size() << " x " << gradients[0].size() << std ::endl;
    std :: cout << "estimated g-field len: " << gradients[0][gradients.size() - 1].position.x - gradients[0][0].position.x << std :: endl;
    std :: cout << "computed g-field len: " << field_side_len << std :: endl;

    for (int i = 0; i < gradients.size(); i++) {
        for (int k = 0; k < gradients[0].size(); k++) {
            std :: cout << "inx (" << i << ", " << k << ") :: ";
            std :: cout << "val (" << gradients[i][k].component.x << ", " << gradients[i][k].component.y << ") :: ";
            std :: cout << "pos (" << gradients[i][k].position.x << ", " << gradients[i][k].position.y << ")  ";
        }   std :: cout << std :: endl;
    }
}


float gradient_field :: get_height(int pos_x, int pos_y) {

    float mapped_x = map_to_field_x(pos_x);
    float mapped_y = map_to_field_y(pos_y);

    //std :: cout << "pos_X: " <<mapped_x << " pos_y: " << mapped_y << std :: endl;
    //std :: cout << "g field size: " << gradients.size() << " x " << gradients[0].size() << std :: endl;
    //std :: cout << "perlin: " << amplitude * perlin_noise(mapped_x, mapped_y) << std :: endl;
    return amplitude * perlin_noise(mapped_x, mapped_y);
    //return 0;
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
    point = positive_mod(point, field_side_len);
    return (float)(point - field_start_x) / (float)field_side_len * (gradients_per_side - 1);

    // int mapped_pos = positive_mod(point, field_side_length);
    // mapped_pos /= field_side_length;
    // std :: cout << mapped_pos << "   <---pos" << std :: endl;
    // return (float)mapped_pos * ((float)field_side_length / (float)frequency);
    // potentialy simpler: return mapped_pos / (float) freq

}


float gradient_field :: map_to_field_y(int point) {
    point = positive_mod(point, field_side_len);
    return (float)(point - field_start_y) / (float)field_side_len * (gradients_per_side - 1);
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
