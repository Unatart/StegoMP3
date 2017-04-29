#ifndef RAWHEAD_HPP
#define RAWHEAD_HPP

#include "basehead.hpp"
const unsigned KB = 1024;

class  RawHeader : public BaseHeader{
public:
    unsigned bitrate() const;
    unsigned samplerate() const;

    bool is_correct() const;
    bool crc_present() const;
    bool padding_present() const;
    bool is_valid_header() const;

    friend std::istream& operator >>(std::istream&, RawHeader&);
    void read_byte(std::ifstream&);

    const unsigned char& operator [](unsigned position) const;
    unsigned char &operator [](unsigned position);

private:
    unsigned char data[RAW_HEADER_SIZE];

};

bool RawHeader::is_correct() const{
    if ((data[0] & 0xFF) != 0xFF) {
        return false;
    }
    if ((data[1] & 0xE0) != 0xE0) {
        return false;
    }                           // check for starting 11 '1'

    return (data[1] & 0x1A) == 0x1A; // check format for mpeg-1 layer 3
}

bool RawHeader::crc_present() const {
    return data[1] & 0x01;
}

bool RawHeader::padding_present() const {
    return data[2] & 0x02;
}

unsigned RawHeader::bitrate() const {
    unsigned char chk = data[2] & 0xF0;
    if (chk == 0x10) {
        return 32 * KB;
    }
    if (chk == 0x20) {
        return 40 * KB;
    }
    if (chk == 0x30) {
        return 48 * KB;
    }
    if (chk == 0x40) {
        return 56 * KB;
    }
    if (chk == 0x50) {
        return 64 * KB;
    }
    if (chk == 0x60) {
        return 80 * KB;
    }
    if (chk == 0x70) {
        return 96 * KB;
    }
    if (chk == 0x80) {
        return 112 * KB;
    }
    if (chk == 0x90) {
        return 128 * KB;
    }
    if (chk == 0xA0) {
        return 160 * KB;
    }
    if (chk == 0xB0) {
        return 192 * KB;
    }
    if (chk == 0xC0) {
        return 224 * KB;
    }
    if (chk == 0xD0) {
        return 256 * KB;
    }
    if (chk == 0xE0) {
        return 320 * KB;
    }
    // for incorrect data
    return 0;
}

unsigned RawHeader::samplerate() const {
    unsigned char chk = data[2] & 0x0C;
    if (chk == 0x00) {
        return 44100;
    }
    if (chk == 0x04) {
        return 48000;
    }
    if (chk == 0x08) {
        return 32000;
    }
    return 0; // incorrect data
}

void RawHeader::read_byte(std::ifstream& src) {
    for (unsigned i = 0; i < 3; ++i) {
        data[i] = data[i + 1];
    }
    src >> data[3];
}

const unsigned char& RawHeader::operator [](unsigned position) const {
    return *(data + position);
}

unsigned char& RawHeader::operator [](unsigned position) {
    return *(data + position);
}

bool RawHeader::is_valid_header() const {
    return (is_correct() && bitrate() && samplerate());
}

std::istream& operator>>(std::istream& src, RawHeader& dst) {
    //The » stream operator reads formatted input and so it will
    // skip some characters when reading the file.
    char bufdata;
    for (unsigned i = 0; i < RAW_HEADER_SIZE; ++i) {
        src.get(bufdata);
        dst.data[i] = (unsigned char) bufdata;
    }

    return src;
}


#endif // RAWHEAD_HPP
