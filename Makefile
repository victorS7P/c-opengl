.PHONY: build run clean all

build:
	@g++ ./src/main.cpp -o ./build/main  			\
		`pkg-config --cflags glfw3 glew`  			\
		`pkg-config --static --libs glfw3 glew` \
																						\
		./src/Mesh/Mesh.cpp											\
		./src/Shader/Shader.cpp									\
		./src/Window/Window.cpp									\
		./src/Camera/Camera.cpp

run:
	./build/main

clean:
	rm ./build/main

all: clean build run
