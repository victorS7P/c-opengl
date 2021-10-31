.PHONY: build run clean all

build:
	@g++ ./src/main.cpp															\
		-o ./build/main																\
		-I ./src/ 																		\
																									\
		`pkg-config --cflags glfw3 glew`  			  		\
		`pkg-config --static --libs glfw3 glew`   		\
																						  		\
		./src/classes/Mesh/Mesh.cpp							  		\
		./src/classes/Shader/Shader.cpp					  		\
		./src/classes/Window/Window.cpp					  		\
		./src/classes/Camera/Camera.cpp					  		\
		./src/classes/Texture/Texture.cpp

run:
	./build/main

clean:
	rm ./build/main

all: clean build run
