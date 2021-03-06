#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Window {
  public:
    Window();
    Window(GLint width, GLint height);
    ~Window();

    int Initialize();
    bool ShouldClose();
    void SwapBuffers();

    GLfloat getBufferWidth () { return (GLfloat)bufferWidth; };
    GLfloat getBufferHeight () { return (GLfloat)bufferHeight; };

    bool* getKeys () { return keys; };

    GLfloat GetXChange ();
    GLfloat GetYChange ();

  private:
    GLFWwindow* window;
    GLint width, height;
    int bufferWidth, bufferHeight;

    void CreateCallbacks ();

    bool keys[1024];
    static void HandleKeys (GLFWwindow* window, int key, int code, int action, int mode);

    bool mouseFirstMove;
    GLfloat lastX, lastY, xChange, yChange;
    static void HandleMouse (GLFWwindow* window, double xPos, double yPos);
};
