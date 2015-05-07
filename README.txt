Comparing the Runtime of 3 MST Algorithms on Graphs with Varying Density
	  Tom, Toren, Yu Heng


********** How to build and run the program **********
To build the program:
   make

To run the program:
   ./MSTCompare <input-file-name> <output-file-name>

To automatically run a default set of tests (warning: will take a LONG time!):
   make analysis

Notes:
   * The input-file is expected to contain any number of graphs.
   * The output-file contains the time (in seconds) it took each of 
     the 3 algorithms to produce a MST for each of the graphs given
     in the input-file. 
   * The format of input and output files are specified in 
     input_format.txt and output_format.txt, respectively.

********** How to build and run the generator **********
To build the generator:
   make gen

To run the generator:
   ./GraphGen <number-of-vertices> <output-file-name>

Notes:
   * The generator will build 10 connected graphs.
   * Each graph will have the user's specified number of vertices.
   * The 10 graphs will vary in density, starting from 10% density
     and incrementing by 10% until 100% density.
   * Density is measured by the number of edges in the graph compared
     to the number of edges in the complete graph with the same number
     of vertices. (ex: a complete graph with 9 vertices has 36 edges,
     thus a graph with 9 vertices and 18 edges is considered to have
     50% density)
