#include <iostream>
#include <vector>

using namespace std;


void printDP(const vector<vector<int>>& dp) {
    for(int i=0;i<dp.size();++i) {
        for(int j=0;j<dp[0].size();++j) {
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}


// recursive
int knapsackRec(int currWeight, int currNum, const vector<int>& weight, const vector<int>& cost) {
    if(currNum == 0) {
        return 0;
    }
    if(currWeight<0){
        return INT_MIN;
    }
    // recursive is a top-down approach
    return max(knapsackRec(currWeight, currNum-1, weight, cost), // not choose weight[currNum]
               knapsackRec(currWeight-weight[currNum], currNum-1, weight, cost) + cost[currNum]); // choose weight[currNum]
}


// iteration
int knapsack(const vector<int>& weight, const vector<int>& cost, int weightCapacity) {
    vector<vector<int>> dp(weight.size()+1, vector<int>(weightCapacity+1, 0));
    // iteration is a bottom-up approach
    for(int i=0;i<dp.size()-1;++i) {
        for(int j=0;j<dp[i].size();++j) {
            if(j-weight[i] < 0) {
                /*
                 * Why dp[i+1] ?
                 * Because if we use dp[i][j] = max(dp[i-1][j], dp[i-1][j-weight[i-1]]+cost[i-1])
                 * Then weight and cost needs to be i-1, because dp.size() is weight.size()+1
                 */
                dp[i+1][j] = dp[i][j];
            }
            else {
                dp[i+1][j] = max(dp[i][j], dp[i][j-weight[i]]+cost[i]);
            }
        }
    }
    return dp.back().back();
}

int main() {
    int weightCapacity = 50;
    vector<int> weight = {10, 20, 30};
    vector<int> cost = {60, 100, 120};

    int res = knapsack(weight, cost, weightCapacity);
    cout<<"The result from 2D array is: "<<res<<endl;

    int res2 = knapsackRec(weightCapacity, weight.size(), weight, cost);
    cout<<"The result from recursive array is: "<<res2<<endl;
    return 0;
}
