#include "head.hpp"
#include "mp3encoder.hpp"
#include "mp3decoder.hpp"
#include "file_func.hpp"

#include <chrono>

using namespace std::chrono;

int main() {

    std::string str;
    std::getline(std::cin, str);

    std::ifstream in("C:/Users/Unatart/Desktop/V2/mp3stego/MISSION COMPLETE.mp3", std::ios::in | std::ios::binary);
    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    if(mp3Encoder::is_acceptable_message(in, str) > 0) {
        std::ofstream out("C:/Users/Unatart/Desktop/V2/mp3stego/copy2.mp3", std::ios::out | std::ios::binary);
        t1 = high_resolution_clock::now();
        mp3Encoder::encode(in, out, str);
        std::cout << "Encoding complete" << std::endl;
    } else return -101;

    std::ifstream out2("C:/Users/Unatart/Desktop/V2/mp3stego/copy2.mp3", std::ios::in | std::ios::binary);
    std::cout << "Starting decoding" << std::endl;
    mp3Decoder::decode(out2);
    std::cout << "Decoding complete" << std::endl;

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();

    std::cout << duration << std::endl;

    return 0;
}
