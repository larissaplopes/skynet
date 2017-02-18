#include "HuffmanCompressor.cpp"

int main(int argc, char *argv[])
{
    std::string in, txt;
    while(std::getline(std::cin, in))
        txt += in+'\n';

    HuffmanCompressor HC(txt);
    //HC.PrintHuffmanCode();
    //HC.PrintEncodedMessage();
    HC.Compress();
    HC.PrintStatistics();
    return 0;
}