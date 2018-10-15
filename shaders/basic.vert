// Minimal vertex shader

#version 420

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;
out vec4 fcolour;

uniform mat4 model;

void main()
{
	//gl_Position = position;
	gl_Position = model * position;
	fcolour = colour;
}