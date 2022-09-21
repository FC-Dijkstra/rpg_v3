#include "Mesh.h"

Mesh::Mesh(std::vector<float>* positions, std::vector<float>* colors, std::vector<int>* indices)
{
	this->vertexCount = indices->size();
	this->colorOffset = sizeof(float) * positions->size();

	glGenVertexArrays(1, &(this->vaoID));
	glBindVertexArray(this->vaoID);

	//on crée un vbo capable de contenir toutes les données de géométrie et couleur
	glGenBuffers(1, &(this->vboID));
	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (positions->size() + colors->size()), NULL, GL_STATIC_DRAW);

	//on fusionne les données de position et couleur dans un seul buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * positions->size(), positions->data());
	glBufferSubData(GL_ARRAY_BUFFER, colorOffset, sizeof(float) * colors->size(), colors->data());

	//on active les pointeurs pour les deux attributs (position et couleur)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//comme les deux tableaux sont mis l'un après l'autre, pour retrouver la couleur d'un vertex on décale de la taille 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)colorOffset);
	glEnableVertexAttribArray(1);

	//on associe les indices d'utilisations des points.
	glGenBuffers(1, &(this->eboID));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices->data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	std::cout << "created mesh with " << this->vertexCount << " vertices from " << positions->size() << " positions | " << this->colorOffset << " : colorOffset" << std::endl;
}

void Mesh::render()
{
	glBindVertexArray(this->vaoID);
	std::cout << "mesh drawn" << std::endl;
	glDrawElements(GL_TRIANGLES, this->vertexCount, GL_UNSIGNED_INT, nullptr);

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