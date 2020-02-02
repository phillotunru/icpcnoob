#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define mk make_pair
#define fs first
#define sc second
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int MAKS = 300100;
const int MOD = 1e9+1;
const int INF = 1e9+1;
const ll LINF = 1e17;
int n;
ll maks[MAKS];
pair<ll, ll > a[MAKS];
ld ans;
int main(){
	scanf("%d", &n);
	for (int i= 0; i < n; i++){
		scanf("%lld%lld", &a[i].fs, &a[i].sc);
		if (a[i].sc < a[i].fs) swap(a[i].sc, a[i].fs);
	}
	sort(a, a+n);
	for (int i = n - 1; i >= 0; i--){
		maks[i] = max(maks[i+1], a[i].sc);
	}
	for (int i = 0; i <= n-1; i++){
		ans = max(ans, (ld)min(maks[i+1], a[i].sc)*a[i].fs);
		ans = max(ans, ((ld)a[i].fs*(ld)a[i].sc)/2.0);
	}
	cout << fixed << setprecision(1) << ans;
}
