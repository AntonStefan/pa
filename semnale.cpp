#include <iostream>
#include<vector>

using namespace std;

const int mod = 1000000007;
const int nmax = 2000;
int dp[2 * nmax + 1][nmax + 1][3];

int type1(int x, int y) {
	dp[0][0][0] = 1;  //  i biti, j de 1, si k pentru 0 sau 1
    for (int i = 0; i < x + y; i++) {  // O((x+y)*y*2)
        for (int j = 0; j <= min(y, i); j++) {
            for (int k = 0; k <= 1; k++) {  // stari pentru bitul precedent
                if (dp[i][j][k] == 0) continue;  // daca 0 urmatoarea iteratie

                // place a 0
                dp[i + 1][j][0] = (dp[i + 1][j][0] + dp[i][j][k]) % mod;

                // place a 1
                if (j < y && k == 0) {
                    dp[i + 1][j + 1][k + 1] =
					(dp[i + 1][j + 1][k + 1] + dp[i][j][k]) % mod;
                }
            }
        }
    }
    return (dp[x + y][y][0] + dp[x + y][y][1]) % mod;
}

int type2(int x, int y) {
	dp[0][0][0] = 1;
    for (int i = 0; i < x + y; i++) {  // O((x+y)*y*3)
        for (int j = 0; j <= min(y, i); j++) {
            for (int k = 0; k <= 2; k++) {  // stari pentru bitul precedent
                if (dp[i][j][k] == 0) continue;

                // place a 0
                dp[i + 1][j][0] = (dp[i + 1][j][0] + dp[i][j][k]) % mod;

                // place a 1
                if (j < y && k <= 1) {
                    dp[i + 1][j + 1][k + 1] =
					(dp[i + 1][j + 1][k + 1] + dp[i][j][k]) % mod;
                }
            }
        }
    }
    return (1ll * dp[x + y][y][0] + dp[x + y][y][1] + dp[x + y][y][2]) % mod;
}

int main() {
    freopen("semnale.in", "r", stdin);
	freopen("semnale.out", "w", stdout);

	int sig_type, x, y;

	cin >> sig_type >> x >> y;

    switch (sig_type) {
		case 1:
			cout << type1(x, y);;
			break;
		case 2:
			cout << type2(x, y);
			break;
		default:
			cout << "wrong task number" << endl;
	}

    return 0;
}
