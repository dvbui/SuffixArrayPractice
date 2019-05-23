//
// Created by bui on 5/23/19.
//
#include <iostream>
#include <cstdio>
#include <string>
#define int long long
using namespace std;
const int maxn = 100001;
const int alphabet = 256;
int n;
string s;
int cnt[maxn];
int p[maxn],c[maxn],classes;
int pn[maxn],cn[maxn];
int rnk[maxn],lcp[maxn];

string suffix(int x)
{
    return s.substr(x,s.size()-x);
}
void createSuffixArray()
{
    s+='\0';
    n=s.size();
    for (int i=0; i<alphabet; i++)
        cnt[i] = 0;

    for (int i=0; i<n; i++)
        cnt[s[i]]++;

    for (int i=1; i<alphabet; i++)
        cnt[i] += cnt[i-1];

    for (int i=0; i<n; i++)
        p[--cnt[s[i]]] = i;

    classes = 1;
    c[p[0]] = 0;
    for (int i=1; i<n; i++) {
        if (s[p[i]] != s[p[i - 1]])
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
            cnt[i] += cnt[i-1];

        for (int i=n-1; i>=0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];

        classes = 1;
        cn[p[0]] = 0;

        for (int i=1; i<n; i++)
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
}
void createLCP()
{
    for (int i=0; i<n; i++)
        rnk[p[i]] = i;

    int k = 0;
    for (int i=0; i<n; i++)
    {
        if (rnk[i]==n-1)
        {
            k=0;
            continue;
        }

        int j=p[rnk[i]+1];
        while (i+k<n and j+k<n and s[i+k]==s[j+k])
            k++;

        lcp[rnk[i]] = k;

        if (k>0)
            k--;
    }
}
void solve()
{
    cin >> s;
    createSuffixArray();
    createLCP();
    //for (int i=0; i<n; i++)
    //    cout << suffix(p[i]) << '\t' << lcp[i] << '\n';

    int res = 0;
    for (int i=0; i+1<n; i++)
        if (lcp[i+1]>lcp[i])
            res+=lcp[i+1]-lcp[i];
    cout << res << '\n';



}
main()
{
    ios_base::sync_with_stdio(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int t;
    cin >> t;
    for (int i=1; i<=t; i++)
        solve();


    return 0;
}
