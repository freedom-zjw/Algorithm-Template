/*
有两只青蛙，在地球的同一个纬度上，但是它们所在经度位置不同。青蛙A一开始在位置x，每次向西跳m米；青蛙B一开始在位置y，每次向西跳n米；这个纬度绕地球一圈是L米。两只青蛙一起跳，问它们最早会在跳几次后相遇，如果不能相遇则输出“Impossible”。
x、y、m、n、L<=2100000000，x!=y。
设它们一起跳了p次，另有一整数q，可以列出方程：(x+p∙m)-(y+p∙n)=q∙L。写成关于p、q的二元一次方程是：(m–n)∙p+L∙q=y–x。
设A=(m–n),B=L ,C=y–x。这道题目就可以转化为求方程A∙p+B∙q=C的p不小于0且最小的解。
这是可以运用拓展欧几里得算法做到的。我们先求出A∙p0+B∙q0=(A,B)的解，如果C mod(A,B)≠0，则无解；否则p=p0∙C/((A,B))就是一个解。然后我们发现，如果给p减去   B/d 同时给q加上 A/d ，等式仍然成立，所以我们可以把p对 B/d 取模，得到想要的答案。
 */
#include<algorithm>
#include<iostream>
#include<cstdio>
using namespace std;
long long extended_gcd( long long A , long long B , long long &x , long long &y ) {
	//solve ax+by=gcd(a,b)
	if ( B == 0 ) {
		x = 1;
		y = 0;
		return A;
	}
	long long d = extended_gcd( B , A % B , x , y );
	long long tmp = x;
	x = y;
	y = tmp - A / B * y;
	return d;
}
void caln( long long A , long long B , long long C ) {
	long long x , y;
	long long d = extended_gcd( A , B , x , y );
	if ( d == 0 || C % d != 0 ) {
		cout << "Impossible" << endl;
		return;
	}
	x = x * ( C / d );
	long long p = abs( B / d );
	cout << ( x % p + p ) % p << endl;
}
void solve() {
	long long x , y , m , n , L;
	cin >> x >> y >> m >> n >> L;
	caln( m - n , L , y - x );
}
int main() {
	solve();	
	return 0;
}
