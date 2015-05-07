TARGET = MSTCompare
GEN = GraphGen

SRC = \
	Driver.cpp \
	Timer.cpp \
	MST.cpp \
	Graph.cpp \
	DisjointComps.cpp \
	FHeap.cpp
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
	rm -f -r analysis/

# run analysis
analysis: $(TARGET) gen
	if [ ! -d "analysis/" ]; then mkdir analysis ; fi 
	./$(GEN) 1000 analysis/1000_vertices.txt
	./$(GEN) 2000 analysis/2000_vertices.txt
	./$(GEN) 3000 analysis/3000_vertices.txt
	./$(GEN) 4000 analysis/4000_vertices.txt
	./$(GEN) 5000 analysis/5000_vertices.txt
	./$(TARGET) analysis/1000_vertices.txt analysis/1000_vertices_run1.txt
	./$(TARGET) analysis/1000_vertices.txt analysis/1000_vertices_run2.txt
	./$(TARGET) analysis/1000_vertices.txt analysis/1000_vertices_run3.txt
	./$(TARGET) analysis/1000_vertices.txt analysis/1000_vertices_run4.txt
	./$(TARGET) analysis/1000_vertices.txt analysis/1000_vertices_run5.txt
	./$(TARGET) analysis/2000_vertices.txt analysis/2000_vertices_run1.txt
	./$(TARGET) analysis/2000_vertices.txt analysis/2000_vertices_run2.txt
	./$(TARGET) analysis/2000_vertices.txt analysis/2000_vertices_run3.txt
	./$(TARGET) analysis/2000_vertices.txt analysis/2000_vertices_run4.txt
	./$(TARGET) analysis/2000_vertices.txt analysis/2000_vertices_run5.txt
	./$(TARGET) analysis/3000_vertices.txt analysis/3000_vertices_run1.txt
	./$(TARGET) analysis/3000_vertices.txt analysis/3000_vertices_run2.txt
	./$(TARGET) analysis/3000_vertices.txt analysis/3000_vertices_run3.txt
	./$(TARGET) analysis/3000_vertices.txt analysis/3000_vertices_run4.txt
	./$(TARGET) analysis/3000_vertices.txt analysis/3000_vertices_run5.txt
	./$(TARGET) analysis/4000_vertices.txt analysis/4000_vertices_run1.txt
	./$(TARGET) analysis/4000_vertices.txt analysis/4000_vertices_run2.txt
	./$(TARGET) analysis/4000_vertices.txt analysis/4000_vertices_run3.txt
	./$(TARGET) analysis/4000_vertices.txt analysis/4000_vertices_run4.txt
	./$(TARGET) analysis/4000_vertices.txt analysis/4000_vertices_run5.txt
	./$(TARGET) analysis/5000_vertices.txt analysis/5000_vertices_run1.txt
	./$(TARGET) analysis/5000_vertices.txt analysis/5000_vertices_run2.txt
	./$(TARGET) analysis/5000_vertices.txt analysis/5000_vertices_run3.txt
	./$(TARGET) analysis/5000_vertices.txt analysis/5000_vertices_run4.txt
	./$(TARGET) analysis/5000_vertices.txt analysis/5000_vertices_run5.txt