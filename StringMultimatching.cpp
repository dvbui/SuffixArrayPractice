//
// Created by bui on 5/22/19.
//
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxN = (int) 1e5;
const int maxn = (int) 2e6;
const int alphabet = 256;
int N;
string S,T;
int startingPostion[maxN+1];
int TPosition;
int n;
string s;
int cnt[maxn];
int p[maxn],pn[maxn];
int c[maxn],cn[maxn];
int classes;
void prepareS()
{
    getline(cin,S);

    s="";
    for (int i=1; i<=N; i++)
    {
        getline(cin,S);
        startingPostion[i] = s.size();
        s+=S+'\0';
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

    for (int i=0; i<alphabet; i++)
        cnt[i] = 0;

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

    cout << s;
    for (int i=0; i<n; i++)
        cout << s.substr(p[i],s.size()-p[i]) << '\n';
    cout << '\n';


}
void solve()
{
    prepareS();
    constructSuffixArray();
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