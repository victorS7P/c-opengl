#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <string.h>
#include <vector>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "classes/Mesh/Mesh.hpp"
#include "classes/Shader/Shader.hpp"
#include "classes/Window/Window.hpp"
#include "classes/Camera/Camera.hpp"
#include "classes/Texture/Texture.hpp"

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

Window* window;
Camera camera;

Texture rockTexture;
Texture grassTexture;
Texture woodTexture;

static const char* vertexLocation = "./shaders/vertexShader.glsl";
static const char* fragmentLocation = "./shaders/fragmentShader.glsl";

void error_glfw(int error, const char* desc) {
  printf("%d: %s\n", error, desc);
}

void CriaTriangulos() {
  GLfloat vertices[] = {
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // Vertice 0
     0.0f,  1.0f, 0.0f, 0.5f, 1.0f, // Vertice 1
     1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // Vertice 2
     0.0f, -1.0f, 1.0f, 0.5f, 0.0f  // Vertice 3
  };

  unsigned int indices[] = {
    0, 1, 2,  //Base da triangulo
    1, 2, 3,  //Base da direita
    0, 1, 3,  //Base da esquerda
    0, 2, 3   //Base de baixo
  };

  GLfloat floorVertices[] = {
    -10.0f, 0.0f, -10.0f,  0.0f,  0.0f,
    -10.0f, 0.0f,  10.0f, 10.0f,  0.0f,
     10.0f, 0.0f,  10.0f, 10.0f, 10.0f,
     10.0f, 0.0f, -10.0f,  0.0f, 10.0f,
  };

  unsigned int floorIndices[] = {
    0, 1, 3,
    1, 2, 3
  };

  GLfloat cubeVertices[] = {
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, -1.0f, 0.0f, 1.0f,
     1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f,  1.0f, 0.25f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.75f, 0.0f,
    -1.0f,  1.0f,  1.0f, 0.25f, 1.0f,
     1.0f,  1.0f,  1.0f, 0.75f, 1.0f
  };

  unsigned int cubeIndices[] = {
    0, 1, 3,
    0, 2, 3,
    0, 1, 5,
    0, 4, 5,
    0, 2, 4,
    2, 4, 6,
    4, 5, 7,
    4, 6, 7,
    2, 3, 7, 
    2, 6, 7,
    1, 3, 5,
    3, 5, 7
  };

  Mesh* obj1 = new Mesh();
  obj1->CreateMesh(vertices, sizeof(vertices), indices, sizeof(indices));
  meshList.push_back(obj1);

  Mesh* floor = new Mesh();
  floor->CreateMesh(floorVertices, sizeof(floorVertices), floorIndices, sizeof(floorIndices));
  meshList.push_back(floor);

  Mesh* cube = new Mesh();
  cube->CreateMesh(cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices));
  meshList.push_back(cube);
}

void CreateShader() {
  Shader* shader = new Shader();
  shader->CreateFromFile(vertexLocation, fragmentLocation);
  shaderList.push_back(shader);
}

int main() {
  glfwSetErrorCallback(error_glfw);

  window = new Window(1200, 768);
  if (window->Initialize()) {
    printf("Erro ao inicializar janela");
    return 1;
  };

  //Criar meu triangulo
  CriaTriangulos();
  CreateShader();

  //Criar camera
  camera = Camera(
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    -90.0f, 0.0f, 0.01f, 0.000001f
  );

  rockTexture = Texture((char*) "src/assets/textures/rock.png");
  rockTexture.loadTexture();

  grassTexture = Texture((char*) "src/assets/textures/grass.png");
  grassTexture.loadTexture();

  woodTexture = Texture((char*) "src/assets/textures/wood.png");
  woodTexture.loadTexture();

  //Declaração de variaveis para movimentação do triangulo
  bool direction = true, sizeDirection = true, angleDirection = true;
  float triOffset = 0.0f, maxOffset = 0.7f, minOffset = -0.7f, incOffset = 0.01f;
  float size = 0.4f, maxSize = 0.7f, minSize = 0.0f, incSize = 0.01f;
  float angle = 0.0f, maxAngle = 360.0f, minAngle = 0.0f, incAngle = 0.1f;

  while (!window->ShouldClose()) {
    //Iniciar os eventos
    glfwPollEvents();

    //Camera controlar teclado e mouse
    camera.keyControl(window->getKeys());
    camera.mouseControl(window->GetXChange(), window->GetYChange());

    //Definindo uma cor para nossa janela
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
      model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f)); //Movimentações do triangulo
      model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)); //Rotação

      glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model)); //Passa os valores para a entrada uniform Model
      rockTexture.useTexture();
      meshList[0]->RenderMesh(); //Desenha o triangulo 3D (Renderização do piramide)

      /*
      * Floor
      */
      model = glm::mat4(1.0f);
      model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

      glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));
      grassTexture.useTexture();
      meshList[1]->RenderMesh();

      /*
      * Cube
      */
      model = glm::mat4(1.0f);
      model = glm::translate(model, glm::vec3(2.0f, 0.7f, -6.0f));
      model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
      model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

      glUniformMatrix4fv(shader->GetUniformModel(), 1, GL_FALSE, glm::value_ptr(model));
      woodTexture.useTexture();
      meshList[2]->RenderMesh();

      /*
      * Calcula a Camera de Projeção 3D
      */
      //Calcular a projeção
      glm::mat4 projection = glm::perspective(1.0f, window->getBufferWidth() / window->getBufferHeight(), 0.1f, 100.0f);
      //Passar o valor para a entrada uniform Projection
      glUniformMatrix4fv(shader->GetUniformProjection(), 1, GL_FALSE, glm::value_ptr(projection));
      glUniformMatrix4fv(shader->GetUniformView(), 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

    glUseProgram(0);

    window->SwapBuffers();
  }
}