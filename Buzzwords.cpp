#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define ii pair<int,int>
using namespace std;
const int maxn = 2000000;
const int alphabet = 256;
string s;
string t;
int n;
int cnt[maxn],p[maxn],c[maxn];
int cn[maxn],pn[maxn];
int rnk[maxn],lcp[maxn],rlcp[maxn];
int classes;

void solve()
{
    t="";
    for (int i=0; i<s.size(); i++) {
        if ('A' <= s[i] and s[i] <= 'Z')
            t += s[i];
    }
    s=t;
    s+='$';
    n = s.size();
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
                pn[i]+=n;
        }

        /*for (int i=0; i<n; i++)
            cout << pn[i] << ' ';
        cout << '\n';*/

        for (int i=0; i<classes; i++)
            cnt[i] = 0;

        for (int i=0; i<n; i++)
            cnt[c[pn[i]]]++;


        for (int i=1; i<classes; i++)
            cnt[i]+=cnt[i-1];

        //cout << cnt[classes-1] << '\n';

        for (int i=n-1; i>=0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];

        cn[p[0]] = 0;
        classes = 1;

        for (int i=1; i<n; i++)
        {
            ii cur = ii(c[p[i]],c[(p[i]+h)%n]);
            ii prev = ii(c[p[i-1]],c[(p[i-1]+h)%n]);

            if (cur!=prev)
                classes++;

            cn[p[i]] = classes - 1;
        }


        for (int i=0; i<n; i++)
            c[i] = cn[i];

        /*for (int i=0; i<n; i++)
            cout << p[i] << ' ';
        cout << '\n';
        for (int i=0; i<n; i++)
            cout << c[i] << ' ';
        cout << '\n';
        cout << classes << '\n';
        cout << '\n';*/
    }


    /*for (int i=0; i<n; i++)
        cout << s.substr(p[i],s.size()-p[i]) << ' ' << p[i] << '\n';
    cout << '\n';*/

    for (int i=0; i<n; i++)
        rnk[p[i]] = i;

    int k = 0;
    for (int i=0; i<n; i++)
    {
        if (rnk[i] == n-1)
        {
            k=0;
            continue;
        }

        int j = p[rnk[i]+1];

        while (j+k<n and i+k<n and s[i+k]==s[j+k])
            k++;

        lcp[rnk[i]] = k;
        //cout << rnk[i] << ' ' << k << '\n';

        //cout << s.substr(i,s.size()-i) << ' ' << s.substr(j,s.size()-j) << ' ' << rnk[i] << ' ' << lcp[rnk[i]] << '\n';

        if (k)
            k--;
    }


    /*for (int i=0; i<n; i++)
        cout << s[p[rnk[i]]] << ' ' << lcp[i] << '\n';
    cout << '\n';*/

    for (int i=0; i+1<n; i++) {
        cout << s.substr(p[i], s.size() - p[i]) << ' ' << s.substr(p[i + 1], s.size() - p[i + 1]) << ' ' << lcp[i]
             << '\n';
    }


}
int main()
{
    ios_base::sync_with_stdio(0);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    while (getline(cin,s) and s!="")
        solve();

    return 0;
}