// Write a program to solve the 0/1 Knapsack Problem using the Branch & Bound approach.
// Compare its efficiency with dynamic programming.
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

struct Item{
    int weight;
    int profit;
    double ratio;
};

struct Node{
    int level;
    int profit;
    int weight;
    double bound;
};

bool compare(Item a, Item b){
    return a.ratio > b.ratio;
}

struct Compare {
    bool operator()(const pair<double, Node>& a,
                    const pair<double, Node>& b) {
        return a.first < b.first;
    }
};

double calculateBound(Node u, int n, int capacity, Item items[]){
    if(u.weight >= capacity)
       return u.profit;
    
    double profitBound = u.profit;
    int totalWeight = u.weight;
    int j = u.level + 1;

    while(j < n &&
          totalWeight + items[j].weight <= capacity){
            totalWeight += items[j].weight;
            profitBound += items[j].profit;
            j++;
        }
        if(j < n){
            profitBound += (capacity - totalWeight) * items[j].ratio;
        }
        return profitBound;
}

int main(){
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    Item items[100];
    
    cout << "Enter weight and profit: \n";

    for(int i = 0; i < n; i++){
        cin >> items[i].weight >> items[i].profit;
        items[i].ratio = 
            (double)items[i].profit / items[i].weight;
    }

    cout << "Enter capacity: ";
    cin >> capacity;

    sort(items, items + n, compare);

     priority_queue<pair<double, Node>,
                   vector<pair<double, Node>>, Compare> pq;

    Node root;
    root.level = -1;
    root.profit = 0;
    root.weight = 0;

    root.bound = calculateBound(
        root, n, capacity, items
    );

    pq.push({root.bound, root});

    int maxProfit = 0;

    while(!pq.empty()){
        
        Node u = pq.top().second;
        pq.pop();

        if(u.bound <= maxProfit)
          continue;

        int next = u.level + 1;

        if(next >= n)
          continue;

        Node v;

        v.level = next;
        v.weight = u.weight + items[next].weight;
        v.profit = u.profit + items[next].profit;

        if(v.weight <= capacity){
            maxProfit = max(maxProfit, v.profit);
            
            v.bound = calculateBound(
                v, n, capacity, items
            );

            if(v.bound > maxProfit)
            pq.push({v.bound, v});
        }

        Node w;

        w.level = next;
        w.weight = u.weight;
        w.profit = u.profit;

        w.bound = calculateBound(
            w, n, capacity, items
        );

        if(w.bound > maxProfit)
           pq.push({w.bound, w});
    }

    cout << "\nMaximum Profit: " << maxProfit;

        return 0;
}


// 4
// 2 40
// 3 50
// 5 100
// 4 60
// 8


// Enter number of items: 4
// Enter weight and profit:
// Enter capacity: 8

// Maximum Profit: 150

// Sorting	O(n log n)
// Bound calculation	O(n)
// Branch and Bound	Exponential worst case
// Space	O(n × 2ⁿ) worst-case loose bound