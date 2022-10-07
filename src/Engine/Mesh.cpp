#include "Mesh.h"

Mesh::Mesh(std::vector<float>* positions, std::vector<float>* colors, std::vector<int>* indices)
{
	this->vertexCount = indices->size();
	this->colorOffset = 0;

	int positionsSize = sizeof(float) * positions->size();
	int colorsSize = sizeof(float) * colors->size();
	int totalSize = sizeof(float) * (positions->size() + colors->size());

	glGenVertexArrays(1, &(this->vaoID));
	glBindVertexArray(this->vaoID);

	//on cr�e un vbo capable de contenir toutes les donn�es de g�om�trie et couleur
	glGenBuffers(1, &(this->vboID));
	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
	glBufferData(GL_ARRAY_BUFFER, totalSize, 0, GL_STATIC_DRAW);

	//on fusionne les donn�es de position et couleur dans un seul buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, positionsSize, positions->data());
	glBufferSubData(GL_ARRAY_BUFFER, positionsSize, colorsSize, colors->data());

	//on active les pointeurs pour les deux attributs (position et couleur)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//comme les deux tableaux sont mis l'un aprs l'autre, pour retrouver la couleur d'un vertex on d�cale de la taille
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)positionsSize);
	glEnableVertexAttribArray(1);

	//on associe les indices d'utilisations des points.
	glGenBuffers(1, &(this->eboID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices->size(), indices->data(), GL_STATIC_DRAW);

	//v�rification de la taille du buffer
	GLint size = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	std::cout << "buffer size: " << size << " bytes, expected: " << totalSize <<  " bytes" << std::endl;

	//nettoyage
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	//log
	std::cout << "created mesh with " << this->vertexCount << " vertices from " << positions->size() << " points" << std::endl;
	std::cout << "vaoID: " << this->vaoID << " | vboID: " << this->vboID << " | eboID: " << this->eboID << std::endl;
	
}

void Mesh::render()
{
	glBindVertexArray(this->vaoID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboID);

	glDrawElements(GL_TRIANGLES, this->vertexCount, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::flush()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &(this->vboID));
	glDeleteBuffers(1, &(this->eboID));

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &(this->vaoID));
}

GLuint Mesh::getVaoID()
{
	return this->vaoID;
}

int Mesh::getVertexCount()
{
	return this->vertexCount;
}