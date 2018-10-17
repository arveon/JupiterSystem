// Minimal vertex shader

#version 420

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec4 normal;
out vec4 fcolour;

uniform mat4 model, view, projection;
uniform uint color_mode;

void main()
{	
	if(color_mode == 0)
		fcolour = colour;
	else
		fcolour = position * 2.0 + vec4(0.5, 0.5, 0.5, 1.0);

	gl_Position = projection * view * model * position;
}