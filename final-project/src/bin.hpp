#ifndef _BIN_HPP_
#define _BIN_HPP_

#include "utils.hpp"

using namespace std;

namespace Bin {
    template <typename T>
    int getSize(T data) {
        return sizeof(data);
    }
    template <typename T>
    int getSize(list<T> data) {
        int ret = 0;
        for (auto it = data.begin(); it != data.end(); ++it) {
            ret += getSize(*it);
        }
        return ret;
    }
    template <typename T>
    int getSize(set<T> data) {
        int ret = 0;
        for (auto it = data.begin(); it != data.end(); ++it) {
            ret += getSize(*it);
        }
        return ret;
    }
    template <typename T>
    int getSize(vector<T> data) {
        int ret = 0;
        for (auto it = data.begin(); it != data.end(); ++it) {
            ret += getSize(*it);
        }
        return ret;
    }
    template <typename T1, typename T2>
    int getSize(map<T1, T2> data) {
        int ret = 0;
        for (auto it = data.begin(); it != data.end(); ++it) {
            ret += getSize(it->first);
            ret += getSize(it->second);
        }
        return ret;
    }
    template <typename T1, typename T2>
    int getSize(pair<T1, T2> data) {
        int ret = 0;
        ret += getSize(data.first);
        ret += getSize(data.second);
        return ret;
    }

    template <typename T>
    shared_ptr<char *> serializeToChar(T serialize_data) {
        shared_ptr<char *> ret = make_shared<char *>(new char[getSize(serialize_data)]);
        memcpy(ret, &serialize_data, getSize(serialize_data));
        return ret;
    }
    template <typename T>
    shared_ptr<char *> serializeToChar(list<T> serialize_data) {
        shared_ptr<char *> ret = make_shared<char *>(new char[getSize(serialize_data)]);
        int record = 0;
        for (auto it = serialize_data.begin(); it != serialize_data.end(); ++it) {
            shared_ptr<char *> tmp = serializeToChar(*it);
            memcpy(ret + record * getSize(*it), tmp.get(), getSize(*it));
            record++;
        }
        return ret;
    }
    template <typename T>
    shared_ptr<char *> serializeToChar(set<T> serialize_data) {
        shared_ptr<char *> ret = make_shared<char *>(new char[getSize(serialize_data)]);
        int record = 0;
        for (auto it = serialize_data.begin(); it != serialize_data.end(); ++it) {
            shared_ptr<char *> tmp = serializeToChar(*it);
            memcpy(ret + record * getSize(*it), tmp.get(), getSize(*it));
            record++;
        }
        return ret;
    }
    template <typename T>
    shared_ptr<char *> serializeToChar(vector<T> serialize_data) {
        shared_ptr<char *> ret = make_shared<char *>(new char[getSize(serialize_data)]);
        int record = 0;
        for (auto it = serialize_data.begin(); it != serialize_data.end(); ++it) {
            shared_ptr<char *> tmp = serializeToChar(*it);
            memcpy(ret + record * getSize(*it), tmp.get(), getSize(*it));
            record++;
        }
        return ret;
    }
    template <typename T1, typename T2>
    shared_ptr<char *> serializeToChar(map<T1, T2> serialize_data) {
        shared_ptr<char *> ret = make_shared<char *>(new char[getSize(serialize_data)]);
        int record = 0;
        cout << "size: " << getSize(serialize_data) << endl;
        for (auto it = serialize_data.begin(); it != serialize_data.end(); ++it) {
            cout << "first: " << it->first << " second: " << it->second << endl;
            cout << "size: " << getSize(it->first) << " " << getSize(it->second) << endl;
            shared_ptr<char *> tmp1 = serializeToChar(it->first);
            shared_ptr<char *> tmp2 = serializeToChar(it->second);
            memcpy(ret + record * (getSize(it->first) + getSize(it->second)), tmp1.get(), getSize(it->first));
            cout << ret << endl;
            memcpy(ret + record * (getSize(it->first) + getSize(it->second)) + getSize(it->first), tmp2.get(), getSize(it->second));
            cout << ret << endl;
            record++;
        }
        return ret;
    }
    template <typename T1, typename T2>
    shared_ptr<char *> serializeToChar(pair<T1, T2> serialize_data) {
        shared_ptr<char *> ret = make_shared<char *>(new char[getSize(serialize_data)]);
        shared_ptr<char *> tmp1 = serializeToChar(serialize_data.first);
        shared_ptr<char *> tmp2 = serializeToChar(serialize_data.second);
        memcpy(ret, tmp1.get(), getSize(serialize_data.first));
        memcpy(ret + getSize(serialize_data.first), tmp2.get(), getSize(serialize_data.second));
        return ret;
    }
    


    template <typename T>
    void deserializeFromChar(T& deserialize_data, shared_ptr<char *> data) {
        memcpy(&deserialize_data, data.get(), sizeof(strlen(data.get())));
    }
    template <typename T>
    void deserializeFromChar(list<T>& deserialize_data, shared_ptr<char *> data) {
        int len = strlen(data.get()) / sizeof(T);
        for (int i = 0; i < len; ++i) {
            T tmp;
            memcpy(&tmp, data.get() + i * sizeof(T), sizeof(T));
            deserialize_data.push_back(tmp);
        }
    }
    template <typename T>
    void deserializeFromChar(set<T>& deserialize_data, shared_ptr<char *> data) {
        int len = strlen(data.get()) / sizeof(T);
        for (int i = 0; i < len; ++i) {
            T tmp;
            memcpy(&tmp, data.get() + i * sizeof(T), sizeof(T));
            deserialize_data.insert(tmp);
        }
    }
    template <typename T>
    void deserializeFromChar(vector<T>& deserialize_data, shared_ptr<char *> data) {
        int len = strlen(data.get()) / sizeof(T);
        for (int i = 0; i < len; ++i) {
            T tmp;
            memcpy(&tmp, data.get() + i * sizeof(T), sizeof(T));
            deserialize_data.push_back(tmp);
        }
    }
    template <typename T1, typename T2>
    void deserializeFromChar(map<T1, T2>& deserialize_data, shared_ptr<char *> data) {
        int len = strlen(data.get()) / (sizeof(T1) + sizeof(T2));
        for (int i = 0; i < len; ++i) {
            T1 tmp1;
            T2 tmp2;
            memcpy(&tmp1, data.get() + i * (sizeof(T1) + sizeof(T2)), sizeof(T1));
            memcpy(&tmp2, data.get() + i * (sizeof(T1) + sizeof(T2)) + sizeof(T1), sizeof(T2));
            deserialize_data[tmp1] = tmp2;
        }
    }
    template <typename T1, typename T2>
    void deserializeFromChar(pair<T1, T2>& deserialize_data, shared_ptr<char *> data) {
        T1 tmp1;
        T2 tmp2;
        memcpy(&tmp1, data.get(), sizeof(T1));
        memcpy(&tmp2, data.get() + sizeof(T1), sizeof(T2));
        deserialize_data = make_pair(tmp1, tmp2);
    }




    template <typename T>
    bool SerializeBin(T serialize_data, const string& filename) {
        shared_ptr<char *> origin = serializeToChar(serialize_data);
        // cout << origin.get() << endl;
        shared_ptr<char *> encoded = utils::base64::encode(origin.get());
        ofstream ofs(filename, ios::binary);
        if (!ofs) {
            return false;
        }
        ofs.write(encoded.get(), strlen(encoded.get()));
        ofs.close();
        return true;
    }

    template <typename T>
    bool DeserializeBin(T& deserialize_data, const string& filename) {
        ifstream ifs(filename, ios::binary);
        if (!ifs) {
            return false;
        }
        ifs.seekg(0, ios::end);
        int len = ifs.tellg();
        ifs.seekg(0, ios::beg);
        shared_ptr<char *> encoded(new char[len + 1]);
        ifs.read(encoded.get(), len);
        encoded.get()[len] = '\0';
        shared_ptr<char *> decoded = utils::base64::decode(encoded.get());
        deserializeFromChar(deserialize_data, decoded);
        ifs.close();
        return true;
    }
};

#endif