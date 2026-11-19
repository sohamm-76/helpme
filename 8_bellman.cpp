#include<iostream>
#include<climits>
using namespace std;

const int INF = INT_MAX;

struct Edge{
    int src, dest, weight;
};

int main(){

    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    if(V < 1 || V > 100 || E < 0 || E > 100){
        cout << "Invalid input\n";
        return 0;
    }

    Edge edges[100];

    cout << "Enter source destination weight:\n";

    for(int i = 0; i < E; i++){
        cin >> edges[i].src
            >> edges[i].dest
            >> edges[i].weight;
    }

    int source;

    cout << "Enter source vertex: ";
    cin >> source;

    if(source < 0 || source >= V){
        cout << "Invalid source vertex\n";
        return 0;
    }

    long long dist[100];

    for(int i = 0; i < V; i++)
        dist[i] = INF;

    dist[source] = 0;

    // Relax all edges V-1 times
    for(int i = 1; i <= V-1; i++){

        for(int j = 0; j < E; j++){

            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if(dist[u] != INF &&
               dist[u] + w < dist[v]){

                dist[v] = dist[u] + w;
            }
        }
    }

    // Check negative weight cycle
    for(int j = 0; j < E; j++){

        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if(dist[u] != INF &&
           dist[u] + w < dist[v]){

            cout << "Negative weight cycle detected\n";
            return 0;
        }
    }

    cout << "\nShortest distance:\n";

    for(int i = 0; i < V; i++){

        cout << source << " -> " << i << " = ";

        if(dist[i] == INF)
            cout << "Unreachable\n";
        else
            cout << dist[i] << endl;
    }

    return 0;
}



//TC O(VE)
//SC O(V+E)


// Enter number of vertices: 5
// Enter number of edges: 8
// Enter source destination weight:
// 0 1 -1
// 0 2 4
// 1 2 3
// 1 3 2
// 1 4 2
// 3 2 5
// 3 1 1
// 4 3 -3
// Enter source vertex: 0

// Shortest distance:
// 0 -> 0 = 0
// 0 -> 1 = -1
// 0 -> 2 = 2
// 0 -> 3 = -2
// 0 -> 4 = 1