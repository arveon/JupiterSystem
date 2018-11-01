#include "Drawable.h"


void Drawable::init(Shader shader_program, float* vertices, int num_verts, float* normals, float* texcoords)
{
	this->shader_program = shader_program;
	verts = vertices;
	this->normals = normals;
	this->num_verts = num_verts;
	this->texture_coords = texcoords;

	load_into_memory();
}

Drawable::~Drawable()
{

}

void Drawable::load_into_memory()
{
	glGenBuffers(1, &buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * VALUES_PER_VERT * num_verts, verts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (normals != nullptr)
	{
		glGenBuffers(1, &normal_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * VALUES_PER_NORMAL * num_verts, normals, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Drawable::draw()
{
	//shader_program.set_model_matrix(model_matrix);
	shader_program.set_model_view_matrix(view_matrix * model_matrix);
	shader_program.set_view_matrix(view_matrix);

	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, VALUES_PER_VERT/2, GL_FLOAT, GL_FALSE, sizeof(float) * VALUES_PER_VERT, 0);//stride = bytes from start of first element to start of next
																						//pointer is int of where to start
																						//describe colour data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, VALUES_PER_VERT / 2, GL_FLOAT, GL_FALSE, sizeof(float) * VALUES_PER_VERT, (char*)(sizeof(float) * VALUES_PER_VERT / 2));

	glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, VALUES_PER_NORMAL, GL_FLOAT, GL_FALSE, 0, 0);

	glUseProgram(shader_program.get_program_id());

	glDrawArrays(GL_TRIANGLES, 0, num_verts);
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//reset matrices
	this->model_matrix = glm::mat4(1.0f);
	this->view_matrix = glm::mat4(1.0f);
}

void Drawable::set_model_matrix(glm::mat4 model_matrix)
{
	this->model_matrix = model_matrix;
}

void Drawable::set_view_matrix(glm::mat4 view_matrix)
{
	this->view_matrix = view_matrix;
}

void Drawable::translate(glm::vec3 direction)
{
	model_matrix = glm::translate(model_matrix, direction);
	center_position = direction;
}

void Drawable::rotate(float radians, glm::vec3 axis)
{
	model_matrix = glm::rotate(model_matrix, radians, axis);
}

void Drawable::scale(glm::vec3 direction)
{
	model_matrix = glm::scale(model_matrix, direction);
}
