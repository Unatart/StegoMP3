#ifndef HEAD_HPP
#define HEAD_HPP

#include "basehead.hpp"
#include "rawhead.hpp"


class Header : public BaseHeader{
public:

    Header() = default;
    Header(const RawHeader&);

    unsigned frame_size() const;
    bool is_correct() const;
    bool crc_present() const;
    bool padding_present() const;

    friend std::istream& operator>>(std::istream&, Header&);
private:
    bool correct = false;
    bool crc = false;
    unsigned bitrate = 0;
    unsigned samplerate = 0;
    bool padding = false;
};


bool Header::is_correct() const {
    return correct;
}

bool Header::crc_present() const {
    return crc;
}

bool Header::padding_present() const {
    return padding;
}

unsigned Header::frame_size() const {
    return BITS_PER_SAMPLE * bitrate / samplerate + (unsigned) padding;
}

std::istream& operator>>(std::istream& src, Header& dst) {

    RawHeader buffer;
    src >> buffer;

    dst.bitrate = buffer.bitrate();
    dst.samplerate = buffer.samplerate();
    dst.correct = buffer.is_correct();
    dst.crc = buffer.crc_present();
    dst.padding = buffer.padding_present();

    return src;
}

Header::Header(const RawHeader& init) {
    correct = init.is_correct();
    crc = init.crc_present();
    bitrate = init.bitrate();
    samplerate = init.samplerate();
    padding = init.padding_present();
}

#endif // HEAD_HPP
