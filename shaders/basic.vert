// Minimal vertex shader

#version 420

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec4 normal;
out vec4 fcolour;

vec4 ambient = vec4(0.2,0.2,0.2,1.0);

uniform mat4 model, view, projection;
uniform uint colour_mode;

void main()
{	
	vec4 diffuse_colour;

	
	if(colour_mode == 0)
	{
		diffuse_colour = colour;
	}
	else
	{
		diffuse_colour = vec4(0.0, 1.0, 0, 1.0);
	}

	ambient = diffuse_colour * 0.2;
	fcolour = ambient;

	gl_Position = projection * view * model * position;
}