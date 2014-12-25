CC=g++

LIBS=-lglut -lGL -lGLEW -m64 -lpng
CFLAGS=-c -Wall
BIN=bin


all: mkdir opengl

opengl: $(BIN)/ConsoleApplication4.o $(BIN)/glut_backend.o $(BIN)/camera.o $(BIN)/math_3d.o $(BIN)/pipeline.o $(BIN)/lighting_technique.o $(BIN)/technique.o $(BIN)/ogldev_util.o $(BIN)/ogldev_texture.o $(BIN)/LibPng.o
	$(CC) $(BIN)/ConsoleApplication4.o $(BIN)/glut_backend.o $(BIN)/camera.o \
 	$(BIN)/math_3d.o $(BIN)/pipeline.o $(BIN)/lighting_technique.o $(BIN)/technique.o \
	$(BIN)/ogldev_util.o $(BIN)/ogldev_texture.o $(BIN)/LibPng.o \
	 -o opengl  $(LIBS)

$(BIN)/ConsoleApplication4.o: 
	$(CC)  $(CFLAGS) ConsoleApplication4.cpp -o $@ 

$(BIN)/glut_backend.o:
	$(CC)  $(CFLAGS) glut_backend.cpp -o $@

$(BIN)/camera.o:
	$(CC) $(CFLAGS)  camera.cpp -o $@

$(BIN)/math_3d.o:
	$(CC) $(CFLAGS) math_3d.cpp -o $@

$(BIN)/pipeline.o:
	$(CC) $(CFLAGS) pipeline.cpp -o $@

$(BIN)/lighting_technique.o:
	$(CC) $(CFLAGS) lighting_technique.cpp -o $@

$(BIN)/technique.o:
	$(CC) $(CFLAGS) common/technique.cpp -o $@

$(BIN)/ogldev_util.o:
	$(CC) $(CFLAGS) common/ogldev_util.cpp -o $@

$(BIN)/ogldev_texture.o:
	$(CC) $(CFLAGS) common/ogldev_texture.cpp -o $@

$(BIN)/LibPng.o:
	$(CC) $(CFLAGS) LibPng.cpp -o $@

mkdir:
	mkdir -p bin
clean:
	rm -rf $(BIN)
