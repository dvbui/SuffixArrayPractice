//
// Created by bui on 5/20/19.
//
#include <iostream>
#include <cstdio>
#include <vector>
#define ii pair<int,int>

using namespace std;

/**
 * Adapted from https://cp-algorithms.com/string/suffix-array.html
 */
class SuffixArray
{
private:
    static const int alphabet = 256;
    int n;
    string s;
    vector<int> array;

    void suffixArrayFirstPass(vector<int>& currentResult,vector<int>& currentClass,vector<int>& cnt)
    {
        for (int i=0; i<n; i++)
            cnt[s[i]]++;
        for (int i=1; i<alphabet; i++)
            cnt[i] = cnt[i-1];
        for (int i=0; i<n; i++)
        {
            cnt[s[i]]--;
            currentResult[i] = cnt[s[i]];
        }
        int numberOfCurrentClass = 1;
        currentClass[currentResult[0]] = 0;

        for (int i=1; i<n; i++)
        {
            if (s[currentResult[i]]!=s[currentResult[i-1]])
                numberOfCurrentClass++;
            currentClass[currentResult[i]] = numberOfCurrentClass--;
        }
    }

    void suffixArrayNextPasses(vector<int>& currentResult,vector<int>& currentClass,vector<int>& cnt)
    {
        vector<int> newResult(n),newClass(n);
        for (int h=1; h<n; h<<=1)
        {
            for (int i=0; i<n; i++) {
                newResult[i] = currentResult[i] - h;
                if (newResult[i] < 0)
                    newResult[i] += n;
            }

            cnt.clear();
            cnt.resize(n);

            for (int i=0; i<n; i++)
                cnt[currentClass[newResult[i]]]++;

            for (int i=0; i<n; i++)
                cnt[i] += cnt[i-1];

            for (int i=0; i<n; i++)
            {
                cnt[currentClass[newResult[i]]]--;
                currentResult[cnt[currentClass[newResult[i]]]] = newResult[i];
            }

            newClass[currentResult[0]] = 0;
            int numberOfNewClass = 1;

            for (int i=1; i<n; i++)
            {
                ii cur = {currentClass[currentResult[i]],currentClass[(currentResult[i]+h)%n]};
                ii prev = {currentClass[currentResult[i-1]],currentClass[(currentResult[i-1]+h)%n]};
                if (cur!=prev)
                    numberOfNewClass++;
                newClass[currentResult[i]] = numberOfNewClass-1;
            }

            currentClass.swap(newClass);
        }
    }
    void constructSuffixArray()
    {
        vector<int> currentResult(n),currentClass(n),cnt(max(n,alphabet),0);
        suffixArrayFirstPass(currentResult,currentClass,cnt);
        suffixArrayNextPasses(currentResult,currentClass,cnt);
        array = currentResult;
        array.erase(array.begin());
    }

public:
    SuffixArray()
    {
        this->n = 0;
        this->s = "";
    }

    SuffixArray(string s)
    {
        this->n = s.size();
        this->s = s;
        constructSuffixArray();
    }

};
int main()
{
    ios_base::sync_with_stdio(0);
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);


    return 0;
}
