#ifndef _BIN_HPP_
#define _BIN_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <map>

static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

using namespace std;

namespace Bin {
    // encode data with base64
    shared_ptr<char> encode(char *data) {
        int i = 0, j = 0;
        unsigned char origin[3], encoded[4];
        int len = strlen(data);
        shared_ptr<char> ret(new char[len * 4 / 3 + 1]);
        while (len--) {
            origin[i++] = *(data++);
            if (i == 3) {
                encoded[0] = (origin[0] & 0xfc) >> 2;
                encoded[1] = ((origin[0] & 0x03) << 4) + ((origin[1] & 0xf0) >> 4);
                encoded[2] = ((origin[1] & 0x0f) << 2) + ((origin[2] & 0xc0) >> 6);
                encoded[3] = origin[2] & 0x3f;
                for (i = 0; i < 4; i++) {
                    ret.get()[j++] = base64_chars[encoded[i]];
                }
                i = 0;
            }
        }
        if (i) {
            for (int k = i; k < 3; k++) {
                origin[k] = '\0';
            }
            encoded[0] = (origin[0] & 0xfc) >> 2;
            encoded[1] = ((origin[0] & 0x03) << 4) + ((origin[1] & 0xf0) >> 4);
            encoded[2] = ((origin[1] & 0x0f) << 2) + ((origin[2] & 0xc0) >> 6);
            encoded[3] = origin[2] & 0x3f;
            for (int k = 0; k < i + 1; k++) {
                ret.get()[j++] = base64_chars[encoded[k]];
            }
            while (i++ < 3) {
                ret.get()[j++] = '=';
            }
        }
        ret.get()[j] = '\0';
        return ret;
    }

    // decode data with base64
    shared_ptr<char> decode(char *data) {
        int i = 0, j = 0;
        unsigned char origin[4], decoded[3];
        int len = strlen(data);
        shared_ptr<char> ret(new char[len * 3 / 4 + 1]);
        while (len--) {
            if (*data != '=') {
                origin[i++] = *(data++);
            } else {
                origin[i++] = '\0';
                data++;
            }
            if (i == 4) {
                for (i = 0; i < 4; i++) {
                    origin[i] = base64_chars.find(origin[i]);
                }
                decoded[0] = (origin[0] << 2) + ((origin[1] & 0x30) >> 4);
                decoded[1] = ((origin[1] & 0xf) << 4) + ((origin[2] & 0x3c) >> 2);
                decoded[2] = ((origin[2] & 0x3) << 6) + origin[3];
                for (i = 0; i < 3; i++) {
                    ret.get()[j++] = decoded[i];
                }
                i = 0;
            }
        }
        if (i) {
            for (int k = i; k < 4; k++) {
                origin[k] = '\0';
            }
            for (int k = 0; k < 4; k++) {
                origin[k] = base64_chars.find(origin[k]);
            }
            decoded[0] = (origin[0] << 2) + ((origin[1] & 0x30) >> 4);
            decoded[1] = ((origin[1] & 0xf) << 4) + ((origin[2] & 0x3c) >> 2);
            decoded[2] = ((origin[2] & 0x3) << 6) + origin[3];
            for (int k = 0; k < i - 1; k++) {
                ret.get()[j++] = decoded[k];
            }
        }
        ret.get()[j] = '\0';
        return ret;
    }

    template <class T>
    shared_ptr<char> serializeToChar(T serialize_data) {
        shared_ptr<char> ret(new char[sizeof(serialize_data)]);
        if (is_member_function_pointer<decltype(serialize_data.begin())>::value) {
            for (auto it = serialize_data.begin(); it != serialize_data.end(); it++) {
                shared_ptr<char> temp = serializeToChar(*it);
                memcpy(ret.get() + strlen(ret.get()), temp.get(), strlen(temp.get()));
            }
        } else if (is_member_function_pointer<decltype(serialize_data.first())>::value) {
            shared_ptr<char> temp = serializeToChar(serialize_data.first());
            memcpy(ret.get() + strlen(ret.get()), temp.get(), strlen(temp.get()));
            temp = serializeToChar(serialize_data.second());
            memcpy(ret.get() + strlen(ret.get()), temp.get(), strlen(temp.get()));
        } else {
            memcpy(ret.get(), reinterpret_cast<char *>(&serialize_data), sizeof(serialize_data));
        }
        return ret;
    }
    
    template <class T>
    void deserializeFromChar(T& deserialize_data, shared_ptr<char> data) {
        memcpy(&deserialize_data, data.get(), sizeof(strlen(data.get())));
    }

    template <class T>
    bool SerializeBin(T serialize_data, const string& filename) {
        shared_ptr<char> origin = serializeToChar(serialize_data);
        cout << origin.get() << endl;
        shared_ptr<char> encoded = encode(origin.get());
        ofstream ofs(filename, ios::binary);
        if (!ofs) {
            return false;
        }
        ofs.write(encoded.get(), strlen(encoded.get()));
        ofs.close();
        return true;
    }

    template <class T>
    bool DeserializeBin(T& deserialize_data, const string& filename) {
        ifstream ifs(filename, ios::binary);
        if (!ifs) {
            return false;
        }
        ifs.seekg(0, ios::end);
        int len = ifs.tellg();
        ifs.seekg(0, ios::beg);
        shared_ptr<char> encoded(new char[len + 1]);
        ifs.read(encoded.get(), len);
        encoded.get()[len] = '\0';
        shared_ptr<char> decoded = decode(encoded.get());
        deserializeFromChar(deserialize_data, decoded);
        ifs.close();
        return true;
    }
};

#endif