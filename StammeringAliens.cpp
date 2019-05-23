//
// Created by bui on 5/23/19.
//
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;
const int maxn = (int) 2e6;
const int alphabet = 256;
int m;
string s;
int n,k;
int cnt[maxn];
int classes;
int p[maxn],c[maxn],pn[maxn],cn[maxn];
int rnk[maxn],lcp[maxn];

string suffix(int x)
{
    return s.substr(x,s.size()-x);
}

void createSuffixArray()
{
    s+='\0';
    n = s.size();
    for (int i=0; i<alphabet; i++)
        cnt[i] = 0;
    for (int i=0; i<n; i++)
        cnt[s[i]]++;
    for (int i=1; i<alphabet; i++)
        cnt[i] +=cnt[i-1];
    for (int i=0; i<n; i++)
        p[--cnt[s[i]]] = i;

    classes = 1;
    c[p[0]] = 0;
    for (int i=1; i<n; i++)
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
                pn[i] += n;
        }

        for (int i=0; i<classes; i++)
            cnt[i] = 0;

        for (int i=0; i<n; i++)
            cnt[c[pn[i]]]++;

        for (int i=1; i<classes; i++)
            cnt[i] += cnt[i-1];

        for (int i=n-1; i>=0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];

        classes = 1;
        cn[p[0]] = 0;

        for (int i=1; i<n; i++)
        {
            pair<int,int> cur = {c[p[i]],c[(p[i]+h)%n]};
            pair<int,int> prev = {c[p[i-1]],c[(p[i-1]+h)%n]};

            if (cur!=prev)
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

    k = 0;
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

int check(int x)
{
    int cnt = 0;
    int currentRightMost = 0;
    int result = -1;
    for (int i=0; i+1<n; i++)
        if (lcp[i]>=x)
        {
            cnt++;
            currentRightMost = max(currentRightMost,p[i+1]);
            currentRightMost = max(currentRightMost,p[i]);
        }
        else
        {
            if (cnt>=m-1)
                result = max(result,currentRightMost);
            cnt = 0;
            currentRightMost = -1;
        }

        if (cnt>=m-1)
            result = max(result,currentRightMost);

        return result;
}
void solve()
{
    if (m==1) {
        cout << s.size() << ' ' << 0 << '\n';
        return;
    }

    createSuffixArray();
    createLCP();

    /*for (int i=0; i<n; i++)
        cout << suffix(p[i]) << "\t" << ((i+1==n)?0:lcp[i]) << '\n';*/

    //cout << '\n';

    int dau = 0,cuoi=n;
    do
    {
        int giua=(dau+cuoi)/2;
        if (check(giua)>=0) dau=giua+1;
        else cuoi=giua-1;
    }
    while (dau<=cuoi);

    if (cuoi==0)
        cout << "none\n";
    else
        cout << cuoi << ' ' << check(cuoi) << '\n';
}
int main()
{
    ios_base::sync_with_stdio(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    while (cin >> m >> s and m!=0)
        solve();

    return 0;
}

