#version 410 core

layout (vertices = 3) out;

in VS_OUT
{
    vec3 color;
    float time;
} tcs_in[];

out TCS_OUT
{
    vec3 color;
    float time;
} tcs_out[];

void main()
{
    // Only if i am invocation 0
    if (gl_InvocationID == 0)
    {
        gl_TessLevelInner[0] = 1.0 + tcs_in[0].time;
        gl_TessLevelOuter[0] = 1.0 + tcs_in[0].time;
        gl_TessLevelOuter[1] = 1.0 + tcs_in[0].time;
        gl_TessLevelOuter[2] = 1.0 + tcs_in[0].time;        
    }

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
    tcs_out[gl_InvocationID].color = tcs_in[gl_InvocationID].color;
    tcs_out[gl_InvocationID].time = tcs_in[gl_InvocationID].time;
}