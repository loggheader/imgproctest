TARGET_CPP_FILES = rangedemo.cpp guirange.cpp histdemo.cpp maskhist.cpp
TARGET_EXECUTABLES = $(patsubst %.cpp, %, $(TARGET_CPP_FILES) )
SRC_FILES := $(filter-out $(TARGET_CPP_FILES), $(wildcard *.cpp) )
CPPFLAGS := -std=c++11
IFLAGS := -I ../union_find/
LDFLAGS := $(filter-out ../union_find/shapetest.o, $(wildcard ../union_find/*.o)) -lopencv_highgui  -lopencv_imgcodecs   -lopencv_imgproc  -lopencv_core
 
OBJ_FILES := $(patsubst %.cpp, %.o ,$(SRC_FILES))
all: $(TARGET_EXECUTABLES)
rangedemo: $(OBJ_FILES) rangedemo.cpp
	g++	 -o $@ $^  $(LDFLAGS) $(CPPFLAGS)
guirange:  $(OBJ_FILES) guirange.cpp
	g++	 -o $@ $^  $(LDFLAGS) $(CPPFLAGS)	 
histdemo:  $(OBJ_FILES) histdemo.cpp
	g++	 -o $@ $^  $(LDFLAGS) $(CPPFLAGS)	 
maskhist:  $(OBJ_FILES) maskhist.cpp
	g++	 -o $@ $^  $(LDFLAGS) $(CPPFLAGS)
%.o:   %.cpp
	g++ $(CPPFLAGS) $(IFLAGS) -c -o $@ $<
clean:
	rm *o
	rm -f $(TARGET_EXECUTABLES)
