#include "./Texture.hpp"

Texture::Texture () {
  clearTexture();
}

Texture::Texture (char* tempFileLocation) {
  clearTexture();
  fileLocation = tempFileLocation;
}

Texture::~Texture () {
  clearTexture();
}

void Texture::clearTexture () { 
  glDeleteTextures(1, &textureID);

  textureID = 0;
  width = 0;
  height = 0;
  bitDepth = 0;
  fileLocation = NULL;
}

void Texture::loadTexture () {
  printf("%s\n", fileLocation);
  unsigned char* textData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);

  if (!textData) {
    printf("ERRO: ao carregar a imagem %s\n", fileLocation);
    return;
  }

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textData);
    glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(textData);
}

void Texture::useTexture () {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureID);
}
