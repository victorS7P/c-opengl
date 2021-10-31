.PHONY: build run clean all

build:
	@g++ ./src/main.cpp -o ./build/main  			\
		`pkg-config --cflags glfw3 glew`  			\
		`pkg-config --static --libs glfw3 glew` \
																						\
		./src/classes/Mesh/Mesh.cpp							\
		./src/classes/Shader/Shader.cpp					\
		./src/classes/Window/Window.cpp					\
		./src/classes/Camera/Camera.cpp					\

run:
	./build/main

clean:
	rm ./build/main

all: clean build run
