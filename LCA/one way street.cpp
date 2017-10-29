#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define ll long long int
#define ld long double
#define pb push_back
#define mkp make_pair
#define pii pair<int, int> 
#define pll pair<long long int, long long int>
#define sci(x) scanf("%d", &x)
#define scl(x) scanf("%lld", &x)
#define fi first
#define sc second
#define deb 0

vector<int> v[100001];
int disc[100001], low[100001], L[100001];
int P[23][100001], timer;
set<pii> bri;

void dfs(int x, int p, int l)
{
	L[x] = l;
	low[x] = disc[x] = ++timer;
	P[0][x] = p;
	for (int y: v[x]) {
		if (y == p) continue;
		if (disc[y] == 0) {
			dfs(y, x, l+1);
		}
		low[x] = min(low[x], low[y]);
		if (low[y] > disc[x]) {
			bri.insert(mkp(x, y));
			bri.insert(mkp(y, x));
		}
	}
}

void make(int n)
{
	for (int i = 1; i <= 20; ++i) {
		for (int j = 1; j <= n; ++j) {
			P[i][j] = P[i-1][P[i-1][j]];
		}
	}
}

int lca(int x, int y)
{
	if (L[x] < L[y]) swap(x, y);
	int i, j, k = L[x] - L[y];
	for (i = 20; i >= 0; --i) {
		if (k&(1<<i)) x = P[i][x];
	}
	if (x == y) return x;
	for (i = 20; i >= 0; --i) {
		if (P[i][x] != P[i][y]) {
			x = P[i][x];
			y = P[i][y];
		}
	}
	return P[0][x];
}

map<pii, int> idx, cnt;
set<pii > pq;
int D[100001], T[100001];

int main()
{
	ios_base::sync_with_stdio(false);cout.tie(0);cin.tie(0);

	int n, m, i, j, k, x, y, z, a, b, c;
	cin >> n >> m;
	string ans = "";
	for (i = 0; i < m; ++i) {
		cin >> x >> y;
		v[x].pb(y);
		v[y].pb(x);
		idx[mkp(x, y)] = i;
		cnt[mkp(x, y)]++;
		cnt[mkp(y, x)]++;
		ans += 'B';
	}
	for (i = 1; i <= n; ++i) {
		if (!disc[i]) dfs(i, 0, 1);
	}
	make(n);
	for (auto it: cnt) {
		if (it.sc > 1) {
		    	x = it.fi.fi;
		    	y = it.fi.sc;
			if (bri.count(mkp(x, y))) bri.erase(bri.find(mkp(x, y)));
			if (bri.count(mkp(y, x))) bri.erase(bri.find(mkp(y, x)));
		}
	}
	for (i = 1; i <= n; ++i) {
		T[i] = MOD;
	}
	int q;
	cin >> q;
	while (q--) {
		cin >> x >> y;
		z = lca(x, y);
		if (L[x] != L[z]) {
			pq.insert(mkp(-L[x], x));
			if (L[z] < T[x]) {
				D[x] = 1; 
				T[x] = L[z];
			}
		}
		if (L[y] != L[z]) {
			pq.insert(mkp(-L[y], y));
			if (L[z] < T[y]) {
				D[y] = 0; 
				T[y] = L[z];
			}
		}
	}
	
	while (!pq.empty()) {
		x = (*pq.begin()).sc;
		pq.erase(pq.begin());
		y = P[0][x];
		if (bri.count(mkp(x, y))) {
			if (D[x] == 1) {
				if (idx.find(mkp(x, y)) != idx.end()) ans[idx[mkp(x, y)]] = 'R';
				else ans[idx[mkp(y, x)]] = 'L';
			} else {
				if (idx.find(mkp(x, y)) != idx.end()) ans[idx[mkp(x, y)]] = 'L';
				else ans[idx[mkp(y, x)]] = 'R';
			}
		}
		if (L[y] == T[x]) continue;
		pq.insert(mkp(-L[y], y));
		if (T[x] < T[y]) {
			D[y] = D[x];
			T[y] = T[x];
		}
	}
	cout << ans << endl;

	return 0;
}
