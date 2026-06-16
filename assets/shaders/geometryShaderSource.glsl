#version 410 core

layout(triangles) in;
layout(points, max_vertices = 3) out;

in TES_OUT
{
    vec3 color;
    float time;
} tes_in[];

out GS_OUT
{
    vec3 color;
    float time;
} gs_out;

void main()
{
    for(int i = 0; i < gl_in.length(); ++i)
    {
        gl_Position = gl_in[i].gl_Position;
        gs_out.color = tes_in[i].color;
        gs_out.time = tes_in[i].time;

        EmitVertex();
    }

    EndPrimitive();
}