// Minimal vertex shader

#version 420

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec3 normal;
out vec4 fcolour;

vec4 ambient = vec4(0.2,0.2,0.2,1.0);
vec4 diffuse_colour;

uniform mat4 model, view, projection;
uniform uint colour_mode;

vec3 light_direction = vec3(1,0,0);


void main()
{	
	//transform normals so they aren't affected by scale anymore
	mat4 model_view = view*model;
	mat3 n_matrix = transpose(inverse(mat3(model_view)));

	//make sure both are normalised
	vec3 transf_normals = n_matrix * normal;
	transf_normals = normalize(transf_normals);
	light_direction = normalize(light_direction);
	float dif_str = dot(transf_normals, light_direction);
	dif_str = max(dif_str, 0);
	

	if(colour_mode == 0)
	{
		diffuse_colour = colour;
	}
	else
	{
		diffuse_colour = vec4(0.0, 1.0, 0, 1.0);
	}
	vec4 diffuse = diffuse_colour * vec4(dif_str);
	ambient = diffuse_colour * 0.2;
	fcolour = ambient + diffuse;

	gl_Position = projection * model_view * position;
}