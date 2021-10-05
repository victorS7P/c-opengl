#include <iostream>
#include <string.h>
#include <vector>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "./Mesh/Mesh.hpp"
#include "./Shader/Shader.hpp"

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

static const char* vertexLocation = "./shaders/vertexShader.glsl";
static const char* fragmentLocation = "./shaders/fragmentShader.glsl";

void error_glfw(int error, const char* desc) {
  printf("%d: %s\n", error, desc);
}

void CriaTriangulos() {
  GLfloat vertices[] = {
    //x      y     z
    -1.0f, -1.0f, 0.0f,  // Vertice 0 (Preto)
    0.0f, 1.0f, 0.0f,    // Vertice 1 (Verde)
    1.0f, -1.0f, 0.0f,   // Vertice 2 (Vermelho)
    0.0f, -1.0f, 1.0f     // Vertice 3 (Azul)
  };

  unsigned int indices[] = {
    0, 1, 2,        //Base da triangulo
    1, 2, 3,        //Base da direita
    0, 1, 3,        //Base da esquerda
    0, 2, 3         //Base de baixo
  };

  Mesh* obj1 = new Mesh();
  obj1->CreateMesh(vertices, sizeof(vertices), indices, sizeof(indices));
  meshList.push_back(obj1);

  Mesh* obj2 = new Mesh();
  obj2->CreateMesh(vertices, sizeof(vertices), indices, sizeof(indices));
  meshList.push_back(obj2);
}

void CreateShader() {
  Shader* shader = new Shader();
  shader->CreateFromFile(vertexLocation, fragmentLocation);
  shaderList.push_back(shader);
}

int main() {
  glfwSetErrorCallback(error_glfw);

  //Iniciar o GLFW
  if (!glfwInit()) {
    printf("GLFW não foi iniciado \n");
    return 1;
  }

  //Garantir que estamos usando a versão 3.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //Cria a janela
  GLFWwindow* mainWindow = glfwCreateWindow(800, 600, "Ola Mundo!", NULL, NULL);
  if (!mainWindow) {
    printf("GLWF n„o consegiu criar a janela");
    glfwTerminate();
    return 1;
  }

  //Define a janela como principal
  glfwMakeContextCurrent(mainWindow);

  //Armazena as informaÁıes de tamanho de janela do buffer
  int bufferWidth, bufferHeigth;
  glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeigth);

  //GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    printf("Não foi iniciado o GLEW");
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    return 1;
  }

  glEnable(GL_DEPTH_TEST); //Habilitar o Depth Test

  glViewport(0, 0, bufferWidth, bufferHeigth);

  //Criar meu triangulo
  CriaTriangulos();
  CreateShader();

  //Declaração de variaveis para movimentação do triangulo
  bool direction = true, sizeDirection = true, angleDirection = true;
  float triOffset = 0.0f, maxOffset = 0.7f, minOffset = -0.7f, incOffset = 0.01f;
  float size = 0.4f, maxSize = 0.7f, minSize = 0.0f, incSize = 0.01f;
  float angle = 0.0f, maxAngle = 360.0f, minAngle = 0.0f, incAngle = 0.1f;

  while (!glfwWindowShouldClose(mainWindow)) {
    //Iniciar os eventos
    glfwPollEvents();

    //Definindo uma cor para nossa janela
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Recriar a função
    Shader * shader = shaderList[0];
    shader->UseProgram();

      /*
      * Calcula a fisica do nosso jogo
      */
      triOffset += direction ? incOffset : incOffset * -1;
      if (triOffset >= maxOffset || triOffset <= minOffset)
          direction = !direction;

      size += sizeDirection ? incSize : incSize * -1;
      if (size >= maxSize || size <= minSize)
          sizeDirection = !sizeDirection;

      angle += angleDirection ? incAngle : incAngle * -1;
      if (angle >= maxAngle || angle <= minAngle)
          angleDirection = !angleDirection;

      /*
      * Piramide 1
      */
      //criar uma matriz 4x4 (1.0f)
      glm::mat4 model(1.0f);
      model = glm::translate(model, glm::vec3(0.0f, -0.5f, -2.5f)); //Movimentações do triangulo
      model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f)); //Tamanho do triangulo
      model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)); //Rotação

      glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model)); //Passa os valores para a entrada uniform Model
      meshList[0]->RenderMesh(); //Desenha o triangulo 3D (Renderização do piramide)

      /*
      * Piramide 2
      */
      model = glm::mat4(1.0f);
      model = glm::translate(model, glm::vec3(0.0f, 0.75f, -2.5f)); //Movimentações do triangulo
      model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f)); //Tamanho do triangulo
      model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, -1.0f, 0.0f)); //Rotação
      glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model)); //Passa os valores para a entrada uniform Model

      meshList[1]->RenderMesh();

      /*
      * Calcula a Camera de Projeção 3D
      */
      //Calcular a projeção
      glm::mat4 projection = glm::perspective(1.0f, (GLfloat)bufferWidth / (GLfloat)bufferHeigth, 0.1f, 100.0f);
      //Passar o valor para a entrada uniform Projection
      glUniformMatrix4fv(shader->GetUniformProjection(), 1, GL_FALSE, glm::value_ptr(projection));

    glUseProgram(0);

    glfwSwapBuffers(mainWindow);
  }
}