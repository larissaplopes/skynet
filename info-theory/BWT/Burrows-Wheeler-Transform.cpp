#include <bits/stdc++.h> //import only necessary libraries

#define str first
#define idx second

using namespace std; //delete std

typedef pair<string ,int> si;

si BWTransform(string &s) //improve: suffix-array O(N) time and space
{
    int ix; string enc;
    vector<string> v;

    for (int i = 0; i < s.size(); i++)
        v.push_back(s.substr(i,s.size()-i)+s.substr(0, i));

    sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); i++) { 
        if (v[i] == s) ix = i;
        enc += v[i][v[i].size()-1];
    }

    return si(enc, ix);
}

string BWTransformInverse(si in) //naive
{
    int f[in.str.size()], v[in.str.size()];
    string sorted = in.str;

    sort(sorted.begin(), sorted.end()); //sorting
    
    memset(v, 0, sizeof v);
    for (int i = 0; i < in.str.size(); i++) //creating map function
        for (int j = 0; j < sorted.size(); j++) 
            if (in.str[i] == sorted[j] && v[j] == 0) {
                f[i] = j;
                v[j] = 1;
                break;
            }

    string I;
    int ix = in.idx;

    while (I.size() != in.str.size()) //decoding
    {
        int i;
        for (i = 0; f[i] != ix; i++);
        I += in.str[i];
        ix = i;
    }

    return I;
}

int main()
{
    string s = "quequalquasequando";
    si r = BWTransform(s);
    cout << r.str << " " << r.idx << endl;
    cout << BWTransformInverse(r) << endl;

    s = "a_asa_da_casa";
    r = BWTransform(s);
    cout << r.str << " " << r.idx << endl;
    cout << BWTransformInverse(r) << endl;

    return 0;
}