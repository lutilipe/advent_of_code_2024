#include <bits/stdc++.h>

using namespace std;

#define int            long long int
#define F              first
#define S              second
#define pb             push_back
#define si             set <int>
#define vi             vector <int>
#define vii            vector <vector <int>>
#define pii            pair <int, int>
#define vpi            vector <pii>
#define vpp            vector <pair<int, pii>>
#define mii            map <int, int>
#define mpi            map <pii, int>
#define spi            set <pii>
#define endl           "\n"
#define sz(x)          ((int) x.size())
#define all(p)         p.begin(), p.end()
#define double         long double
#define que_max        priority_queue <int>
#define que_min        priority_queue <int, vi, greater<int>>
#define bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)
#define ANS(ans)       cout << ans << endl
#define print(a)       for(auto x : a) cout << x << " "; cout << endl
#define print1(a)      for(auto x : a) cout << x.F << " " << x.S << endl
#define print2(a,x,y)  for(int i = x; i < y; i++) cout<< a[i]<< " "; cout << endl
#define REPL(i,a,b)    for (int i = a; i < b; i++)
#define REPR(i,a,b)    for (int i = a-1; i >= b; i--)
#define PI             3.141592653589793238
#define INF            LONG_LONG_MAX
#define MOD            1e9+7
#define IMAX           LONG_LONG_MAX
#define IMIN           LONG_LONG_MIN

inline int power(int a, int b) {
	int x = 1;
	while (b)
	{
		if (b & 1) x *= a;
		a *= a;
		b >>= 1;
	}
	return x;
}

template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args) {
	const char* comma = strchr (names + 1, ',');
	cout.write (names, comma - names) << " : " << arg1 << " | "; __f (comma + 1, args...);
}

const int N = 200005;

bool isInBounds(vector<vector<char>>& m, int i, int j) {
    return i >= 0 && i < m.size() && j >= 0 && j < m[0].size();
}

void insertAntinode(vector<vector<char>>& a, int i, int dx, int j, int dy, int& count) {
    while (isInBounds(a, i, j)) {
        if (a[i][j] != '#') {
            a[i][j] = '#';
            count++;
        }
        i += dx;
        j += dy;
    }
}

void solve() {
    string line;
    vector<string> m;

    unordered_map<char, vector<pii>> antennas;

    while (cin >> line) {
        REPL(i, 0, line.size()) {
            if (line[i] != '.') {
                antennas[line[i]].push_back(make_pair(m.size(), i));
            }
        }

        m.push_back(line);
    }

    int count = 0;

    vector<vector<char>> antinodes(m.size(), vector<char>(m[0].size(), '.'));

    for (auto& antenna : antennas) {
        REPL(i, 0, antenna.S.size()) {
            pii curr = antenna.S[i];
            REPL(j, 0, antenna.S.size()) {
                if (i == j) continue;
                pii toCompare = antenna.S[j];
                int dx = abs(curr.F - toCompare.F);
                int dy = abs(curr.S - toCompare.S);

                if (curr.F > toCompare.F && curr.S > toCompare.S) {
                    insertAntinode(antinodes, curr.F, dx, curr.S, dy, count);
                    insertAntinode(antinodes, toCompare.F, -dx, toCompare.S, -dy, count);
                } else if (curr.F == toCompare.F && curr.S > toCompare.S) {
                    insertAntinode(antinodes, curr.F, 0, curr.S, dy, count);
                    insertAntinode(antinodes, toCompare.F, 0, toCompare.S, -dy, count);
                } else if (curr.F < toCompare.F && curr.S > toCompare.S) {
                    insertAntinode(antinodes, curr.F, -dx, curr.S, dy, count);
                    insertAntinode(antinodes, toCompare.F, dx, toCompare.S, -dy, count);
                } else if (curr.F < toCompare.F && curr.S == toCompare.S) {
                    insertAntinode(antinodes, curr.F, -dx, curr.S, 0, count);
                    insertAntinode(antinodes, toCompare.F, dx, toCompare.S, 0, count);
                } else if (curr.F < toCompare.F && curr.S < toCompare.S) {
                    insertAntinode(antinodes, curr.F, -dx, curr.S, -dy, count);
                    insertAntinode(antinodes, toCompare.F, dx, toCompare.S, dy, count);
                } else if (curr.F == toCompare.F && curr.S < toCompare.S) {
                    insertAntinode(antinodes, curr.F, 0, curr.S, -dy, count);
                    insertAntinode(antinodes, toCompare.F, 0, toCompare.S, dy, count);
                } else if (curr.F > toCompare.F && curr.S < toCompare.S) {
                    insertAntinode(antinodes, curr.F, dx, curr.S, -dy, count);
                    insertAntinode(antinodes, toCompare.F, -dx, toCompare.S, dy, count);
                } else if (curr.F > toCompare.F && curr.S == toCompare.S) {
                    insertAntinode(antinodes, curr.F, dx, curr.S, 0, count);
                    insertAntinode(antinodes, toCompare.F, -dx, toCompare.S, 0, count);
                }
            }
        }
    }

    cout << count << endl;
}

int32_t main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    #ifndef ONLINE_JUDGE
        freopen("input.txt",  "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

	int t = 1;
	// cin >> t;
	while (t--) solve();

	return 0;
}
