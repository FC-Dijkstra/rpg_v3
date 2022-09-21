#include <iostream>
using namespace std;
#include "../../lib/glad/glad.h"
#include <GLFW/glfw3.h>
#include "../../lib/stb_image.h"
#include "Texture.h"
GLuint loadTexture(const char * texture_file_path) {

	unsigned int texture;
	glGenTextures(1, &texture);

	int width, height, nrComponents;
	unsigned char * data = stbi_load(texture_file_path, &width, &height, &nrComponents, 0);
	if (data) {
		//si on peut lire les données de la texture
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4) {
			format = GL_RGBA;
			stbi_set_flip_vertically_on_load(true);
		}

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);

		std::cout << "Loaded texture " << texture_file_path << std::endl;
	}
	else {
		std::cout << "Erreur, impossible de charger la texture " << texture_file_path << std::endl;
		stbi_image_free(data);
	}

	return texture;
}