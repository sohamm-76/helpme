// Represent a graph of city using adjacency matrix /adjacency list. Nodes should represent the various
// landmarks and links should represent the distance between them. Find the shortest path using
// Dijkstra's algorithm from single source to all destination.
#include<iostream>
#include<climits>
using namespace std;

const int INF = INT_MAX;

int main(){

    int n;
    int cost[10][10];

    cout << "Enter number of landmarks: ";
    cin >> n;

    if(n < 1 || n > 10){
        cout << "Invalid input";
        return 0;
    }

    cout << "Enter distance matrix (0 for no edge):\n";

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> cost[i][j];

            if(i != j && cost[i][j] == 0)
                cost[i][j] = INF;
        }
    }

    int source;
    cout << "Enter source landmark: ";
    cin >> source;

    if(source < 0 || source >= n){
        cout << "Invalid source";
        return 0;
    }

    int dist[10], visited[10] = {0};

    for(int i = 0; i < n; i++)
        dist[i] = INF;

    dist[source] = 0;

    for(int i = 0; i < n - 1; i++){

        int u = -1;
        int minDist = INF;

        for(int j = 0; j < n; j++){
            if(!visited[j] && dist[j] < minDist){
                minDist = dist[j];
                u = j;
            }
        }

        if(u == -1)
            break;

        visited[u] = 1;

        for(int v = 0; v < n; v++){

            if(!visited[v] && cost[u][v] != INF &&
               dist[u] + cost[u][v] < dist[v]){

                dist[v] = dist[u] + cost[u][v];
            }
        }
    }

    cout << "\nShortest distances from landmark " << source << ":\n";

    for(int i = 0; i < n; i++){

        cout << source << " -> " << i << " = ";

        if(dist[i] == INF)
            cout << "Unreachable\n";
        else
            cout << dist[i] << endl;
    }

    return 0;
}


// Time: \(O(V^2)\) using an adjacency matrix.
// Space: \(O(V^2)\) because of the adjacency matrix.

// Enter number of landmarks: 4
// Enter distance matrix (0 for no edge):
// 0 10 15 0
// 10 0 5 20
// 15 5 0 10
// 0 20 10 0
// Enter source landmark: 0

// Shortest distances from landmark 0:
// 0 -> 0 = 0
// 0 -> 1 = 10
// 0 -> 2 = 15
// 0 -> 3 = 25