#pragma once
#include <string>


struct Texture {
	unsigned int id;
	std::string type;
	std::string path; //pour éviter les duplicata
};

GLuint loadTexture(const char * texture_file_path);