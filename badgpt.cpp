#include <iostream>
#include <string>
#include<fstream>

const int MOD = 1e9 + 7;
using namespace std;
ifstream fin("badgpt.in");
ofstream fout("badgpt.out");

long long factorial(long long n) {
    long long result = 1;

    for (int i = 2; i <= n; i++) {
        result *= i;
    }

    return result;
}

int main() {
    string s;
    fin >> s;
    long long n = s.size() - 1;
    long long ans = 0;
    for (int i = 0; i < n; i += 2) {
        char c = s[i];
        long long len = s[i+1];
        if (c == 'u' || c == 'n') {
            if(len == 1 || len == 2){
            ans+=len;
            break;
            }
        ans = (ans + (factorial(len)/factorial(len-2))) % MOD;
    }
    }
    if (ans == 0) {
    ans = 1;
    }
    fout << ans << endl;
    return 0;
}
