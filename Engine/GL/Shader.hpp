#pragma once
#include <vector>
#include <iostream>
#include "glm/glm.hpp"

class Shader {
public:
	Shader(const char* vertex_file_path, const char* fragment_file_path);
	void linkTexture(unsigned int texture, const char * texture_shader_name);
	void bind();
	void unbind();
	void linkMat4(glm::mat4 matrix, const char *matrix_shader_name);
	void linkVec3(const float v1, const float v2, const float v3, const char* vector_shader_name);
	void bindTextures();
	~Shader();

private:
	GLuint ProgramID;
	std::vector<GLuint> textures;
};