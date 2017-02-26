#include "HuffmanCompressor.cpp"
#include "HuffmanDecompressor.cpp"

//making tests
//TODO:
//solve 1 symbol problem
//shellcontrole

int main(int argc, char *argv[])
{
    try {
        HuffmanCompressor HC(argv[1]);
        //HC.PrintHuffmanCode();
        //HC.PrintEncodedMessage();
        HC.Compress();
        HC.PrintStatistics();

        HuffmanDecompressor HD(argv[1]); 
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}