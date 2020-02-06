#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec4 vertex_color;
} gs_in[];

out vec4 vertex_color;

uniform float time;
uniform int option;

vec4 explode(vec4 position, vec3 normal)
{

    if (option == 1)
    {
        float magnitude = 2*sqrt(normal.x*normal.x + normal.z*normal.z);
        float scale = 1.0 *cos(time*2 * magnitude) ;
        if(scale < 0)
          scale = 0;

        return vec4(position.xyz + (normal * scale) , 1.0);
    }
    else if (option == 2)
    {
        float magnitude = length(normal);

                vec3 direction;
                //if (int(magnitude) % 3 == 0)
                  //   direction = normal * (tan(time + 1) ) * magnitude;
                if (int(magnitude) % 2 == 0)
                    direction = normal * (cos(time + 1.0) ) * magnitude;
                else
                        direction = normal * (sin(time + 1.0) ) * magnitude;

                return position + vec4(direction, 0.0);
    }

    return position;
}

vec4 setcolor(vec4 color, vec4 pos)
{
        float len = length(pos);
        return vec4(color + pos*sin(time)*len);
}

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

float GetLen()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 dif = b - a;
    return length(dif);
}

void main() {
    vec3 normal = GetNormal();
    float dif = GetLen();

    if (dif > 0.001)
    {

        gl_Position = explode(gl_in[0].gl_Position, normal);
        vertex_color = setcolor(gs_in[0].vertex_color, gl_Position);
        EmitVertex();

        gl_Position = explode(gl_in[1].gl_Position, normal);
        vertex_color = setcolor(gs_in[1].vertex_color, gl_Position);
        EmitVertex();

        gl_Position = explode(gl_in[2].gl_Position, normal);
        vertex_color = setcolor(gs_in[2].vertex_color, gl_Position);
        EmitVertex();
        EndPrimitive();
    }
}