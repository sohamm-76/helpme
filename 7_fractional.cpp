// Write a program to implement Fractional knapsack using Greedy algorithm and 0/1 knapsack
// using dynamic programming. Show that Greedy strategy does not necessarily yield an optimal
// solution over a dynamic programming approach.
#include <iostream>
#include <algorithm>
using namespace std;

struct Item {
    int weight;
    int profit;
    double ratio;
};

// Fractional Knapsack
bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(Item items[], int n, int capacity) {  //O(nlogn)
    sort(items, items + n, compare);

    double totalProfit = 0;

    for (int i = 0; i < n; i++) {
        if (capacity >= items[i].weight) {
            capacity -= items[i].weight;
            totalProfit += items[i].profit;
        }
        else {
            totalProfit += items[i].ratio * capacity;
            break;
        }
    }

    return totalProfit;
}

// 0/1 Knapsack using DP
int knapsackDP(int weight[], int profit[], int n, int capacity) { // O(n*w)
    int dp[101][101] = {0};

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {

            if (weight[i - 1] <= w) {
                dp[i][w] = max(
                    profit[i - 1] + dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    int weight[100], profit[100];
    Item items[100];

    cout << "Enter weights:\n";
    for (int i = 0; i < n; i++)
        cin >> weight[i];

    cout << "Enter profits:\n";
    for (int i = 0; i < n; i++)
        cin >> profit[i];

    cout << "Enter capacity: ";
    cin >> capacity;

    for (int i = 0; i < n; i++) {
        items[i].weight = weight[i];
        items[i].profit = profit[i];
        items[i].ratio = (double)profit[i] / weight[i];
    }

    cout << "\nFractional Knapsack Profit: "
         << fractionalKnapsack(items, n, capacity);

    cout << "\n0/1 Knapsack Profit: "
         << knapsackDP(weight, profit, n, capacity);

    return 0;
}






//Enter number of items: 3

// Enter weights:
// 10 20 30

// Enter profits:
// 60 100 120

// Enter capacity: 50

// Fractional Knapsack Profit: 240
// 0/1 Knapsack Profit: 220