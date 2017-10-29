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

#define LG 20

vector<int> v[100001];
int P[LG+2][100001], n, L[100001];

void dfs(int x, int p, int l)
{
	P[0][x] = p;
	L[x] = l;
	for (int y: v[x]) {
		if (y == p) continue;
		dfs(y, x, l+1);
	}
}

void make()
{
	for (int i = 1; i < LG; ++i) {
		for (int j = 1; j <= n; ++j) {
			P[i][j] = P[i-1][P[i-1][j]];
		}
	}
}

int lca(int x, int y)
{
	if (L[x] < L[y]) swap(x, y);
	int i, j, k = L[x] - L[y];
	for (i = LG; i >= 0; --i) {
		if (k&(1<<i)) {
			x = P[i][x];
		}
	}
	if (x == y) return x;
	for (i = LG; i >= 0; --i) {
		if (P[i][x] != P[i][y]) {
			x = P[i][x];
			y = P[i][y];
		}
	}
	
	return P[0][x];
}

pii query(int x, int y, int z)
{
	int l1 = lca(x, y);
	int l2 = lca(l1, z);
	return mkp(l1, L[x] - L[l1] + L[y] - L[l1] + L[l1] - L[l2] + L[z] - L[l2]);
}

int M[][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};

int main()
{
	ios_base::sync_with_stdio(false);cout.tie(0);cin.tie(0);

	int i, j, k, x, y, z, q;
	cin >> n >> q;
	for (i = 1; i < n; ++i) {
		cin >> x >> y;
		v[x].pb(y);
		v[y].pb(x);
	}
	dfs(1, 0, 1);
	make();

	int node, ans;
	pii tmp;
	int A[3];
	while (q--) {
		cin >> A[0] >> A[1] >> A[2];
		ans = MOD;
		for (i = 0; i < 6; ++i) {
			tmp = query(A[M[i][0]], A[M[i][1]], A[M[i][2]]);
			//cout << A[M[i][0]] << " " << A[M[i][1]] << " " << A[M[i][2]] << endl;
			if (tmp.sc < ans) {
				ans = tmp.sc;
				node = tmp.fi;
			}
		}
		cout << node << " " << ans << endl;
	}

	return 0;
}
