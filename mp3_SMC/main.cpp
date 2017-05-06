#include "head.h"
#include "mp3_encoder.h"
#include "mp3_decoder.h"

int main() {

    std::string str;
    std::getline(std::cin, str);

    mp3_encoder encoder;
    encoder.set_input_file("C:/Users/Unatart/Desktop/V2/mp3stego/MISSION COMPLETE.mp3");
    encoder.set_output_file("C:/Users/Unatart/Desktop/V2/mp3stego/copy2.mp3");
    encoder.set_message(str);
    encoder.encode();

    mp3_decoder decoder;
    decoder.set_input_file("C:/Users/Unatart/Desktop/V2/mp3stego/copy2.mp3");
    std::string message = decoder.decode();;
    std::cout << "message: " << "|" << message << "|" << std::endl;

    return 0;
}
