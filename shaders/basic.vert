#version 420

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec3 normal;
out vec4 fcolour;

vec4 ambient = vec4(0.2,0.0,0.0,1.0);
vec4 diffuse_colour;

uniform mat4 model, view, projection;
uniform uint colour_mode;

vec3 light_direction = vec3(1,0,0);

vec3 specular_source = vec3(1,1,0);
float shininess = 0.8;


void main()
{	
	//CALCULATING_DIFFUSE
	//transform normals so they aren't affected by scaling anymore?
	mat4 model_view = view*model;
	mat3 n_matrix = transpose(inverse(mat3(model_view)));
	vec3 transf_normals = n_matrix * normal;

	//make sure both are normalised
	transf_normals = normalize(transf_normals);
	light_direction = normalize(light_direction);

	//get the cos of angle between them
	float dif_str = dot(transf_normals, light_direction);
	dif_str = max(dif_str, 0);//clip result at 0-1

	//CALCULATING SPECULAR
	vec4 source =  model_view * vec4(specular_source, 1.0);
	vec3 V = normalize(-source.xyz);
	vec3 reflection = reflect(-specular_source, transf_normals);
	vec4 specular = pow(max(dot(reflection, V),0.0),shininess) * vec4(0.8,.8,.8, 1.0);

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