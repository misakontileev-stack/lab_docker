#include <fstream>
#include <iostream>
#include <string>

inline void print(const std::string& text, std::ofstream& out) {
    out << text;
}

inline void print(const std::string& text, std::ostream& out = std::cout) {
    out << text;
}
