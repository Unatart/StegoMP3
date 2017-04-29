#include "head.hpp"
#include "coder.hpp"
#include "file_func.hpp"

#include <string>

int main() {

    std::ifstream in("C:/Users/Unatart/Desktop/data2.mp3", std::ios::in | std::ios::binary);
    std::ofstream out("C:/Users/Unatart/Desktop/copy.mp3", std::ios::out | std::ios::binary);
    copy_file(in, out);
    rewind_file(in);
    unsigned number = Decoder::number_of_frames(in);
    // std::cout << "number 1: " << number << std::endl;





    return 0;
}
