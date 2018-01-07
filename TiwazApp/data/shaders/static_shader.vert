#version 450

layout(location = 0) in vec3 position;
in vec3 normal;
in vec2 texCoord;

out VS_OUT
{
	vec3 pos;
} vs_out;

uniform mat4 transformation;

void main()
{
	vec4 transformated_position = transformation * vec4(position, 1.0);
	
	vs_out.pos = position;
	gl_Position = transformated_position;
}