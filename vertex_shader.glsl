#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;

out vec3 abnormal;
out vec3 fragment_position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {

    gl_Position = projection * view * model * vec4(pos, 1.f);
    fragment_position = vec3(model * vec4(pos, 1.f));
    vec4 bad_normal = model * vec4(normal, 1.f);
    abnormal = vec3(bad_normal.x, bad_normal.y, bad_normal.z);
}
