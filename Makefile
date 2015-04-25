TARGET = SoftHeap

SRC = \
	Driver.cpp \

OBJ_FILES := $(SRC:.cpp=.o)

CPPFLAGS := -g -Wall -std=c++11

all:	$(TARGET)

$(TARGET):	$(OBJ_FILES)
	g++ $(CPPFLAGS) $(OBJ_FILES) -o $@

# common build recipe for .o files
%.o:	%.cpp
	g++ $(CPPFLAGS) -c $^

clean:
	rm -f *~ *# *.o *.exe $(TARGET)