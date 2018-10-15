#include "Drawable.h"


void Drawable::init(const char* shader_path, const char* fragment_shader_path, float* vertices, int num_verts)
{
	try
	{
		shader.load_shader(shader_path, fragment_shader_path);
	}
	catch (std::exception e)
	{
		std::cout << "Couldn't load shader: " << e.what() << std::endl;
		std::cin.ignore();
		exit(EXIT_FAILURE);
	}

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 2 * num_verts, verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);//stride = bytes from start of first element to start of next
																		  //pointer is int of where to start
																		  //describe colour data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (char*)(sizeof(float) * 4));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//allocate uniform in shader
	model_uniform_id = glGetUniformLocation(shader.get_program_id(), "model");
	//set initial matrix value to identity matrix
	glUseProgram(shader.get_program_id());
	glm::mat4 model = glm::mat4(1.f);
	glUniformMatrix4fv(model_uniform_id, 1, GL_FALSE, &model[0][0]);
	glUseProgram(0);
}

void Drawable::draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
	
	glUseProgram(shader.get_program_id());
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Drawable::set_model_matrix(glm::mat4 model_matrix)
{
	glUniformMatrix4fv(model_uniform_id, 1, GL_FALSE, &model_matrix[0][0]);
}
