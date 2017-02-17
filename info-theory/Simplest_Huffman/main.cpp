#include "HuffmanCompressor.cpp"

int main()
{
    HuffmanCompressor HC("AAAAAAAAAAAAAAABBBBBBBBBBBBBBCDEFGASFSPKKASPFKOASJFIHASIFHASOIFJIASIOFJIAOSHIJK");
    HC.PrintHuffmanCode();
    HC.PrintEncodedMessage();
    HC.Compress();
    return 0;
}