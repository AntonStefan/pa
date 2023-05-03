#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int task1(int n, int m, int x, vector <int>& p, vector <vector <int> >& g) {
    vector<int> scores(m, 0);
    for (int i = 0; i < m; i++) {  // O(m*n)
        for (int j = 0; j < n; j++) {
            scores[i] += g[j][i];
        }
    }
    int W = n * x;  // bugetul maxim
    vector<vector<int>> dp(m+1 , vector<int>(W+1 , 0));

    // cazul general O(m*W)
    for (int i = 1; i <= m; ++i) {  // m platouri
        for (int cap = 0; cap <= W; ++cap) {  // W lei
            // nu folosesc platoul i => e soluția de la pasul i - 1
            dp[i][cap] = dp[i-1][cap];

			// daca avem buget pentru platoul curent il adaugam la score
            if (cap - p[i-1] >= 0) {
                int sol_aux = dp[i-1][cap - p[i-1]] + scores[i-1];
                dp[i][cap] = max(dp[i][cap], sol_aux);
            }
        }
    }
    return dp[m][W];
}


int task2(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
    vector<int> scores(m, 0);
    for (int i = 0; i < m; i++) {  // O(m*n)
        for (int j = 0; j < n; j++) {
            scores[i] += g[j][i];
        }
    }
    int W = n * x;  // bugetul maxim
    vector<vector<int>> dp(m+1 , vector<int>(W+1 , 0));

    // cazul general O(m*W)
    for (int i = 1; i <= m; ++i) {
        for (int cap = 0; cap <= W; ++cap) {
            // nu folosesc platoul i => e soluția de la pasul i - 1
            dp[i][cap] = dp[i-1][cap];

			// daca avem buget pentru 2 platouri adaugam 2 daca nu verificam pentru 1
            if (cap - p[i-1] >= 0) {
				if(cap - 2*p[i-1] >= 0) {
					int sol_aux = dp[i-1][cap - 2*p[i-1]] + 2*scores[i-1];
					dp[i][cap] = max(dp[i][cap], sol_aux);
				}
				int sol_aux = dp[i-1][cap - p[i-1]] + scores[i-1];
                dp[i][cap] = max(dp[i][cap], sol_aux);
            }
        }
    }
    return dp[m][W];
}

int task3(int n, int m, int x, vector <int> &p, vector <vector <int> > &g) {
	int W = n * x;
    vector<int> scores(m, 0);  // O(m*n)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scores[i] += g[j][i];
        }
    }

	vector<int> newscores(0, 0);  // O(m) si spatial O(2*m)
    for (int i = 0; i < m; i++) {
        newscores.push_back(scores[i]);
		newscores.push_back(scores[i]);
        }

	vector<int> newprices(0, 0);  // O(m) si spatial O(2*m)
	for (int i = 0; i <m ; i++) {
		newprices.push_back(p[i]);
		newprices.push_back(p[i]);
	}
    // dp[i][j][k] obine scorul maxim folosind
    // 2*m platouri, cu bugetul total W, si un numar limitat de platouri n
    vector<vector<vector<int>>> dp(
        2*m + 1, vector<vector<int>>(
                   W + 1,
                   vector<int>(n + 1, 0)));

    // pentru fiecare platou  O(2*m*W*n)
    for (int i = 1; i <= 2* m; i++) {
        // pentru fiecare pret
        for (int j = 1; j <= W; j++) {
		  // pentru fiecare maxim n platouri
			for (int k = 1; k <= n; k++) {
				dp[i][j][k] = dp[i-1][j][k];

				// daca avem buget pentru platou
				if (j - newprices[i - 1] >= 0) {
				int sol_aux = dp[i - 1][j - newprices[i - 1]][k - 1] + newscores[i - 1];
				dp[i][j][k] = max(dp[i][j][k], sol_aux);
				}
			}
        }
    }
    // scorul maxim obtinut folosind n platouri
    return dp[2*m][W][n];
}

int main() {
	freopen("sushi.in", "r", stdin);
	freopen("sushi.out", "w", stdout);

	int task;  // task number

	int n;  // number of friends
	int m;  // number of sushi types
	int x;  // how much each of you is willing to spend

	vector <int> prices;  // prices of each sushi type
	// the grades you and your friends gave to each sushi type
	vector <vector <int> > grades;

	cin >> task;
	cin >> n >> m >> x;

	prices.assign(m, 0);
	grades.assign(n, vector <int> (m, 0));

	// price of each sushi
	for(int i = 0; i < m; ++i) {
		cin >> prices[i];
	}

	// each friends rankings of sushi types
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			cin >> grades[i][j];
		}
	}

	int ans = -1;

	switch(task) {
		case 1:
			ans = task1(n, m, x, prices, grades);
			break;
		case 2:
			ans = task2(n, m, x, prices, grades);
			break;
		case 3:
			ans = task3(n, m, x, prices, grades);
			break;
		default:
			cout << "wrong task number" << endl;
	}

	cout << ans << endl;

	return 0;
}
