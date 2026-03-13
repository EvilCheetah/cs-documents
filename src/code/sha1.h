/**
 * @file      sha1.h
 * @author    Eugene Moshchyn
 * @studentID 113-683-484
 * @course    CS 5173 - Computer Security
 * @date      Mar 13th, 2026
 * @brief     SHA1 Algorithm Implementation
**/

#pragma once


#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip>
#include <sstream>

/*
 * Helper function 
 * Source: https://en.wikipedia.org/wiki/Circular_shift#Implementing_circular_shifts
**/
/// Source: 
inline uint32_t leftrotate(uint32_t val, size_t count)
{
    return (val << count) | (val >> (32 - count));
}


/*
 * SHA1 Implementation
 * Source: https://en.wikipedia.org/wiki/SHA-1#SHA-1_pseudocode
**/
std::string sha1(const std::string& message)
{
    // Initialize variables
    uint32_t h0 = 0x67452301,
             h1 = 0xEFCDAB89,
             h2 = 0x98BADCFE,
             h3 = 0x10325476,
             h4 = 0xC3D2E1F0;

    uint64_t message_bitlength = message.length() * 8;


    // Pre-processing
    std::vector<uint8_t> padded_message(message.begin(), message.end());

    padded_message.push_back(0x80);            // append the bit '1' to the message
    while ((padded_message.size() % 64) != 56) // append '0', until message length is 448 bits
    {
        padded_message.push_back(0x00);
    }

    for (int i = 7; i >= 0; --i) // append message_bitlength
    {
        padded_message.push_back(static_cast<uint8_t>((message_bitlength >> (i * 8)) & 0xFF));
    }


    // Process the message in successive 512-bit chunks
    for (size_t offset = 0; offset < padded_message.size(); offset += 64)
    {
        std::vector<uint32_t> w(80, 0);

        // Break chunk into sixteen 32-bit big-endian words
        for (int i = 0; i < 16; ++i)
        {
            w[i] = (padded_message[offset + i * 4] << 24)     |
                   (padded_message[offset + i * 4 + 1] << 16) |
                   (padded_message[offset + i * 4 + 2] << 8)  |
                   (padded_message[offset + i * 4 + 3]);
        }

        // Message schedule: extend the sixteen 32-bit words into eighty 32-bit words
        for (int i = 16; i < 80; ++i)
        {
            w[i] = leftrotate(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        }

        // Initialize hash value for this chunk
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;

        // Main loop
        for (int i = 0; i < 80; ++i)
        {
            uint32_t f = 0,
                     k = 0;

            switch (i / 20)
            {
                case 0: // 0 ... 19
                    f = (b & c) | ((~b) & d);
                    k = 0x5A827999;
                    break;
                case 1: // 20 ... 39
                    f = b ^ c ^ d;
                    k = 0x6ED9EBA1;
                    break;
                case 2: /// 40 ... 59
                    f = (b & c) | (b & d) | (c & d);
                    k = 0x8F1BBCDC;
                    break;
                case 3: /// 60 ... 79
                    f = b ^ c ^ d;
                    k = 0xCA62C1D6;
                    break;
                default:
                    break;
            }

            uint32_t temp = leftrotate(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = leftrotate(b, 30);
            b = a;
            a = temp;
        }

        // Add this chunk's hash to result so far
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    // Produce the final hash value (big-endian) as a 160-bit number
    std::stringstream result;
    result << std::hex << std::setfill('0')
           << std::setw(8) << h0
           << std::setw(8) << h1
           << std::setw(8) << h2
           << std::setw(8) << h3
           << std::setw(8) << h4;

    return result.str();
}
