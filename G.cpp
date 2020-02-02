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
int tree[2*MAKS], lazy[2*MAKS], size[MAKS], a[MAKS], p[MAKS], q[MAKS], n, m, Q;
int x, y, z;
vector < int > b[MAKS];
void propagate(int idx, int l, int r){
	if (lazy[idx]==0) return;
	tree[idx] += lazy[idx];
	if (l!=r){
		lazy[idx*2] += lazy[idx];
		lazy[idx*2+1] += lazy[idx];
	}
	lazy[idx] = 0;
	return;
}
void update(int idx, int l, int r, int a, int b, int val){
	propagate(idx, l, r);
	if (l > b || r < a) return;
	if (a <= l && r <= b){
		lazy[idx] += val;
		propagate(idx, l, r);
		return;
	}
	int mid = (l+ r)/2;
	update(idx*2, l, mid, a, b, val);
	update(idx*2+1, mid+1, r, a, b, val);
	tree[idx] = min(tree[idx*2], tree[idx*2+1]);
	return;
}

int main(){
	scanf("%d%d%d", &n, &m, &Q);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	for (int i = 1; i < n; i++){
		if (a[i]>a[0]) p[0]--;
	}
	for (int i = 0; i < m; i++){
		scanf("%d", &size[i]);
		q[i] = n-size[i];
		b[i].resize(size[i]);
		for (int j = 0; j < size[i]; j++){
			scanf("%d", &b[i][j]);
			if (b[i][j]>a[0]) p[i+1]--;
		}
	}
	q[m] = n;
	for (int i = 0; i <= m; i++){
		update(1, 0, m, i, m, p[i]);
//		printf("p %d %d\n", i, p[i]);
	}
	for (int i = 0; i <= m; i++){
		 update(1, 0, m, i, i, q[i]);
//		 printf("q %d %d\n", i, q[i]);
	}
	propagate(1, 0, m);
//	printf("yo %d\n", tree[1]);
	for (int i = 0; i < Q; i++){
		scanf("%d%d%d", &x, &y, &z);
		if (b[x-1][y-1] > a[0] && z < a[0]) update(1, 0, m, x, m, 1);
		if (b[x-1][y-1] < a[0] && z > a[0]) update(1, 0, m, x, m, -1);
		b[x-1][y-1] = z;
		propagate(1, 0, m);
//		printf("ans %d ", tree[1]);
		if (tree[1]>0) printf("1\n"); else printf("0\n");
	}
}

