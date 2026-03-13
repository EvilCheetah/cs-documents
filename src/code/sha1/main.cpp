/**
 * @file      main.cpp
 * @author    Eugene Moshchyn
 * @studentID 113-683-484
 * @course    CS 5173 - Computer Security
 * @date      Mar 13th, 2026
 * @brief     Main Function that utilizes SHA1
**/


#include "sha1.h"


int main() {
    std::vector<std::string> messages = {
        "OU",
        "Computer Science",
        "Crypto"
    };

    for (auto message : messages)
    {
        std::cout << "Message:    " << message       << std::endl;
        std::cout << "SHA-1 Hash: " << sha1(message) << std::endl;
        std::cout << std::endl;
    }

    return 0;
}