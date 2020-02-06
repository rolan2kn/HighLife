#version 330
layout (location = 0) in vec3 aPos;

out VS_OUT {
    vec4 vertex_color;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vs_out.vertex_color =  vec4(1.0, 0.0, 0.0, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
