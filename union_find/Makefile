#SRC_FILES := $(wildcard *.cpp)
#OBJ_FILES := $(patsubst %.cpp, %.o, $(SRC_FILES))
#CC := g++  
#all: $(OBJ_FILES)
#clean:
#	rm *.o

SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp, %.o ,$(SRC_FILES))
CPPFLAGS := -std=c++11
LDFLAGS := -lopencv_highgui  -lopencv_imgcodecs   -lopencv_imgproc  -lopencv_core
shapetest: $(OBJ_FILES)
	g++	 -o $@ $^ $(LDFLAGS)

%.o:   %.cpp
	g++ $(CPPFLAGS) -c -o $@ $<
clean:
	rm *o
	rm shapetest



