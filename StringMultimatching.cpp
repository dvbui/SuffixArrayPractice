//
// Created by bui on 5/22/19.
//
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
const int maxN = (int) 2e5;
const int maxn = (int) 2e6;
const int alphabet = 256;
int N;
string S,T;
int startingPosition[maxN+1],sz[maxN+1];
int TPosition;
int n;
string s;
int cnt[maxn];
int p[maxn],pn[maxn];
int c[maxn],cn[maxn];
int rnk[maxn];
int lcp[maxn];
int k;
int classes;
set<int> res;
void prepareS()
{
    getline(cin,S);

    s="";
    for (int i=1; i<=N; i++)
    {
        getline(cin,S);
        sz[i] = S.size();
        startingPosition[i] = s.size();
        s+=S+'\1';
        //V[i].clear();
    }
    TPosition = s.size();
    getline(cin,T);
    s+=T+'\0';
    n = s.size();
}
void constructSuffixArray()
{

    for (int i=0; i<alphabet; i++)
        cnt[i] = 0;

    for (int i=0; i<n; i++)
        cnt[s[i]]++;

    for (int i=1; i<alphabet; i++)
        cnt[i]+=cnt[i-1];

    for (int i=0; i<n; i++)
        p[--cnt[s[i]]] = i;

    classes = 1;
    c[p[0]] = 0;

    for (int i=0; i<n; i++)
    {
        if (s[p[i]]!=s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }

    for (int h=1; h<n; h<<=1)
    {
        for (int i=0; i<n; i++)
        {
            pn[i] = p[i] - h;
            if (pn[i]<0)
                pn[i]+=n;
        }

        for (int i=0; i<classes; i++)
            cnt[i] = 0;

        for (int i=0; i<n; i++)
            cnt[c[p[i]]]++;

        for (int i=1; i<classes; i++)
            cnt[i]+=cnt[i-1];

        for (int i=n-1; i>=0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];

        classes = 1;
        cn[p[0]] = 0;

        for (int i=0; i<n; i++)
        {
            pair<int,int> prev = {c[p[i-1]],c[(p[i-1]+h)%n]};
            pair<int,int> cur = {c[p[i]],c[(p[i]+h)%n]};

            if (prev!=cur)
                classes++;
            cn[p[i]] = classes - 1;
        }

        for (int i=0; i<n; i++)
            c[i] = cn[i];
    }

    /*cout << s << '\n';
    for (int i=0; i<n; i++)
        cout << p[i] << ' ' << s.substr(p[i],s.size()-p[i]) << '\n';
    cout << '\n';*/

    for (int i=0; i<n; i++)
        rnk[p[i]] = i;

    k = 0;
    for (int i=0; i<n; i++)
    {
        if (rnk[i]==n-1)
        {
            k=0;
            continue;
        }

        int j=p[rnk[i]+1];

        //cout << i << ' ' << j << ' ' << s.substr(i,s.size()-i) << ' ' << s.substr(j,s.size()-j) << '\n';

        while (i+k<n and j+k<n and s[i+k]==s[j+k])
            k++;

        //cout << rnk[i] << ' ' << k << '\n';

        lcp[rnk[i]] = k;

        if (k>0)
            k--;
    }

    /*for (int i=0; i+1<n; i++)
        cout << lcp[i] << ' ';
    cout << '\n';*/

}

string subString(int x)
{
    return s.substr(x,s.size()-x);
}
void process()
{
    /*cout << "p TPosit \n";
    for (int i=0; i<n; i++)
        cout << (p[i]>=TPosition) << ' ';
    cout << '\n';

    cout << "lcp \n";
    for (int i=0; i<n; i++)
        cout << lcp[i] << ' ';
    cout << '\n';*/

    //cout << s << '\n';
    for (int i=1; i<=N; i++)
    {
        res.clear();
        int j=rnk[startingPosition[i]];
        //cout << i << ' ' << j << '\n';
        int commonLength = lcp[j];
        while (j<n and commonLength>=sz[i])
        {
            if (p[j+1]>=TPosition)
                res.insert(p[j+1]-TPosition);
            j++;
            commonLength=min(commonLength,lcp[j]);
        }
        //cout << "firstLoop " << j << ' ' << commonLength << '\n';

        j=rnk[startingPosition[i]]-1;
        if (j>=0)
        {
            commonLength = lcp[j];
            while (j>=0 and commonLength>=sz[i])
            {
                if (p[j]>=TPosition)
                    res.insert(p[j]-TPosition);
                j--;
                if (j>=0)
                    commonLength=min(commonLength,lcp[j]);
            }
        }

        //cout << "secondLoop " << j << ' ' << commonLength << '\n';
        //cout << '\n';

        for (auto it=res.begin(); it!=res.end(); it++)
            cout << *it << ' ';
        cout << '\n';
    }

}
void solve()
{
    prepareS();
    constructSuffixArray();
    process();
}
int main()
{
    ios_base::sync_with_stdio(0);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    while (cin >> N)
        solve();

    return 0;
}