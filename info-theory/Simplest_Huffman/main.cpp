#include "HuffmanCompressor.cpp"
#include "HuffmanDecompressor.cpp"

//making tests

int main(int argc, char *argv[])
{
    if (argc < 2) std::cout << "Need filepath!" << std::endl;
    else {
        try {
            HuffmanCompressor HC(argv[1]);
            //HC.PrintHuffmanCode();
            HC.PrintEncodedMessage();
            HC.PrintStatistics();
            HC.Compress();
            HuffmanDecompressor HD(argv[1]); 
        } catch (const std::exception& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }
    
    return 0;
}