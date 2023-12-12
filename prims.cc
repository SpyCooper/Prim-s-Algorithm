#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <sstream>

using namespace std;

// typedefs
typedef pair<int, int> two_ints;

// structs
struct three_ints
{
    int first_v;
    int second_v;
    int connection_weight;
};

// function prototypes
vector<vector<two_ints>> ReadInGraph(string filename);
void PrintOutGraph(string filename, vector<three_ints> MST, int vertices);
vector<three_ints> PrimsAlgorithm(vector<vector<two_ints>> graph, int start);

// main function
int main()
{
    // creates the paths to the input files
    string graph1_path = "graph1.txt";
    string graph2_path = "graph_v100_e150.txt";
    string graph3_path = "graph_v200_e300.txt";
    string graph4_path = "graph_v400_e1200.txt";
    string graph5_path = "graph_v800_e3200.txt";
    string graph6_path = "graph_v1600_e6400.txt";
    string graphs[6] = {graph1_path, graph2_path, graph3_path, graph4_path, graph5_path, graph6_path};

    // goes through each graph file
    for(int i = 0; i < 6; i++)
    {
        // reads in the graph from the corresponding input file
        vector<vector<two_ints>> graph = ReadInGraph(graphs[i]);

        // checks to see if the file opened correctly
        if(graph.size() == 0)
        {
            cout << "Failed to open the graph folder:" << graphs[i] << endl;
            return 1;
        }

        // gets the number of vertices
        int vertices = graph.size() - 1;

        // finds the minimum spanning tree using Prim's algorithm
        vector<three_ints> prim_MST = PrimsAlgorithm(graph, 1);

        // prints the minimum spanning trees to the corresponding output files
        PrintOutGraph(graphs[i], prim_MST, vertices);
    }

    return 0;
}

// reads in the graph from the corresponding input file
vector<vector<two_ints>> ReadInGraph(string filename)
{
    // opens the input file
    ifstream inputFile;
    string folderPath = "graphs/";
    inputFile.open(folderPath + filename);

    // creates a vector to store the graph
    vector<vector<two_ints>> graph;

    // checks to see if the file opened correctly
    if(inputFile.fail()) 
    {
        cout << "Failed to open the graph file: " << filename << endl;
        return graph;
    }

    // stores the line of the file
    string line;

    // reads the first line (vertices)
    getline(inputFile, line);
    int vertices = stoi(line);
    graph.resize(vertices+1);

    // processes each line of the file
    while(!inputFile.eof()) 
    {
        string line;
        getline(inputFile, line);
        stringstream ss(line);
        int vertex1, vertex2, weight;
        char comma1, comma2;
        ss >> vertex1 >> comma1 >> vertex2 >> comma2 >> weight;
        graph[vertex1].push_back(make_pair(vertex2, weight));
        graph[vertex2].push_back(make_pair(vertex1, weight));
    }
    inputFile.close();

    return graph;
}

// prints the minimum spanning tree to the corresponding output file
void PrintOutGraph(string filename, vector<three_ints> MST, int vertices)
{
    // sets up all the paths to the output files
    string outputFolderPath = "MSTs/";
    string prims_output_path = "prims_MST_";

    // opens the output file
    ofstream outputFile;
    outputFile.open(outputFolderPath + prims_output_path + filename);

    // checks to see if the file opened correctly
    if(outputFile.fail()) 
    {
        cout << "Failed to open the output file: " << filename << endl;
        return;
    }

    // prints the minimum spanning tree to the output file
    outputFile << vertices;
    for (size_t i = 0; i < MST.size(); i++) 
    {
        outputFile << "\n"<< MST[i].first_v << "," << MST[i].second_v << "," << MST[i].connection_weight;
    }
    outputFile.close();
}

// finds the minimum spanning tree of a graph using Prim's algorithm
vector<three_ints> PrimsAlgorithm(vector<vector<two_ints>> graph, int start) 
{
    // gets the number of vertices
    int n = graph.size();

    // creates a vector to store the visited vertices, and sets them all to false, except for the starting vertex
    bool visited[n];
    for(int i = 0; i < n; i++) 
    {
        visited[i] = false;
    }
    visited[start] = true;

    // creates a vector to store the minimum spanning tree
    vector<three_ints> prim_MST;

    // creates a boolean to check if the algorithm is finished
    bool finished = false;

    // runs the algorithm until all vertices have been visited
    while (finished==false) 
    {
        finished = true;

        /*
        creates variables to store the minimum distance, the index of the minimum distance, and the first vertex
        of all the connections from the visited vertices
        */
        int min_dist = INT_MAX;
        int min_index = -1;
        int first_vertex = -1;

        // goes through each vertex
        for(int i = 0; i < n; i++)
        {
            // checks if the vertex has been visited
            if(visited[i])
            {
                // goes through each connection of the vertex
                for(size_t j = 0; j < graph[i].size(); j++)
                {
                    // checks if the connected vertex has been visited
                    if (!visited[graph[i][j].first])
                    {
                        // checks if the distance is less than the current minimum distance
                        if (graph[i][j].second < min_dist)
                        {
                            // sets the minimum distance, index, and first vertex to the current connection
                            first_vertex = i;
                            min_dist = graph[i][j].second;
                            min_index = graph[i][j].first;
                        }
                    }
                }
            }
        }

        // checks if the minimum index has been changed
        if (min_index != -1) {
            // sets the minimum index to visited
            visited[min_index] = true;

            // adds the connection to the minimum spanning tree
            if(first_vertex < min_index)
                prim_MST.push_back(three_ints{first_vertex, min_index, min_dist});
            else
            {
                prim_MST.push_back(three_ints{min_index, first_vertex, min_dist});
            }
        }

        // checks if all vertices have been visited
        for(int i = 1; i < n; i++) 
        {
            if (visited[i] == false) 
            {
                finished = false;
            }
        }
    }

    // returns the minimum spanning tree
    return prim_MST;
}
