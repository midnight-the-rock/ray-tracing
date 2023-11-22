OUT=ray_trace
CC=g++ -std=c++20 -march=native -mtune=native -O3

S=./src
O=./obj

OBJ= 	$(O)/main.o			\
			$(O)/renderer.o	\
			$(O)/camera.o		\
			$(O)/sphere.o		\
			$(O)/scene.o		\
			$(O)/ray.o			\
			$(O)/material.o			\


$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $@

$(O)/%.o: $(S)/%.cpp 
	$(CC) $< -c -o $@
