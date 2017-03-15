#include "HuffmanCompressor.cpp"
#include "HuffmanDecompressor.cpp"
#include <chrono>

int main(int argc, char *argv[])
{
    if (argc < 2) std::cout << "Need filepath!" << std::endl;
    else {
        try {
            auto t1 = std::chrono::high_resolution_clock::now();
            HuffmanCompressor HC(argv[1]);
            //HC.PrintHuffmanCode();
            //HC.PrintEncodedMessage();
            HC.Compress();
            HC.PrintStatistics();
            auto t2 = std::chrono::high_resolution_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count() << " ms\n";
            HuffmanDecompressor HD(argv[1]); 
            auto t3 = std::chrono::high_resolution_clock::now();
            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t3-t2).count() << " ms\n";
 
        } catch (const std::exception& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }
    
    return 0;
}