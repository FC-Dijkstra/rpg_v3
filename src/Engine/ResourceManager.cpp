#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

std::map<std::string, Texture2D*> ResourceManager::Textures;
std::map<std::string, Shader*> ResourceManager::Shaders;

Shader* ResourceManager::loadShader(const char* vertShaderFile, const char* fragShaderFile, const char* geoShaderFile, std::string name) {
	Shader* s = new Shader(vertShaderFile, fragShaderFile, geoShaderFile);
	Shaders[name] = s;
	return Shaders[name];
}

Shader* ResourceManager::getShader(std::string name) {
	return Shaders[name];
}

Texture2D* ResourceManager::loadTexture(const char* texFile, std::string name) {
    Texture2D *t = new Texture2D();
    t->load(texFile);
    Textures[name] = t;
    return Textures[name];
}