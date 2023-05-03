#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>  // acumulator
#include<fstream>
using namespace std;

int main() {
    ifstream fin("feribot.in");
    ofstream fout("feribot.out");

    int n, k;
    fin >> n >> k;

    vector<long long> weights(n);
    for (int i = 0; i < n; i++) {  // O(n)
        fin >> weights[i];
    }

    long long left = *max_element(weights.begin(), weights.end());  // O(n)
    long long right = accumulate(weights.begin(), weights.end(), 0LL);  // O(n)
    long long ans = right;

    while (left <= right) {  // O(n log m)
        long long mid = (left + right) / 2;
        long long ferry_count = 0;
        long long cur_weight = 0;

        for (int i = 0; i < n; i++) {
            if (cur_weight + weights[i] <= mid) {
                cur_weight += weights[i];
            } else {
                ferry_count += 1;
                cur_weight = weights[i];
            }
        }

        if (ferry_count < k) {
            right = mid - 1;
            ans = mid;
        } else {
            left = mid + 1;
        }
    }

    fout << ans << endl;
    return 0;
}
