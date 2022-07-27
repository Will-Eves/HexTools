#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

namespace HexTools {
    char const hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    struct HexByte {
        unsigned char a = '0';
        unsigned char b = '0';

        HexByte(const unsigned char& data) {
            a = hex_chars[(data & 0xF0) >> 4];
            b = hex_chars[(data & 0x0F) >> 0];
        }

        HexByte(const unsigned int& data) {
            a = hex_chars[(data & 0xF0) >> 4];
            b = hex_chars[(data & 0x0F) >> 0];
        }

        HexByte(const char& data) {
            a = hex_chars[((unsigned char)data & 0xF0) >> 4];
            b = hex_chars[((unsigned char)data & 0x0F) >> 0];
        }

        HexByte(const int& data) {
            a = hex_chars[((unsigned int)data & 0xF0) >> 4];
            b = hex_chars[((unsigned int)data & 0x0F) >> 0];
        }

        HexByte(const char* data) {
            std::string newData = data;
            std::transform(newData.begin(), newData.end(), newData.begin(), toupper);
            a = newData[0];
            b = newData[1];
        }

        HexByte(const HexByte& data) {
            a = data.a;
            b = data.b;
        }

        unsigned char ToUnsignedChar() {
            unsigned char c;
            std::stringstream stream;
            stream << std::hex << a << b;
            stream >> c;
            return c;
        }

        unsigned int ToUnsignedInt() {
            unsigned int c;
            std::stringstream stream;
            stream << std::hex << a << b;
            stream >> c;
            return c;
        }

        char ToChar() {
            char c;
            std::stringstream stream;
            stream << std::hex << a << b;
            stream >> c;
            return c;
        }

        int ToInt() {
            int c;
            std::stringstream stream;
            stream << std::hex << a << b;
            stream >> c;
            return c;
        }
    };

    std::ostream& operator<<(std::ostream& os, const HexByte& data)
    {
        os << data.a << data.b;
        return os;
    }

    struct HexData {
        std::vector<HexByte> data;

        HexData(std::string filename) {
            std::ifstream input(filename, std::ios::binary);
            std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

            for (unsigned char c : buffer) {
                data.push_back(c);
            }
        }

        HexData(std::vector<unsigned char> buffer) {
            for (unsigned char c : buffer) {
                data.push_back(c);
            }
        }

        HexData(const HexData& hexData) {
            data = hexData.data;
        }

        std::string Format(int horizontalSpacing = 0, int verticalSpacing = 0, int breakEvery = -1, int byteCount = -1) {
            std::stringstream stream;
            int index = 0;
            int charNum = 0;
            for (HexByte byte : data) {
                stream << byte;
                for (int i = 0; i < horizontalSpacing; i++) {
                    stream << " ";
                }
                index++;
                if (index == breakEvery) {
                    stream << "\n";
                    for (int i = 0; i < verticalSpacing; i++) {
                        stream << "\n";
                    }
                    index = 0;
                }
                charNum++;
                if (charNum == byteCount) {
                    break;
                }
            }
            return stream.str();
        }

        void Save(std::string filename) {
            std::ofstream output(filename, std::ios::binary);
            std::string buffer;

            for (HexByte byte : data) {
                buffer += byte.ToUnsignedChar();
            }

            output.write((const char*)buffer.c_str(), data.size() * sizeof(unsigned char));
        }

        HexByte GetByteAt(long long position) {
            return data[position];
        }

        void SetByteAt(HexByte byte, long long position) {
            data[position] = byte;
        }

        HexByte& operator[](int i) {
            if (i > data.size()) {
                return data[0];
            }

            return data[i];
        }
    };
}
