#include "file_func.hpp"

void copy_file(std::ifstream& in, std::ofstream& out) {
    // The » stream operator reads formatted input and so it will
    // skip some characters when reading the file.
    char c;
    while(!in.eof())
    {
       in.get(c);
       out.put(c);
    }
}

// now its ok
void rewind_file(std::ifstream& in) {
    in.close();
    in.open("C:/Users/Unatart/Desktop/mp3stego/MISSION COMPLETE.mp3", std::ios::in | std::ios::binary);
}
