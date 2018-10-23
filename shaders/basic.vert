#version 420

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec3 normal;
out vec4 fcolour;

vec4 ambient = vec4(0.2,0.0,0.0,1.0);
vec4 diffuse_colour;

uniform mat4 model, view, projection;
uniform uint colour_mode;
uniform float shininess = 10.0;
uniform vec4 light_position;
uniform vec4 emissive_light;

vec3 light_direction = vec3(1,0,0);


void main()
{	
	//CALCULATING_DIFFUSE
	//transform normals so they aren't affected by scaling anymore?
	mat4 model_view = view*model;
	mat3 n_matrix = transpose(inverse(mat3(model_view)));
	vec3 transf_normal = n_matrix * normal;

	//make sure both are normalised
	transf_normal = normalize(transf_normal);
	light_direction = normalize(light_direction);

	//get the cos of angle between them
	float dif_str = dot(transf_normal, light_direction);
	dif_str = max(dif_str, 0);//clip result at 0-1

	//CALCULATING SPECULAR
	vec4 vert_pos =  model_view * position;
	vec3 vert_pos_normalized = normalize(-vert_pos.xyz);
	vec3 reflection = reflect(-light_direction, transf_normal);
	vec4 specular = pow(max(dot(reflection, vert_pos_normalized),0.0),shininess) * vec4(0.8,.8,.8, 1.0);

	if(colour_mode == 0)
	{
		diffuse_colour = colour;
		ambient = (ambient + colour) * 0.2;
	}
	else
	{
		diffuse_colour = vec4(0.0, 1.0, 0, 1.0);
	}
	
	vec4 diffuse = diffuse_colour * vec4(dif_str);
	fcolour = specular + ambient + diffuse;

	gl_Position = projection * model_view * position;
}