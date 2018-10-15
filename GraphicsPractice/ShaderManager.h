#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <malloc.h>

class ShaderManager
{
private:
	GLuint program = NULL;
public:

	GLuint load_shader(const char* shader_path, const char* fragment_shader_path);
	GLuint build_shader(GLenum shaderType, const std::string &shaderText);
	std::string read_file(const char* file_path);

	GLuint get_program_id() { return program; };

	ShaderManager();
	~ShaderManager();
};

