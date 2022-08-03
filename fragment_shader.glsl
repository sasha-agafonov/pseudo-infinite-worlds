#version 460 core

out vec4 frag_colour;

in vec3 fragment_position;
in vec3 abnormal;

uniform vec3 view_position;
uniform vec3 light_position;
uniform vec3 light_colour;
uniform vec3 object_colour;

vec3 ambient(float intensity) {
    return intensity * light_colour;
}

vec3 diffuse(float intensity) {
    vec3 diffuse_component = max(dot(normalize(abnormal), normalize(light_position - fragment_position)), 0.0) * light_colour;
    return intensity * diffuse_component;
}

vec3 specular(float intensity, int power) {
    vec3 reflect_direction = reflect(-normalize(light_position - fragment_position), normalize(abnormal));
    vec3 view_direction = normalize(view_position - fragment_position);
    vec3 specular_component = pow(max(dot(view_direction, reflect_direction), 0.0), power) * light_colour;
    return intensity * specular_component;
}

void main() {
    vec3 result = (ambient(0.1) + diffuse(0.2) + specular(0.4, 32)) * object_colour;
    frag_colour = vec4(result, 1.0);
}
