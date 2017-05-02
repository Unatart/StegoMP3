#include "head.hpp"
#include "mp3encoder.hpp"
#include "mp3decoder.hpp"
#include "file_func.hpp"

#include <string>
#include <vector>
#include <algorithm>

int main() {

    std::string str;
    std::getline(std::cin, str);

    std::ifstream in("C:/Users/Unatart/Desktop/mp3stego/MISSION COMPLETE.mp3", std::ios::in | std::ios::binary);

    if(mp3Encoder::is_acceptable_message(in, str) > 0) {
        std::ofstream out("C:/Users/Unatart/Desktop/mp3stego/copy.mp3", std::ios::out | std::ios::binary);
        mp3Encoder::encode(in, out, str);
        std::cout << "Encoding complete" << std::endl;
    } else return -101;

    std::ifstream out2("C:/Users/Unatart/Desktop/mp3stego/copy.mp3", std::ios::in | std::ios::binary);
    std::cout << "Starting decoding" << std::endl;
    mp3Decoder::decode(out2);
    std::cout << "Decoding complete" << std::endl;


    return 0;
}
