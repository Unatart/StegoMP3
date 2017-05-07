#include "head.h"
#include "mp3_encoder.h"
#include "mp3_decoder.h"

int main() {

    std::string str;
    std::getline(std::cin, str);

    mp3_encoder encoder;
    encoder.set_input_file("C:/Users/unata/Desktop/MISSION COMPLETE.mp3");
    encoder.set_output_file("C:/Users/unata/Desktop/copy2.mp3");
    encoder.set_message(str);
    encoder.encode();

    mp3_decoder decoder;
    decoder.set_input_file("C:/Users/unata/Desktop/copy2.mp3");
    std::string message = decoder.decode();;
    std::cout << "message: " << "|" << message << "|" << std::endl;

    return 0;
}
