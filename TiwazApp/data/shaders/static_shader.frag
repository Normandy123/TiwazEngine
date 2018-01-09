#version 450

out vec4 color;

in VS_OUT
{
	vec3 pos;
} fs_in;

void main()
{
	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}