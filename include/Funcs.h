#ifndef FUNCS_H
#define FUNCS_H

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>

inline bool validation(const std::string& ipAddress) {
    std::vector<std::string> parts;
    std::string part;
    std::istringstream iss(ipAddress);

    while (std::getline(iss, part, '.')) {
        if (part.empty() || part.size() > 3) {
            return false;
        }

        for (char c : part) {
            if (!std::isdigit(c)) {
                return false;
            }
        }

        int num = std::stoi(part);
        if (num < 0 || num > 255) {
            return false;
        }

        parts.push_back(part);
    }

    return parts.size() == 4;
}

template<class T>
inline T getNum(T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) {
    T a;
    while(true) {
        std::cin >> a;
        if(std::cin.eof())
            throw std::runtime_error("Failed to read number: EOF");
        else if(std::cin.bad())
            throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
        else if(std::cin.fail() || a < min || a > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You are wrong; repeat please!" << std::endl;
        }
        else
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return a;
    }
}

inline std::string readLine() {
    std::string line;
    try {
        if (!std::getline(std::cin, line)) {
            if (std::cin.eof()) {
                throw std::runtime_error("End of file reached.");
            } else if (std::cin.fail()) {
                if (std::cin.bad()) {
                    throw std::runtime_error("Critical stream error occurred.");
                } else {
                    throw std::runtime_error("Input error occurred.");
                }
            } else {
                throw std::runtime_error("Unknown error occurred while reading input.");
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        line = "";
    }
    return line;
}

#endif //FUNCS_H
