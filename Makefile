build: main

main: ./src/main.cpp
	g++ `pkg-config --cflags glfw3 glew` -o ./build/main ./src/main.cpp `pkg-config --static --libs glfw3 glew` ./src/Mesh/Mesh.cpp ./src/Shader/Shader.cpp
	@echo "Execute ./build/main para rodar o programa"

run:
	./build/main

clean:
	rm ./build/main