#pragma once
#include <map>
#include <string>
#include "../lib/glad/glad.h"
#include "GL/Shader.h"
#include "GL/Texture.h"

//TODO: ajouter chargement d'un fichier JSON contenant toutes les ressources
class ResourceManager
{
public:
	static std::map<std::string, Shader*> Shaders;
	static std::map<std::string, Texture2D*> Textures;

	static Shader* loadShader(const char* vertShaderFile, const char* fragShaderFile, const char* geoShaderFile, std::string name);
	static Shader* getShader(std::string name);

	static Texture2D* loadTexture(const char* texFile, std::string name);
	static Texture2D* getTexture(std::string name);

	static void clear();

private:
	ResourceManager() {}

};

