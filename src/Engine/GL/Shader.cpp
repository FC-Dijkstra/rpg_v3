#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;
#include <stdlib.h>
#include <string.h>
#include "../../lib/glad/glad.h"
#include "lib/glm/glm.hpp"
#include "lib/glm/gtc/type_ptr.hpp"
#include "Shader.h"

Shader::Shader(const char * vertex_file_path, const char * fragment_file_path, const char * geo_file_path) {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint geoShaderID = glCreateShader(GL_GEOMETRY_SHADER);

	std::string vertexShaderCode = this->load(vertex_file_path);
	std::string fragmentShaderCode = this->load(fragment_file_path);
	std::string geoShaderCode = geo_file_path != nullptr ? this->load(geo_file_path) : "";

	this->compile(vertexShaderCode, vertexShaderID);
	this->check(vertexShaderID);

	this->compile(fragmentShaderCode, fragmentShaderID);
	this->check(fragmentShaderID);

	if (geoShaderCode != "") {
		this->compile(geoShaderCode, geoShaderID);
		this->check(geoShaderID);
	}

	// Lier les shaders
	printf("Linking program\n");
	ProgramID = glCreateProgram();
	glAttachShader(ProgramID, vertexShaderID);
	glAttachShader(ProgramID, fragmentShaderID);
	if (geo_file_path != nullptr) {
		glAttachShader(ProgramID, geoShaderID);
	}
	glLinkProgram(ProgramID);

	// Check the program
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, vertexShaderID);
	glDetachShader(ProgramID, fragmentShaderID);
	if (geo_file_path != nullptr) {
		glDetachShader(ProgramID, geoShaderID);
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteShader(geoShaderID);
}

std::string Shader::load(const char* filePath) {
	std::string ShaderCode;
	std::ifstream ShaderStream(filePath, std::ios::in);
	if (ShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << ShaderStream.rdbuf();
		ShaderCode = sstr.str();
		ShaderStream.close();
	}
	else {
		printf("Impossible de charger un shader: %s\n", filePath);
		getchar();
	}

	return ShaderCode;
}

void Shader::check(GLuint shaderID) {
	GLint Result = GL_FALSE;
	int InfoLogLength;

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
	}
}
void Shader::compile(std::string code, GLuint shaderID) {
	printf("Compilation du shader : %d\n", shaderID);
	char const* VertexSourcePointer = code.c_str();
	glShaderSource(shaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(shaderID);
}

Shader::~Shader() {
	glDeleteProgram(ProgramID);
}

void Shader::linkTexture(unsigned int texture,const char * texture_shader_name) {
	unsigned int textureLocation = glGetUniformLocation(ProgramID, texture_shader_name);
	glUniform1i(textureLocation, textures.size());
	textures.push_back(texture);
	glBindTexture(GL_TEXTURE_2D, texture);
}

void Shader::bindTextures(){
	for (int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures.at(i));
	}
}

void Shader::linkMat4(glm::mat4 matrix, const char * matrix_shader_name) {
	unsigned int matrixLocation = glGetUniformLocation(ProgramID, matrix_shader_name);
	glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, value_ptr(matrix));
}

void Shader::linkVec3(const float v1, const float v2, const float v3, const char* vector_shader_name)
{
	unsigned int vectorLocation = glGetUniformLocation(ProgramID, vector_shader_name);
	glUniform3f(vectorLocation, v1, v2, v3);
}

void Shader::bind() {
	glUseProgram(ProgramID);
}

void Shader::unbind()
{
	glUseProgram(0);
}