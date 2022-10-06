#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

std::map<std::string, Texture> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::loadShader(const char* vertShaderFile, const char* fragShaderFile, const char* geoShaderFile, std::string name) {
	//Shader s = Shader(vertShaderFile, fragShaderFile, geoShaderFile);
	//Shaders[name] = s;
	return Shaders[name];
}

Shader ResourceManager::getShader(std::string name) {
	return Shaders[name];
}

Texture ResourceManager::loadTexture(const char* texFile, bool alpha, std::string name) {
	Texture t = Texture();
	
}