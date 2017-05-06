#ifndef HEAD_H
#define HEAD_H

#include "base_head.h"
#include "raw_head.h"

class Header : public BaseHeader{
public:

    Header() = default;
    Header(const RawHeader&);

    unsigned frame_size() const;
    bool is_correct() const;
    bool crc_present() const;
    bool padding_present() const;

    friend std::istream& operator >>(std::istream&, Header&);

private:
    bool correct = false;
    bool crc = false;
    unsigned bitrate = 0;
    unsigned samplerate = 0;
    bool padding = false;
};

#endif // HEAD_H
