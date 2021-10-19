#include "Window.hpp"

Window::Window () : Window(800, 600) {}

Window::Window (GLint width_param, GLint height_param) {
  for (int i = 0; i < 1024; i++) { keys[i] = false; }

  width = width_param;
  height = height_param;
  mouseFirstMove = true;
}

Window::~Window () {
  glfwDestroyWindow(window);
  glfwTerminate();
}

int Window::Initialize () {
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
  window = glfwCreateWindow(width, height, "Ola Mundo!", NULL, NULL);
  if (!window) {
    printf("GLWF não consegiu criar a janela");
    glfwTerminate();
    return 1;
  }

  //Define a janela como principal
  glfwMakeContextCurrent(window);

  //Armazena as informaÁıes de tamanho de janela do buffer
  glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

  //GLEW
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    printf("Não foi iniciado o GLEW");
    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
  }

  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, bufferWidth, bufferHeight);
  glfwSetWindowUserPointer(window, this);

  CreateCallbacks();
  return 0;
}

bool Window::ShouldClose () {
  return glfwWindowShouldClose(window);
}

void Window::SwapBuffers () {
  glfwSwapBuffers(window);
}

void Window::CreateCallbacks () {
  glfwSetKeyCallback(window, HandleKeys);
  glfwSetCursorPosCallback(window, HandleMouse);
}

void Window::HandleKeys (GLFWwindow* window, int key, int code, int action, int mode) {
  Window* temp = static_cast<Window*>(glfwGetWindowUserPointer(window));

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  if (key > 0 && key <= 1024) {
    if (action == GLFW_PRESS) {
      temp->keys[key] = true;
    }
    
    else if (action == GLFW_RELEASE) {
      temp->keys[key] = false;
    }
  }
}

void Window::HandleMouse (GLFWwindow* window, double xPos, double yPos) {
  Window* temp = static_cast<Window*>(glfwGetWindowUserPointer(window));

  if (temp->mouseFirstMove) {
    temp->mouseFirstMove = false;
    temp->lastX = xPos;
    temp->lastY = yPos;
  }

  temp->xChange = xPos - temp->lastX;
  temp->yChange = temp->lastY - yPos;

  temp->lastX = xPos;
  temp->lastY = yPos;
}

GLfloat Window::GetXChange() {
  GLfloat change = xChange;
  xChange = 0.0f;
  return change;
}

GLfloat Window::GetYChange() {
  GLfloat change = yChange;
  yChange = 0.0f;
  return change;
}