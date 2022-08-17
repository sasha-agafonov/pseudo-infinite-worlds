#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

out vec3 bnormal;
out vec3 ragment_position;
out vec3 vex_pos;
//out vec3 vex_colour;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {

    gl_Position = projection * view * model * vec4(pos, 1.f);
    ragment_position = vec3(model * vec4(pos, 1.f));
    vec4 bad_normal = model * vec4(normal, 1.f);
    bnormal = vec3(bad_normal.x, bad_normal.y, bad_normal.z);
    vex_pos = pos;
}


// vec3 interpolate_height_colour(float height) {
//
//     float color_1 = (0.725 - 0.227) * height / (5) + 0.227;
//     float color_2 = (0.662 - 0.552) * height / (5) + 0.552;
//     float color_3 = (0.592 - 0.321) * height / (5) + 0.321;
//
//     return vec3(color_1, color_2, color_3);
// }
