#include "head.hpp"
#include "mp3encoder.hpp"
#include "mp3decoder.hpp"
#include "file_func.hpp"

#include <string>
#include <vector>
#include <algorithm>

int main() {

    std::ifstream in("C:/Users/Unatart/Desktop/data2.mp3", std::ios::in | std::ios::binary);
    std::ofstream out("C:/Users/Unatart/Desktop/copy.mp3", std::ios::out | std::ios::binary);

    std::string str;
    std::getline(std::cin, str);

    std::cout << mp3Encoder::is_acceptable_message(in, str) << std::endl;
    mp3Encoder::encode(in, out, str);

    out.close();
    std::ifstream out2("C:/Users/Unatart/Desktop/copy.mp3", std::ios::in | std::ios::binary);

    //mp3Decoder::decode(out2);

    return 0;
}
