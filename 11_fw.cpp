// Implement Floyd-Warshall algorithm to find the shortest paths between all pairs of vertices in a
// weighted graph using dynamic programming.
#include<iostream>
#include<climits>
using namespace std;

const int INF = INT_MAX;

int main(){
    int n;

    cout << "Enter number of vertices: ";
    cin >> n;

    if(n < 1 || n > 10){
        cout << "Invalid number of vertices";
        return 0;
    }

    int dist[10][10];

    cout << "Enter adjacency matrix:\n";
    cout << "(Enter -1 for no edge)\n";

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int x;
            cin >> x;

            if(x == -1)
                dist[i][j] = INF;
            else
                dist[i][j] = x;
        }
    }

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){

                if(dist[i][k] != INF &&
                   dist[k][j] != INF){

                    long long sum = (long long)dist[i][k] + dist[k][j];

                    if(sum < dist[i][j]){
                        dist[i][j] = (int)sum;
                    }
                }
            }
        }
    }

    cout << "\nShortest distance Matrix:\n";

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < n; i++){
        if(dist[i][i] < 0){
            cout << "\nNegative Cycle Detected\n";
            return 0;
        }
    }

    return 0;
}

// TC O(n3)
//SC 0(n2)
// 3
// 0 5 99999
// 99999 0 3
// 2 99999 0