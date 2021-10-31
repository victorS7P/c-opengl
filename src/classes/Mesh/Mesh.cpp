#include "./Mesh.hpp"

Mesh::Mesh() {
  VAO = 0;
  VBO = 0;
  IBO = 0;
}

Mesh::~Mesh() {
	if (IBO != 0) {
		glDeleteBuffers(1, &IBO);
	}

	if (VBO != 0) {
		glDeleteBuffers(1, &VBO);
	}

	if (VAO != 0) {
		glDeleteBuffers(1, &VAO);
	}
}

void Mesh::CreateMesh(GLfloat *vertices, unsigned int numOfVertices, unsigned int *indices, unsigned int numOfIndices) {
  Mesh::numOfIndices = numOfIndices;
  //VAO
  glGenVertexArrays(1, &VAO); //Gera um VAO
  glBindVertexArray(VAO); //Registrando um VAO

    //IBO
    glGenBuffers(1, &IBO); //Gera o IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); //Registra o IBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfIndices, indices, GL_STATIC_DRAW); //Registro os atributos no IBO

      //VBO
      glGenBuffers(1, &VBO); //Gera o VBO
      glBindBuffer(GL_ARRAY_BUFFER, VBO); //Registra o VBO

      glBufferData(GL_ARRAY_BUFFER, numOfVertices, vertices, GL_STATIC_DRAW); //Registro os atributos no VBO
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

      glEnableVertexAttribArray(0); //0: shader location
    glBindBuffer(GL_ARRAY_BUFFER, 0); //remove o acesso do VBO

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //remove o acesso do IBO
  glBindVertexArray(0); //Removendo o acesso ao VAO
}

void Mesh::RenderMesh(){
  glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); //Registra o IBO
      glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //remove o acesso do IBO
  glBindVertexArray(0);
}
