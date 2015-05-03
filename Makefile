TARGET = MSTCompare
GEN = GraphGen

SRC = \
	Driver.cpp \
	Timer.cpp \
	MST.cpp \
	Graph.cpp \
	DisjointComps.cpp 
#	SoftHeap.cpp

GEN_SRC = \
	Generator.cpp 

OBJ_FILES := $(SRC:.cpp=.o)
GEN_OBJ_FILES := $(GEN_SRC:.cpp=.o)

CPPFLAGS := -g -Wall -std=c++11

all:	$(TARGET)

$(TARGET):	$(OBJ_FILES)
	g++ $(CPPFLAGS) $(OBJ_FILES) -o $@

# common build recipe for .o files
%.o:	%.cpp
	g++ $(CPPFLAGS) -c $^

gen:	$(GEN_OBJ_FILES)
	g++ $(CPPFLAGS) $(GEN_OBJ_FILES) -o $(GEN)

clean:
	rm -f *~ *# *.o *.exe $(TARGET) $(GEN)

# REMOVE AFTER DONE WITH TESTING TIMER
time:	Timer.o TimerTest.o
	g++ $(CPPFLAGS) Timer.o TimerTest.o -o test.exe
