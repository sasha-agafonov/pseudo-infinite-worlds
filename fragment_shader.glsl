#version 460 core

out vec4 frag_colour;

in vec3 fragment_position;
in vec3 abnormal;
in vec3 vex_pos_p;

uniform vec3 direction;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 view_position;
uniform vec3 object_colour;
uniform vec3 clear_colour;

uniform vec3 observer;



vec3 interpolate_height_colour(vec3 pos) {

    //1.00, 0.960, 0.660
    //0.468, 0.667, 0.780

    float color_1 = (1.f - 0.367) * pos.y / (5) + 0.367;
    float color_2 = (0.960 - 0.552) * pos.y / (5) + 0.552;
    float color_3 = (0.80 - 0.381) * pos.y / (5) + 0.381;

    return vec3(color_1, color_2, color_3);
}


float lin_fog(float fragment, float fog_start, float fog_end) {

    if (fragment < fog_start) return 0.f;
    else if (fragment > fog_end) return 1.f;
    return (1.f - (fog_end - fragment) / (fog_end - fog_start));
}


void main() {

    vec3 height_colour = interpolate_height_colour(vex_pos_p);

    vec3 light_direction = normalize(- direction);
    vec3 ndiffuse = diffuse * max(dot(abnormal, light_direction), 0.0);

    vec3 view_direction = normalize(view_position - fragment_position);
    vec3 reflect_direction = reflect(- light_direction, abnormal);

    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), 1.f);
    vec3 nspecular = specular * spec;

    float fogval = lin_fog(length(view_position - fragment_position), 300.f, 1000.f);

    // float mx = clear_colour.x;
    //


    //vec3 final_colour = vec3(cx, cy, cz);


    vec3 res = (ambient + ndiffuse + nspecular) * height_colour;

    float cx = (clear_colour.x - res.x) * fogval + res.x;
    float cy = (clear_colour.y - res.y) * fogval + res.y;
    float cz = (clear_colour.z - res.z) * fogval + res.z;

    vec3 last = vec3(cx, cy, cz);

    frag_colour = vec4(last, 1.0);

}
