#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn = 100005;
/*a,b为两个序列，lis记录a中元素在b中的位置，d[i]为
长度i的上升子序列最后一个元素的值，pos[i][j]记录a中
值为i的元素在b中出现的第j个位置的序号*/
int a[maxn], b, lis[maxn*20],d[maxn*20];
vector<int> pos[maxn];
int main(){
    int len_a, len_b;
    scanf("%d%d", &len_a, &len_b);
    for (int i = 1; i <= len_a; i++)
        scanf("%d", a + i);
    for (int i = 1; i <= len_b; i++){
        scanf("%d", &b);
        pos[b+5000].push_back(i);
    }

    int len_lis = 1;
    for (int i = 0; i <= len_a; i++)
        for (int k = pos[a[i]+5000].size() - 1; k >= 0; k--)
            lis[len_lis++] = pos[a[i]+5000][k];

    d[1] = lis[1];
    int max_len_lcs = 1;
    for (int i = 2; i <= len_lis; i++){
/*如果lis[i]大于目前最长子序列的最后一个元素，
把lia[i]附在改序列后边，构成长度+1的最长序列，
同时更新d[]的值.
否则找到d[]中第一个大于lis[i]的位置k，将lis[i]
附在长度为k-1的序列后边，即变为长度为k的序列，因此
更新d[k]的值为lis[i]*/
        if (lis[i] > d[max_len_lcs])
            d[++max_len_lcs] = lis[i];
        else {
            int pos_greater_than_lis_i = lower_bound(d, d + max_len_lcs, lis[i]) - d;
            d[pos_greater_than_lis_i] = lis[i];
        }
    }

    printf("%d\n", max_len_lcs);
    return 0;
}