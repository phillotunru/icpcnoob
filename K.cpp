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
const int MOD = 1e9+7;
const int INF = 1e9+1;
const ll LINF = 1e17;
int l, r, n, q, lazy[2*MAKS], x;
string s;
ll a, b;
struct matrix{
	ll _11, _12, _21, _22;
};
void print(matrix p){
	printf("\n\n%lld %lld\n%lld %lld\n\n", p._11, p._12, p._21, p._22);
	return;
}
matrix A, B, mat[MAKS], I, tree[2*MAKS], tree2[2*MAKS];

matrix kali(matrix a, matrix b){
	matrix p;
	p._11 = a._11*b._11 + a._12*b._21;
	p._12 = a._11*b._12 + a._12*b._22;
	p._21 = a._21*b._11 + a._22*b._21;
	p._22 = a._21*b._12 + a._22*b._22;
	p._11 %= MOD;
	p._12 %= MOD;
	p._21 %= MOD;
	p._22 %= MOD;
	return p;
}
matrix transpose(matrix a){
	matrix p;
	p._11 = a._11;
	p._12 = a._21;
	p._21 = a._12;
	p._22 = a._22;   
	return p;
}
void build(int idx, int l, int r){
	if (l==r){
		tree[idx] = mat[l];
		tree2[idx] = mat[l];
		return;
	}
	int mid = (l+r)/2;
	build(idx*2, l, mid);
	build(idx*2+1, mid+1, r);
	tree[idx] = kali(tree[idx*2], tree[idx*2+1]);
	tree2[idx] = kali(tree2[idx*2+1], tree2[idx*2]);
	return;
}
void propagate(int idx, int l, int r){
	lazy[idx]%= 2;
	if (lazy[idx]==0) return;
	matrix temp = tree[idx];
	tree[idx] = transpose(tree2[idx]);
	tree2[idx] = transpose(temp);
	if (l!=r){
		lazy[idx*2] ^= lazy[idx];
		lazy[idx*2+1] ^= lazy[idx];
	}
	lazy[idx] = 0;
	return;
}
void update(int idx, int l, int r, int a, int b, int val){
	propagate(idx, l, r);
	if (r < a || l > b) return;
	if (a <= l && r <= b){
		lazy[idx] ^= val;
		propagate(idx, l, r);
		return;
	}
	int mid = (l+r)/2;
	update(idx*2, l, mid, a, b, val);
	update(idx*2+1, mid+1, r, a, b, val);
	tree[idx] = kali(tree[idx*2], tree[idx*2+1]);
	tree2[idx] = kali(tree2[idx*2+1], tree2[idx*2]);
	return;
}
matrix query(int idx, int l, int r, int a, int b){
	propagate(idx, l, r);
	if (r < a || l > b) return I;
	if (a <= l && r <=b){
		return tree[idx];
	}
	int mid = (l+r)/2;
	return kali(query(idx*2, l, mid, a, b), query(idx*2+1, mid+1, r, a, b));
}

int main(){
	A._11 = 1;
	A._12 = 0;
	A._21 = 1;
	A._22 = 1;
	B._11 = 1;
	B._12 = 1;
	B._21 = 0;
	B._22 = 1;
	I._11 = 1;
	I._12 = 0;
	I._21 = 0;
	I._22 = 1;
	scanf("%d%d", &n, &q);
	cin >> s;
	for (int i = 1; i <= n; i++){
		if (s[i-1]=='A') mat[i] = A; else mat[i] = B;
	}
	build(1, 1, n);
//	print(tree[1]);
	for (int i = 0; i < q; i++){
		scanf("%d", &x);
		if (x==1){
			scanf("%d%d",&l, &r );
			update(1, 1,n, l, r, 1);
		}else{
			scanf("%d%d%lld%lld", &l, &r, &a, &b);
			matrix p = query(1,1 ,n, l, r);
			ll ans1 = a*p._11 + b*p._21;
			ans1 %= MOD;
			ll ans2 = a*p._12 + b*p._22;
			ans2 %= MOD;
			printf("%lld %lld\n", ans1, ans2);
		//	print(p);
		}
	}
}

