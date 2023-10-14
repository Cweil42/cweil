#include "CreateGraphs.h"
#include "ColorSolver.h"
using namespace std;

int main() {
    srand (time(NULL));
    CreateGraphs create;
    ColorSolver solver;

//    // PART 1
//    AdjacencyList cycle = create.CreateGraph(10, 16, "CYCLE", "NONE");
//    AdjacencyList complete = create.CreateGraph(10, 16, "COMPLETE", "NONE");
//    AdjacencyList uniform = create.CreateGraph(10, 16, "RANDOM", "UNIFORM");
//    AdjacencyList tier = create.CreateGraph(10, 16, "RANDOM", "TIERED");
//    AdjacencyList linear = create.CreateGraph(10, 16, "RANDOM", "LINEAR");
//
//    cycle.OutputFile("../Graphs/cycle.csv");
//    complete.OutputFile("../Graphs/complete.csv");
//    uniform.OutputFile("../Graphs/uniform.csv");
//    tier.OutputFile("../Graphs/tier.csv");
//    linear.OutputFile("../Graphs/linear.csv");
//
//
//    // PART 2
//
//    // Complete output for SLVO
//    string filenames[5] = {"complete","cycle","uniform","tier","linear"};
//    AdjacencyList graph = create.createRandomTiered(100, 900);
//    int *slvoOrder = solver.slvoSolver(graph);
//    solver.colorGraph(slvoOrder, graph, "SLVO_" + filenames[2], true, true);
//
//    // Get outputs for all combinations of ordering/ graph
//    for(int i = 2; i < 5; i++) {
//        AdjacencyList graph = create.createRandomUniform(10,18);
//
//        AdjacencyList graph = create.readFromFile("../Graphs/" + filenames[i] + ".csv");
//        cout << "--------------------------------" << endl;
//        cout << filenames[i] << endl;
//
//        cout  << endl << "SLVO" << endl;
//        int *slvoOrder = solver.slvoSolver(graph);
//        solver.colorGraph(slvoOrder, graph, "SLVO_" + filenames[i], false, false);
//        delete[] slvoOrder;
//
//        cout  << endl << "Smallest Original Degree" << endl;
//        int *smallOrigOrder = solver.smallOriginalSolver(graph);
//        solver.colorGraph(smallOrigOrder, graph, "SmallestOriginalDegree_" + filenames[i], false, false);
//        delete[] smallOrigOrder;
//
//        cout  << endl << "Random Order" << endl;
//        int *randomOrder = solver.uniformRandomSolver(graph);
//        solver.colorGraph(randomOrder, graph, "RandomOrder_" + filenames[i], false, false);
//        delete[] randomOrder;
//    }
//
//    // Functions to create data/ graph files
//    create.CycleAndCompleteGraphTimings();
    create.RandomGraphCreationTimings();
//    create.OutputGraphConflicts();
//
//    solver.PrintExampleSLVO();
//    solver.OrderSolverTimings();
//
//    solver.ColorTimings();

    return 0;
}

