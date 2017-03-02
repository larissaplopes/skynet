#include "HuffmanCompressor.cpp"
#include "HuffmanDecompressor.cpp"

int main(int argc, char *argv[])
{
    if (argc < 2) std::cout << "Need filepath!" << std::endl;
    else {
        try {
            HuffmanCompressor HC(argv[1]);
            //HC.PrintEncodedMessage();
            HC.Compress();

            HC.PrintStatistics();
            HuffmanDecompressor HD(argv[1]); 
        } catch (const std::exception& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }
    
    return 0;
}