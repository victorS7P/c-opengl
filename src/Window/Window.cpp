#include "Window.hpp"

Window::Window () {
  width = 800;
  height = 600;
}

Window::Window (GLint width_param, GLint height_param) {
  width = width_param;
  height = height_param;
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
}

void Window::HandleKeys (GLFWwindow* window, int key, int code, int action, int mode) {
  Window* temp = static_cast<Window*>(glfwGetWindowUserPointer(window));

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }

  if (key > 0 && key <= 1024) {
    if (action == GLFW_PRESS) {
      temp->keys[key] = true;
      printf("press: %i\n", key);
    }
    
    else if (action == GLFW_RELEASE) {
      temp->keys[key] = false;
      printf("release: %i\n", key);
    }
  }
}
