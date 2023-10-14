//
// Created by Colin Weil on 12/5/22.
//

#include "ColorSolver.h"

ColorSolver::ColorSolver(){}

int* ColorSolver::slvoSolver(AdjacencyList& graph){
    LinkedList<int>* vertexDegrees = new LinkedList<int>[graph.getNumVertices()-1];
    int graphSize = graph.getNumVertices();

    // Create Blank Lists at every possible number of connections
    for(int i = 0; i < graphSize; i++)
        vertexDegrees[i] = LinkedList<int>();

    // Add node number to list where it has number of connections in array
    for(int i = 0; i < graphSize; i++)
        graph.adjList[i].orderPointer = vertexDegrees[graph.adjList[i].connections.getSize()].push_back(i);

    int* ordering = new int[graphSize];
    int orderingCount = 0;
    int smallIndex = 0;

    while(orderingCount < graphSize){
        if(vertexDegrees[smallIndex].getSize() != 0) {
            // Pulling Smallest Vertex off Tree and marking deleted
            int deleted = vertexDegrees[smallIndex].removeHead();
            ordering[graphSize-orderingCount-1] = deleted;
            orderingCount++;
            graph.adjList[deleted].deleted = true;

            // Loop through all of its connections
            ListNode<int> *cur = graph.adjList[deleted].connections.getHead();
            while (cur != nullptr) {
                int vertexNum = cur->data;
                // If the connection is not deleted:
                // delete from current list, subtract connections, add onto new list, and update pointer
                if (!graph.adjList[vertexNum].deleted) {
                    ListNode<int> *toDelete = graph.adjList[vertexNum].orderPointer;
                    vertexDegrees[graph.adjList[vertexNum].curConnections].deleteNode(toDelete);
                    graph.adjList[vertexNum].curConnections--;
                    graph.adjList[vertexNum].orderPointer =
                            vertexDegrees[graph.adjList[vertexNum].curConnections].push_back(vertexNum);
                }
                cur = cur->next;
            }
            // Go back one index in array
            if(smallIndex>0) smallIndex-=2;
            else smallIndex--;
        }
        smallIndex++;
    }
    return ordering;
}

int* ColorSolver::smallOriginalSolver(AdjacencyList graph) {
    LinkedList<int>* vertexDegrees = new LinkedList<int>[graph.getNumVertices()-1];
    int graphSize = graph.getNumVertices();

    // Create Blank Lists at every possible number of connections
    for(int i = 0; i < graphSize; i++)
        vertexDegrees[i] = LinkedList<int>();

    // Add node number to list where it has number of connections in array
    for(int i = 0; i < graphSize; i++)
        graph.adjList[i].orderPointer = vertexDegrees[graph.adjList[i].connections.getSize()].push_back(i);

    int* ordering = new int[graphSize];
    int orderingCount = 0;
    int smallIndex = 0;

    while(orderingCount < graphSize){
        if(vertexDegrees[smallIndex].getSize() != 0) {
            // Pulling Smallest Vertex off Tree and marking deleted
            int deleted = vertexDegrees[smallIndex].removeHead();
            ordering[graphSize-orderingCount-1] = deleted;
            orderingCount++;
            graph.adjList[deleted].deleted = true;

            // Go back one index in array
            if(smallIndex>0) smallIndex-=2;
            else smallIndex--;
        }
        smallIndex++;
    }
    return ordering;
}

int* ColorSolver::uniformRandomSolver(AdjacencyList graph){
    int graphSize = graph.getNumVertices();
    int* ordering = new int[graphSize];

    Vector<int> temp;
    temp.createRandom(graphSize);
    for(int i = 0; i < graphSize; i++)
        ordering[i] = temp[i];
    return ordering;
}

int getSmallestColorInList(AdjacencyList graph, VertexNode& node, int numColors){
    for(int i = 1; i <= numColors; i++){
        bool found = false;
        ListNode<int> *cur =node.connections.getHead();
        while (cur != nullptr) {
            if(graph.adjList[cur->data].color == i){
                found = true;
                break;
            }
            cur = cur->next;
        }
        if(!found) return i;
    }
    return numColors + 1;
}

int ColorSLVO(int* order, AdjacencyList& graph, string filename){
    ofstream out("../Color_Outputs/"+filename+".csv");
    int numColors = 0;
    cout << filename << endl;
    cout << "VERTEX NUM" << "," << "ORIGINAL DEGREE" << "," << "DEGREE WHEN DELETED" << endl;
    int degreeCount = 0;
    int maxDeleted = 0;
    int cliqueSize = 0;

    for(int i = 0; i < graph.getNumVertices(); i++){
        VertexNode& curVertex = graph.adjList[order[i]];
        curVertex.color = getSmallestColorInList(graph, curVertex, numColors);
        if(curVertex.color > numColors) {
            numColors++;
            if(i+1 == numColors)
                cliqueSize++;
        }
        if(curVertex.curConnections > maxDeleted)
            maxDeleted = curVertex.curConnections;

        out << order[i]+1 << "," << curVertex.color << endl;
        cout << order[i]+1 << "," << curVertex.size << "," << curVertex.curConnections << endl;
        degreeCount += curVertex.size;
    }
    cout << "Total Colors Used: " << numColors << endl;
    cout << "Average Original Degree (rounded down): " << degreeCount/graph.getNumVertices() << endl;
    cout << "Maximum Degree when Deleted: " << maxDeleted << endl;
    cout << "Size of Terminal Clique: " << cliqueSize << endl;

    out.close();
    return numColors;
}

int ColorNonSLVO(int* order, AdjacencyList& graph, string filename){
    ofstream out("../Color_Outputs/"+filename+".csv");
    int numColors = 0;
    cout << filename << endl;
    cout << "VERTEX NUM" << "," << "ORIGINAL DEGREE" << endl;
    int degreeCount = 0;

    for(int i = 0; i < graph.getNumVertices(); i++){
        VertexNode& curVertex = graph.adjList[order[i]];
        curVertex.color = getSmallestColorInList(graph, curVertex, numColors);
        if(curVertex.color > numColors) numColors++;

        out << order[i]+1 << "," << curVertex.color << endl;
        cout << order[i]+1 << "," << curVertex.size << endl;
        degreeCount += curVertex.size;
    }
    cout << "Total Colors Used: " << numColors << endl;
    cout << "Average Original Degree (rounded down): " << degreeCount/graph.getNumVertices() << endl;

    out.close();
    return numColors;
}

int ColorNoOutput(int* order, AdjacencyList& graph){
    int numColors = 0;
    int degreeCount = 0;

    for(int i = 0; i < graph.getNumVertices(); i++){
        VertexNode& curVertex = graph.adjList[order[i]];
        curVertex.color = getSmallestColorInList(graph, curVertex, numColors);
        if(curVertex.color > numColors) numColors++;

        degreeCount += curVertex.size;
    }
    cout << "Total Colors Used: " << numColors << endl;
    cout << "Average Original Degree (rounded down): " << degreeCount/graph.getNumVertices() << endl;
    return numColors;
}

int ColorSolver::colorGraph(int* order, AdjacencyList graph, string filename, bool output, bool slvo){
    if(output) {
        if (slvo)
            return ColorSLVO(order, graph, filename);
        else
            return ColorNonSLVO(order, graph, filename);
    }
    else return ColorNoOutput(order, graph);
}

void ColorSolver::OrderSolverTimings(){
    ofstream output("../Timings/OrderSolverTimings.csv");
    output << "V" << "," << "E" << "," << "SLVO" << "," << "Smallest Original" << "," << "Uniform Random" << endl;

    CreateGraphs create;
    int E = 2000;
    for(int i = 1000; i <= 10000; i+=1000)
    {
        AdjacencyList graph = create.createRandomUniform(i, E);

        auto beginTime = chrono::high_resolution_clock::now();
        slvoSolver(graph);
        auto endTime = chrono::high_resolution_clock::now();
        auto slvoTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);

        beginTime = chrono::high_resolution_clock::now();
        smallOriginalSolver(graph);
        endTime = chrono::high_resolution_clock::now();
        auto smallOrginalTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);

        beginTime = chrono::high_resolution_clock::now();
        uniformRandomSolver(graph);
        endTime = chrono::high_resolution_clock::now();
        auto uniformRandomTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);


        output << i << "," << E << "," << slvoTime.count() << "," << smallOrginalTime.count() << ","
            << uniformRandomTime.count() << endl;
    }
    output << endl;
    int V = 2000;
    for(int i = 1000; i <= 10000; i+=1000)
    {
        AdjacencyList graph = create.createRandomUniform(V, i);

        auto beginTime = chrono::high_resolution_clock::now();
        slvoSolver(graph);
        auto endTime = chrono::high_resolution_clock::now();
        auto slvoTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);

        beginTime = chrono::high_resolution_clock::now();
        smallOriginalSolver(graph);
        endTime = chrono::high_resolution_clock::now();
        auto smallOrginalTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);

        beginTime = chrono::high_resolution_clock::now();
        uniformRandomSolver(graph);
        endTime = chrono::high_resolution_clock::now();
        auto uniformRandomTime =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);


        output << V << "," << i << "," << slvoTime.count() << "," << smallOrginalTime.count() << ","
               << uniformRandomTime.count() << endl;
    }
    output.close();
}

void ColorSolver::ColorTimings(){
    ofstream output("../Timings/ColorSolverTimings.csv");
    output << "V" << "," << "E" << "," << "μs" << endl;

    CreateGraphs create;
    for(int i = 10; i <= 100; i+=10)
    {
        AdjacencyList graph = create.createComplete(i);
        int *randomOrder = uniformRandomSolver(graph);

        auto beginTime = chrono::high_resolution_clock::now();
        colorGraph(randomOrder, graph, "none", false, false);
        auto endTime = chrono::high_resolution_clock::now();
        auto time =
                chrono::duration_cast<chrono::microseconds>(endTime - beginTime);

        output << i << "," << graph.getNumEdges() << "," << time.count() << endl;
    }
    output << endl;
    output.close();
}

void ColorSolver::PrintExampleSLVO(){
    CreateGraphs create;
    AdjacencyList graph = create.createRandomUniform(5,6);
    cout << "EXAMPLE" << endl;
    graph.display();
    LinkedList<int>* vertexDegrees = new LinkedList<int>[graph.getNumVertices()-1];
    int graphSize = graph.getNumVertices();

    // Create Blank Lists at every possible number of connections
    for(int i = 0; i < graphSize; i++)
        vertexDegrees[i] = LinkedList<int>();

    // Add node number to list where it has number of connections in array
    for(int i = 0; i < graphSize; i++)
        graph.adjList[i].orderPointer = vertexDegrees[graph.adjList[i].connections.getSize()].push_back(i);

    int* ordering = new int[graphSize];
    int orderingCount = 0;
    int smallIndex = 0;

    while(orderingCount < graphSize){
        if(vertexDegrees[smallIndex].getSize() != 0) {
            // Pulling Smallest Vertex off Tree and marking deleted
            int deleted = vertexDegrees[smallIndex].removeHead();
            ordering[graphSize-orderingCount-1] = deleted;
            orderingCount++;
            graph.adjList[deleted].deleted = true;
            cout << "DELETED " << deleted+1 << endl;

            // Loop through all of its connections
            ListNode<int> *cur = graph.adjList[deleted].connections.getHead();
            while (cur != nullptr) {
                int vertexNum = cur->data;
                // If the connection is not deleted:
                // delete from current list, subtract connections, add onto new list, and update pointer
                if (!graph.adjList[vertexNum].deleted) {
                    ListNode<int> *toDelete = graph.adjList[vertexNum].orderPointer;
                    vertexDegrees[graph.adjList[vertexNum].curConnections].deleteNode(toDelete);
                    graph.adjList[vertexNum].curConnections--;
                    graph.adjList[vertexNum].orderPointer =
                            vertexDegrees[graph.adjList[vertexNum].curConnections].push_back(vertexNum);
                }
                cur = cur->next;
            }
            // Go back one index in array
            if(smallIndex>0) smallIndex-=2;
            else smallIndex--;
        }
        smallIndex++;
    }
    cout << "SLVO Order: [" << ordering[0]+1;
    for(int i = 1; i < graphSize; i++)
        cout << ", " << ordering[i]+1;
    cout << "]" << endl;
}

