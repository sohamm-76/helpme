// Write a program to solve the traveling salesman problem and to print the path and the cost using LC
// Branch and Bound.
    #include <iostream>
    #include <queue>
    #include <vector>
    #include <algorithm>
    #include <climits>
    using namespace std;

    const int INF = INT_MAX;

    int n;
    int cost[10][10];
    int minOut[10];

    struct Node {
        vector<int> path;
        int visited;
        int level;
        long long currentCost;
        long long bound;
    };

    long long calculateBound(Node node) {

        long long bound = node.currentCost;

        for (int i = 0; i < n; i++) {

            if (!(node.visited & (1 << i))) {

                if (minOut[i] == INF)
                    return INF;

                bound += minOut[i];
            }
        }

        if (minOut[node.path.back()] == INF)
            return INF;

        bound += minOut[node.path.back()];

        return bound;
    }

    struct Compare {
        bool operator()(Node a, Node b) {
            return a.bound > b.bound;
        }
    };

    int main() {

        cout << "Enter number of cities: ";
        cin >> n;

        if (n < 2 || n > 10) {
            cout << "Invalid number of cities\n";
            return 0;
        }

        cout << "Enter cost matrix:\n";

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> cost[i][j];
            }
        }

        // Find minimum outgoing cost
        for (int i = 0; i < n; i++) {

            minOut[i] = INF;

            for (int j = 0; j < n; j++) {

                if (i != j && cost[i][j] > 0) {
                    minOut[i] = min(minOut[i], cost[i][j]);
                }
            }
        }

        priority_queue<Node, vector<Node>, Compare> pq;

        Node start;

        start.path.push_back(0);
        start.visited = 1;
        start.level = 1;
        start.currentCost = 0;
        start.bound = calculateBound(start);

        pq.push(start);

        long long bestCost = INF;
        vector<int> bestPath;

        while (!pq.empty()) {

            Node curr = pq.top();
            pq.pop();

            // Prune costly paths
            if (curr.bound >= bestCost)
                continue;

            // Check if all cities are visited
            if (curr.level == n) {

                int last = curr.path.back();

                if (cost[last][0] > 0) {

                    long long total = curr.currentCost + cost[last][0];

                    if (total < bestCost) {
                        bestCost = total;
                        bestPath = curr.path;
                    }
                }

                continue;
            }

            // Try every unvisited city
            int last = curr.path.back();

            for (int i = 0; i < n; i++) {

                if (!(curr.visited & (1 << i)) &&
                    cost[last][i] > 0) {

                    Node child = curr;

                    child.path.push_back(i);
                    child.visited |= (1 << i);
                    child.level++;

                    child.currentCost += cost[last][i];

                    child.bound = calculateBound(child);

                    if (child.bound < bestCost) {
                        pq.push(child);
                    }
                }
            }
        }

        // Print result
        if (bestCost == INF) {
            cout << "No valid tour exists\n";
        }
        else {
            cout << "\nMinimum Cost: " << bestCost;

            cout << "\nBest Path: ";

            for (int city : bestPath)
                cout << city << " -> ";

            cout << "0\n";
        }

        return 0;
    }




//     Time Complexity: \(O(N \times N!)\)
// Space Complexity: \(O(N \times N!)\)
// Algorithm: Least Cost Branch and Bound
// Data Structure: Priority Queue
// Problem: Travelling Salesman Problem (TSP)

// Enter number of cities: 4
// Enter cost matrix:
// 0 10 15 20
// 10 0 35 25
// 15 35 0 30
// 20 25 30 0

// Minimum Cost: 80
// Best Path: 0 -> 1 -> 3 -> 2 -> 0