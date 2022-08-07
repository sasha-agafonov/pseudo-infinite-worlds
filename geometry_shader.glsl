#version 460 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 bnormal[];
in vec3 ragment_position[];

out vec3 fragment_position;
flat out vec3 abnormal;

void main() {

      vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
      vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);

      abnormal = normalize(cross(a, b));
      fragment_position = ragment_position[0];

      for (int i = 0; i < gl_in.length(); i++) {
          gl_Position = gl_in[i].gl_Position;
          EmitVertex();
      }
      EndPrimitive();
}

// vec3 get_normal() {
//
// }
