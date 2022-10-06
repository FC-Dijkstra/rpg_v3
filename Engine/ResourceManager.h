#pragma once
#include <map>
#include <string>
#include "../lib/glad/glad.h"
#include "GL/Shader.h"
#include "GL/Texture.h"

class ResourceManager
{
public:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture> Textures;

	static Shader loadShader(const char* vertShaderFile, const char* fragShaderFile, const char* geoShaderFile, std::string name);
	static Shader getShader(std::string name);

	static Texture loadTexture(const char* texFile, bool alpha, std::string name);
	static Texture getTexture(std::string name);

	static void clear();

private:
	ResourceManager() {}

};

