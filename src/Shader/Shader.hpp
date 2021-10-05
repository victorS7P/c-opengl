#include <iostream>
#include <string>
#include <fstream>

#include "GL/glew.h"

class Shader {
	public:
		Shader();
		~Shader();

		void CreateFromString(const char* vertexCode, const char* fragmentCode);
		void CreateFromFile(const char* vertexLocation, const char* fragmentLocation);
		void UseProgram();

		GLint GetUniformProjection() { return uniformProjection; }
		GLint GetUniformModel() { return uniformModel; }

	private:
		GLuint shaderID;
		GLint uniformProjection, uniformModel;

		void Compile(const char* vertexCode, const char* fragmentCode);
		void AddShader(GLenum shaderType, const char* shaderCode);

		std::string ReadFile(const char* fileLocation);
};
