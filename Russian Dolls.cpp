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

map<int, ll> mp;
int A[2000001];
ll F[2000001];

int main()
{
	ios_base::sync_with_stdio(false);cout.tie(0);cin.tie(0);

	int n, i, j, k, x, y, z, a, b, c;
	cin >> n;
	int mx = 0;
	for (i = 0; i < n; ++i) {
		cin >> x;
		mp[x]++;
		mx = max(mx, x);
	}

	ll ans = 1e18;
	ll cur = 0;
	ll fix = 0;
	for (int last = mx, move = 17; (last >= 1) && (move > 0); --last, --move) {
		int len = 1;
		for (auto it: mp) {
			if (it.fi > last) continue;
			x = it.fi;
			x = max(A[len-1]+1, x-20);
			while (x <= it.fi) A[len++] = x++;
			F[len-1] = it.sc;
		}
		bool possible = true;
		cur = 0;
		for (i = len-1; i > 0; --i) {
			if (F[i] > F[len-1]) {
				if (A[i] == 1 || F[i] > 2 * F[len-1]) {
					possible = false;
					break;
				} 
				F[i-1] = F[i-1] + (F[i] - F[len-1]) * 2;
				cur += (F[i] - F[len-1]);
			}
		}
		if (possible) ans = min(ans, cur + fix);
		mp[last-1] += mp[last]*2;
		fix += mp[last];
	}
	cout << ans << endl;

	return 0;
}
