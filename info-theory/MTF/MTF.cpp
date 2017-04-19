#include <bits/stdc++.h> //import only necessary libraries

using namespace std; //delete std

typedef pair<string ,int> si;

int *MoveToFront(string M) 
{
    //getting alphabet
    int *ct = new int[256];
    list<int> al;

    for (int i = 0; i < M.size(); i++) ct[M[i]] = 1;
    for (int i = 0; i < 256; i++)
        if (ct[i]) al.push_back(i);

    //moving to front
    int *f = new int[M.size()], fi = 0;
    for (int i = 0; i < M.size(); i++)
    {
        int c = 0; //counting
        for (auto it = al.begin(); it != al.end(); it++, c++)
        {
            if (*it == M[i]) {
                char tmp = *it;
                f[fi++] = c;
                al.erase(it);
                al.push_front(tmp);
            }
        }
    }

    return f;
}

//can be improve
int main()
{
    int *F = MoveToFront("uuunusaadeeloaqqqq");
    for (int i = 0; i < 18; i++)
        cout << F[i] << " "; cout << endl;

    return 0;
}