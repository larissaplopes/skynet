#include "HuffmanCompressor.cpp"
#include "HuffmanDecompressor.cpp"

int main(int argc, char *argv[])
{

    //try {
        HuffmanCompressor HC(argv[1]);
        //HC.PrintHuffmanCode();
        //HC.PrintEncodedMessage();
        HC.Compress();
        HC.PrintStatistics();
        HuffmanDecompressor HD("./compressed.bin");
    /*} catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }*/
    
    return 0;
}