#include <bits/stdc++.h>
#include <cstdint> //int types

using namespace std;

int main()
{
    fstream f("FulledByteProblem", ios::out | ios::binary);

    char i = 0; f.write(&i, sizeof(char));
        i = 255; f.write(&i, sizeof(char));
        i = 0; f.write(&i, sizeof(char));
    //for (char i = 0; i < 256; i++) {
        //f.write(&i, sizeof(char));
      ///  cout << (int)((uint8_t)i) << endl;
       // if (i==255) break;
    //}

    return 0;
}