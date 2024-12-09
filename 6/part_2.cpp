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

vector<char> moves = {'^', '>', 'v', '<'};

pii getCoords(int x, int y, int direction) {
    int sx = x + (moves[direction] == '^' ? -1 : moves[direction] == 'v' ? 1 : 0);
    int sy = y + (moves[direction] == '>' ? 1 : moves[direction] == '<' ? -1 : 0);
    return make_pair(sx, sy);
}

bool isInLoop(vector<string> board, int startX, int startY, int startDir) {
    set<tuple<int, int, int>> visited;
    int x = startX, y = startY, direction = startDir;

    while (true) {
        if (visited.count({x, y, direction})) return true;
        visited.insert({x, y, direction});

        auto [nx, ny] = getCoords(x, y, direction);

        if (nx < 0 || nx >= board.size() || ny < 0 || ny >= board[0].size()) return false;

        if (board[nx][ny] == '#') {
            direction = (direction + 1) % 4;
        } else {
            x = nx;
            y = ny;
        }
    }
}

void solve() {
    vector<string> board;
    string row;
    int startX = -1, startY = -1, startDir = -1;

    while (cin >> row) {
        for (int i = 0; i < row.size(); i++) {
            char c = row[i];
            if (c != '.' && c != '#') {
                startX = board.size();
                startY = i;
                for (int j = 0; j < moves.size(); j++) {
                    if (c == moves[j]) startDir = j;
                }
            }
        }
        board.push_back(row);
    }

    spi paths;
    int x = startX;
    int y = startY;
    int direction = startDir;

    while (true) {
        pii newPos = getCoords(x, y, direction);
        if (newPos.F < 0 || newPos.F >= board.size() || newPos.S < 0 || newPos.S >= board[0].size()) {
            break;
        }

        if (board[newPos.F][newPos.S] == '#') {
            direction = (direction+1) % 4;
            newPos = make_pair(x,y);
        }

        x = newPos.F;
        y = newPos.S;

        paths.insert(make_pair(x, y));
    }

    int possiblePositions = 0;

    for (auto& [i, j] : paths) {
        if (board[i][j] == '.' && !(i == startX && j == startY)) {
            board[i][j] = '#';
            if (isInLoop(board, startX, startY, startDir)) {
                possiblePositions++;
            }
            board[i][j] = '.';
        }
    }

    cout << possiblePositions << endl;
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
