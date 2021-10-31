#include "GL/glew.h"
#include "vendors/stb_image.hpp"

class Texture {
  public:
    Texture();
    Texture(char* tempFileLocation);
    ~Texture();

    void loadTexture();
    void createTexture();
    void useTexture();
    void clearTexture();

  private:
    GLuint textureID;
    int width, height, bitDepth;
    char* fileLocation;
};
