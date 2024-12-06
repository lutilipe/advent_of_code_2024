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

vi reorder(vi& l, unordered_map<int, vi>& adjacency_list) {
    unordered_map<int, int> degrees;
    si validNodes(l.begin(), l.end());
    unordered_map<int, vi> graph;

    for (int node : l) {
        degrees[node] = 0;
        if (adjacency_list.find(node) != adjacency_list.end()) {
            for (int child : adjacency_list[node]) {
                if (validNodes.find(child) != validNodes.end()) {
                    degrees[node]++;
                    graph[child].push_back(node);
                }
            }
        }
    }

    queue<int> q;

    for (int node : l) {
        if (degrees[node] == 0) {
            q.push(node);
        }
    }

    vi sorted;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int child : graph[node]) {
            degrees[child]--;
            if (degrees[child] == 0) {
                q.push(child);
            }
        }
        sorted.push_back(node);
    }

    return sorted;
}

void solve() {
    string line;
    unordered_map<int, vi> adjacency_list;

    while (getline(cin, line) && !line.empty()) {
        istringstream ss(line);
        int a, b;
        char sep;
        ss >> a >> sep >> b;
        adjacency_list[a].push_back(b);
    }

    int c = 0;

    while (getline(cin, line)) {
        if (line.empty()) continue;
        istringstream ss(line);
        int num;
        char sep;

        unordered_map<int, bool> m;
        vi l;
        bool ok = true;

        while (ss >> num) {
            m[num] = true;

            if (adjacency_list.find(num) != adjacency_list.end()){
                for (auto& child : adjacency_list[num]) {
                    if (m.find(child) != m.end()) {
                        ok = false;
                        break;
                    }
                }
            };

            l.push_back(num);
            ss >> sep;
        }

        if (!ok) {
            vi reordered = reorder(l, adjacency_list);
            int middle = reordered.size() / 2;
            c+= reordered[middle];
        }
    }

    cout << c << endl;
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
