#include "Drawable.h"


void Drawable::init(Shader shader_program, float* vertices, int num_verts)
{
	this->shader_program = shader_program;
	verts = vertices;
	this->num_verts = num_verts;
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

}

void Drawable::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * VALUES_PER_VERT, 0);//stride = bytes from start of first element to start of next
																						//pointer is int of where to start
																						//describe colour data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * VALUES_PER_VERT, (char*)(sizeof(float) * VALUES_PER_VERT / 2));

	glUseProgram(shader_program.get_program_id());

	glDrawArrays(GL_TRIANGLES, 0, num_verts);
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Drawable::set_model_matrix(glm::mat4 model_matrix)
{
	shader_program.set_model_matrix(model_matrix);
}

void Drawable::set_view_matrix(glm::mat4 view_matrix)
{
	shader_program.set_view_matrix(view_matrix);
}
