#ifndef BASEHEAD_H
#define BASEHEAD_H

#include <fstream>
#include <iostream>

const unsigned RAW_HEADER_SIZE = 4;
const unsigned BITS_PER_SAMPLE = 144;

class BaseHeader {
public:
    virtual bool is_correct() const = 0;
    virtual bool crc_present() const = 0;
    virtual bool padding_present() const = 0;
};

#endif // BASEHEAD_H
