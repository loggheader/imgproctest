SRC_FILES := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp, %.o ,$(SRC_FILES))
CPPFLAGS := -std=c++11
IFLAGS := -I ../union_find/
LDFLAGS := -lopencv_highgui  -lopencv_imgcodecs   -lopencv_imgproc  -lopencv_core $(wildcard ../union_find/*.o)
featuredemo: $(OBJ_FILES)
	g++	 -o $@ $^ $(filter-out ../union_find/shapetest.o, $(LDFLAGS) )

%.o:   %.cpp
	g++ $(CPPFLAGS) $(IFLAGS) -c -o $@ $<
clean:
	rm *o
	rm featuredemo

