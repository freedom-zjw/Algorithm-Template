/*中国剩余定理(西方数学史中的叫法)，就是上一题目的一般情况。
设m1,m2...mk是两两互素的正整数，即: gcd(mi, mj) = 1 (其中 i != j, i, j >= 1且 <=k).
则同余方程组:
x ≡ a1(mod m1)
x ≡ a2(mod m2)
... ...
x ≡ ak(mod mk)
存在唯一[m1,m2...mk]使方程成立.
解法同物不知数是一致的.我们可以稍微模仿一下.
唯一的难题就是如何把上面70, 15, 21的求法,对应到一般情况来.
假设: N1, N2, ... ,Nk.就是对应的权值, 满足如下条件:
N1 能够被 m2, m3..., mk整除,但是除以m1正好余1.
N2 能够被 m1, m3..., mk整除,但是除以m2正好余1.
... ...
Nk能够被m1, m2,...,mk-1整除,但是除以mk正好余1.
N1->Nk如果求出来了,那么假设:
x1 = N1*a1 + N2*a2 + ... + Nk*ak就是我们要求的x一个解, 同物不知数一样,我们把x1 mod (m1*m2*...*mk)的结果
就是x的最小整数解,若为负数,则再加上一个m1*m2*...*mk.因为加减整数倍个m1*m2*...*mk所得结果都是x的解.
所以问题只剩下一个,就是求N1, N2,...,Nk.
怎么求呢?我需要先化简一番:
设m = m1*m2*...*mk, L, J为任意整数.
因为Ni能被m1, m2,...,mi-1, mi+1,...,mk整除(其中i+1<k)
因此: Ni = m/mi *L
又因为Ni除以mi余1
因此: Ni = mi*J + 1
即: mi*J + 1 = m/mi *L ==> (-mi)*J + m/mi*L = 1
而m1-->mk这些数都是互质数,所以(-mi) 同 m/mi也是互质数.即:
gcd(mi, m/mi) = 1也就是说:
 (m/mi)*L + (-mi)*J  = gcd(m/mi, -mi)==>其中-mi和m/mi都是已知的,J和L未知
这就是经典扩展欧几里德定理的原型(由定理知J和L是唯一的, 因此,N1-->Nk有唯一解).
按照扩展欧几里德定理求解即可.
扩展欧几里德定理：
a和b都是不全为0的正整数，则：
a*x + b*y = gcd(a, b)
存在唯一的x, y使得上面等式成立。
(当然，容易得知，如果，a和b中有负数，那么也是成立的。)
本题中，m/mi相当于a, -mi相当于b, L相当于x, J相当于y。求出L, J就能求出Ni。
此时Ni求解完毕.
我们要求的x的最小整数解也就呼之欲出了.*/

#include <iostream>
using namespace std;
//参数可为负数的扩展欧几里德定理
void exOJLD(int a, int b, int &x, int &y){
    //根据欧几里德定理
    if(b == 0){//任意数与0的最大公约数为其本身。
        x = 1;
        y = 0;
    }else{
        int x1, y1;
        exOJLD(b, a%b, x1, y1);
        if(a*b < 0){//异号取反
            x = - y1;
            y = a/b*y1 - x1;
        }else{//同号
            x = y1;
            y = x1 - a/b* y1;
        }
    }
}
//剩余定理
int calSYDL(int a[], int m[], int k){
    int N[k];//这个可以删除
    int mm = 1;//最小公倍数
    int result = 0;
    for(int i = 0; i < k; i++){
        mm *= m[i];
    }
    for(int j = 0; j < k; j++){
        int L, J;
        exOJLD(mm/m[j], -m[j], L, J);
        N[j] = m[j] * J + 1;//1
        N[j] = mm/m[j] * L;//2 【注】1和2这两个值应该是相等的。
        result += N[j]*a[j];
    }
    return (result % mm + mm) % mm;//落在(0, mm)之间，这么写是为了防止result初始为负数，本例中不可能为负可以直接 写成：return result%mm;即可。
}


int main(){
    int a[3] = {2, 3, 2};
    int m[3] = {3, 5, 7};    
    cout<<"结果:"<<calSYDL(a, m, 3)<<endl;
}