#version 420

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 tex_coords;
out vec4 fcolour;

vec4 ambient_colour = vec4(0.1, 0.1, 0.1, 1);
vec4 diffuse_colour = vec4(0.3, 0.3, 0.3, 1);
vec4 specular_colour = vec4(0.5, 0.5, 0.5, 1);

uniform mat4 model_view, view, projection;
uniform uint colour_mode;

uniform vec4 light_position;

out vec3 fposition, fnormal, flightpos;
out vec4 fdiffuse, fspecular, fambient;
out vec2 ftexCoords;

uniform float shininess = 10;


void main()
{	
	fposition = (model_view * position).xyz;
	fnormal = transpose(inverse(mat3(model_view)))*normal;
	flightpos = (view * light_position).xyz;
	fdiffuse = diffuse_colour;
	fambient = ambient_colour;
	fspecular = specular_colour;
	ftexCoords = tex_coords;

	gl_Position = projection * model_view * position;
}