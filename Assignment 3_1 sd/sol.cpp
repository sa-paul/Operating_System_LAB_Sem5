#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ll n, m, k;
    cin >> n >> m;
    ll arr[n][m];
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) cin >> arr[i][j];
    }
    
    cin >> k;

    vector<ll> count((1LL << m) + 10, 0);
    for (ll i = 0; i < n; i++) {
        ll x = 0;
        for (ll j = 0; j < m; j++) x += arr[i][j] * (1LL << j);
        count[x]++;
    }

    ll ans = 0;
    for (ll i = 0; i < (1LL << m); i++) {
        ll req = m - __builtin_popcount(i);
        if ((k < req) || ((k - req) & 1LL)) continue;
        ans = max(ans, count[i]);
    }

    cout << ans << endl;
    return 0;
}