/*
 * Acest schelet citește datele de intrare și scrie răspunsul generat de voi,
 * astfel că e suficient să completați cele două funcții.
 *
 * Scheletul este doar un punct de plecare, îl puteți modifica oricum doriți:
 * puteți schimba parametrii, reordona funcțiile etc.
 */

#include<iostream>
#include <cstdint>
#include <fstream>
#include <vector>
#include <algorithm>
#include<numeric>
#include<utility>
#include<cmath>

using namespace std;

bool compare(int a, int b) {
    return a > b;
}

bool compare2(int a, int b) {
    return a < b;
}


int64_t SolveTask1(const vector<int>& a, const vector<int>& b) {
    int n = a.size();
    vector<int> merged(2 * n);
    for (int i = 0; i < n; i++) {  // O(n)
        merged[2 * i] = a[i];
        merged[2 * i + 1] = b[i];
    }
    sort(merged.begin(), merged.end(), compare);  // O(n)
    int64_t ans = 0;
    for (int i = 0; i < n; i++) {  // O(n)
        ans += merged[i];
    }
    return ans;
}

int64_t SolveTask2(const vector<int>& a, const vector<int>& b, int moves) {
    int n = a.size();
    vector<int> c(n);
    vector<int> g(n);
    vector<int> maxims(n);
    for (int i = 0; i < n; i++) {  // O(n)
        if (a[i] > b[i]) {
            c[i] = a[i];
            g[i] = b[i];
        } else {
            c[i] = b[i];
            g[i] = a[i];
        }
    }
    int64_t ans = 0;
    sort(c.begin(), c.end(), compare2);  // O(n)
    sort(g.begin(), g.end(), compare);  // O(n)
    for (int i = 0; i < moves; i++) {  // O(n)
        int aux;
        aux = c[i];
        c[i] = g[i];
        g[i] = aux;
    }

     for (int i = 0; i < n; i++) {  // O(n)
        ans += c[i];
    }
    return ans;
}

vector<int> ReadVector(istream& is, int size) {
    vector<int> vec(size);
    for (auto& num : vec) {
        is >> num;
    }
    return vec;
}

int main() {
    ifstream fin("nostory.in");
    ofstream fout("nostory.out");

    int task;
    fin >> task;

    int n, moves;
    if (task == 1) {
        fin >> n;
    } else {
        fin >> n >> moves;
    }

    auto a = ReadVector(fin, n);
    auto b = ReadVector(fin, n);

    auto res = task == 1 ? SolveTask1(a, b) : SolveTask2(a, b, moves);
    fout << res << "\n";

    return 0;
}
