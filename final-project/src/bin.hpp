#ifndef _BIN_HPP_
#define _BIN_HPP_

#include "utils.hpp"

using namespace std;

// macro for define serialize
#define BEGIN_REGISTER_STRUCT_SERIALIZE_BIN(className)              bool SerializeBin(className data, const string filename) {\
                                                                        ofstream outputFile(filename, ios::binary);\
                                                                        if (outputFile) {\
                                                                            bool ok = true;
#define REGISTER_STRUCT_MEMBER_SERIALIZE_BIN(memberName)                    ok = bin::writeSerialize(data.memberName, outputFile);\
                                                                            if (!ok) {\
                                                                                return false;\
                                                                            }
#define END_REGISTER_STRUCT_SERIALIZE_BIN()                                 outputFile.close();\
                                                                            return ok;\
                                                                        } else {\
                                                                            cerr << "无法打开文件：" << filename << endl;\
                                                                            return false;\
                                                                        }\
                                                                    }

// macro for define deserialize
#define BEGIN_REGISTER_STRUCT_DESERIALIZE_BIN(className)            bool DeserializeBin(className& data, const string filename) {\
                                                                        ifstream inputFile(filename, ios::binary);\
                                                                        data = className();\
                                                                        if (inputFile) {\
                                                                            bool ok = true;
#define REGISTER_STRUCT_MEMBER_DESERIALIZE_BIN(memberName)                  ok = bin::readSerialize(data.memberName, inputFile);\
                                                                            if (!ok) {\
                                                                                return false;\
                                                                            }
#define END_REGISTER_STRUCT_DESERIALIZE_BIN()                               return ok;\
                                                                        } else {\
                                                                            cerr << "无法打开文件：" << filename << endl;\
                                                                            return false;\
                                                                        }\
                                                                    }

/// @brief namespace for bin serialize and deserialize
namespace bin {
    /// @brief writeSerialize for basic type
    /// @tparam T the type of data
    /// @param data the data to be serialized
    /// @param outputFile the stream to write
    /// @return true if success, false if fail
    template <typename T>
    bool writeSerialize(const T data, ofstream& outputFile);
    /// @brief writeSerialize for string
    /// @param data the string to be serialized
    /// @param outputFile the stream to write
    /// @return true if success, false if fail
    bool writeSerialize(const string data, ofstream& outputFile);
    /// @brief writeSerialize for list
    /// @tparam T the type of list item
    /// @param data the list to be serialized
    /// @param outputFile the stream to write
    /// @return true if success, false if fail
    template <typename T>
    bool writeSerialize(list<T> data, ofstream& outputFile);
    /// @brief writeSerialize for set
    /// @tparam T the type of set item
    /// @param data the set to be serialized
    /// @param outputFile the stream to write
    /// @return true if success, false if fail
    template <typename T>
    bool writeSerialize(set<T> data, ofstream& outputFile);
    /// @brief writeSerialize for vector
    /// @tparam T the type of vector item
    /// @param data the vector to be serialized
    /// @param outputFile the stream to write
    /// @return true if success, false if fail
    template <typename T>
    bool writeSerialize(vector<T> data, ofstream& outputFile);
    /// @brief writeSerialize for map
    /// @tparam T1 the type of map key
    /// @tparam T2 the type of map value
    /// @param data the map to be serialized
    /// @param outputFile the stream to write
    /// @return true if success, false if fail
    template <typename T1, typename T2>
    bool writeSerialize(map<T1, T2> data, ofstream& outputFile);
    /// @brief writeSerialize for pair
    /// @tparam T1 the type of pair first
    /// @tparam T2 the type of pair second
    /// @param data the pair to be serialized
    /// @param outputFile the stream to write
    /// @return true if success, false if fail
    template <typename T1, typename T2>
    bool writeSerialize(pair<T1, T2> data, ofstream& outputFile);

    /// @brief readSerialize for basic type
    /// @tparam T the type of data
    /// @param data the data to be deserialized
    /// @param inputFile the stream to read
    /// @return true if success, false if fail
    template <typename T>
    bool readSerialize(T& data, ifstream& inputFile);
    /// @brief readSerialize for string
    /// @param data the string to be deserialized
    /// @param inputFile the stream to read
    /// @return true if success, false if fail
    bool readSerialize(string& data, ifstream& inputFile);
    /// @brief readSerialize for list
    /// @tparam T the type of list item
    /// @param data the list to be deserialized
    /// @param inputFile the stream to read
    /// @return true if success, false if fail
    template <typename T>
    bool readSerialize(list<T>& data, ifstream& inputFile);
    /// @brief readSerialize for set
    /// @tparam T the type of set item
    /// @param data the set to be deserialized
    /// @param inputFile the stream to read
    /// @return true if success, false if fail
    template <typename T>
    bool readSerialize(set<T>& data, ifstream& inputFile);
    /// @brief readSerialize for vector
    /// @tparam T the type of vector item
    /// @param data the vector to be deserialized
    /// @param inputFile the stream to read
    /// @return true if success, false if fail
    template <typename T>
    bool readSerialize(vector<T>& data, ifstream& inputFile);
    /// @brief readSerialize for map
    /// @tparam T1 the type of map key
    /// @tparam T2 the type of map value
    /// @param data the map to be deserialized
    /// @param inputFile the stream to read
    /// @return true if success, false if fail
    template <typename T1, typename T2>
    bool readSerialize(map<T1, T2>& data, ifstream& inputFile);
    /// @brief readSerialize for pair
    /// @tparam T1 the type of pair first
    /// @tparam T2 the type of pair second
    /// @param data the pair to be deserialized
    /// @param inputFile the stream to read
    /// @return true if success, false if fail
    template <typename T1, typename T2>
    bool readSerialize(pair<T1, T2>& data, ifstream& inputFile);

    /// @brief Serialize
    /// @tparam T the type of data
    /// @param data the data to be serialized
    /// @param filename the file to write
    /// @return true if success, false if fail
    template <typename T>
    bool Serialize(const T data, const string filename);
    /// @brief Serialize
    /// @tparam T the type of data
    /// @param data unique_ptr of type T to be serialized
    /// @param filename the file to write
    /// @return true if success, false if fail
    template <typename T>
    bool Serialize(const unique_ptr<T>& data, const string filename);
    /// @brief Serialize
    /// @tparam T the type of data
    /// @param data shared_ptr of type T to be serialized
    /// @param filename the file to write
    /// @return true if success, false if fail
    template <typename T>
    bool Serialize(const shared_ptr<T>& data, const string filename);
    /// @brief Serialize
    /// @tparam T the type of data
    /// @param data weak_ptr of type T to be serialized
    /// @param filename the file to write
    /// @return true if success, false if fail
    template <typename T>
    bool Serialize(const weak_ptr<T>& data, const string filename);
    /// @brief Deserialize
    /// @tparam T the type of data
    /// @param data the data to be deserialized
    /// @param filename the file to read
    /// @return true if success, false if fail
    template <typename T>
    bool Deserialize(T& data, const string filename);
    /// @brief Deserialize
    /// @tparam T the type of data
    /// @param data unique_ptr of type T to be deserialized
    /// @param filename the file to read
    /// @return true if success, false if fail
    template <typename T>
    bool Deserialize(unique_ptr<T>& data, const string filename);
    /// @brief Deserialize
    /// @tparam T the type of data
    /// @param data shared_ptr of type T to be deserialized
    /// @param filename the file to read
    /// @return true if success, false if fail
    template <typename T>
    bool Deserialize(shared_ptr<T>& data, const string filename);
    /// @brief Deserialize
    /// @tparam T the type of data
    /// @param data weak_ptr of type T to be deserialized
    /// @param filename the file to read
    /// @return true if success, false if fail
    template <typename T>
    bool Deserialize(weak_ptr<T>& data, const string filename);

    template <typename T>
    bool writeSerialize(const T data, ofstream& outputFile) {
        // cout << "data size: " << utils::size::getSize(data) << endl;
        if (outputFile) {
            int size = utils::size::getSize(data); // get size of data
            outputFile.write(reinterpret_cast<const char*>(&data), size);
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    bool writeSerialize(const string data, ofstream& outputFile) {
        // cout << "string size: " << utils::size::getSize(data) << endl;
        if (outputFile) {
            int size = utils::size::getSize(data);
            outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size)); // write size of string
            // serialize each char
            for (int i = 0; i < size; ++i) {
                outputFile.write(reinterpret_cast<const char*>(&data[i]), sizeof(data[i]));
            }
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    template <typename T>
    bool writeSerialize(list<T> data, ofstream& outputFile) {
        // cout << "list size: " << data.size() << endl;
        if (outputFile) {
            int size = data.size();
            outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            for (auto &it : data) {
                writeSerialize(it, outputFile);
            }
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    template <typename T>
    bool writeSerialize(set<T> data, ofstream& outputFile) {
        // cout << "set size: " << data.size() << endl;
        if (outputFile) {
            int size = data.size();
            outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            for (auto &it : data) {
                writeSerialize(it, outputFile);
            }
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    template <typename T>
    bool writeSerialize(vector<T> data, ofstream& outputFile) {
        // cout << "vector size: " << data.size() << endl;
        if (outputFile) {
            int size = data.size();
            outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            for (auto &it : data) {
                writeSerialize(it, outputFile);
            }
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    template <typename T1, typename T2>
    bool writeSerialize(map<T1, T2> data, ofstream& outputFile) {
        // cout << "map size: " << data.size() << endl;
        if (outputFile) {
            int size = data.size();
            outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            for (auto &it : data) {
                writeSerialize(it.first, outputFile);
                writeSerialize(it.second, outputFile);
            }
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    template <typename T1, typename T2>
    bool writeSerialize(pair<T1, T2> data, ofstream& outputFile) {
        // cout << "pair size: " << utils::size::getSize(data) << endl;
        if (outputFile) {
            writeSerialize(data.first, outputFile);
            writeSerialize(data.second, outputFile);
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }


    template <typename T>
    bool readSerialize(T& data, ifstream& inputFile) {
        if (inputFile) {
            int size = utils::size::getSize(data);
            // cout << "data size: " << size << endl;
            inputFile.read(reinterpret_cast<char*>(&data), size);
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    bool readSerialize(string& data, ifstream& inputFile) {
        if (inputFile) {
            int size;
            inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
            // cout << "string size: " << size << endl;
            for (int i = 0; i < size; ++i) {
                char tmp;
                inputFile.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
                data += tmp;
            }
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    template <typename T>
    bool readSerialize(list<T>& data, ifstream& inputFile) {
        if (inputFile) {
            int size;
            inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
            // cout << "list size: " << size << endl;
            for (int i = 0; i < size; ++i) {
                T tmp;
                readSerialize(tmp, inputFile);
                data.push_back(tmp);
            }
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    template <typename T>
    bool readSerialize(set<T>& data, ifstream& inputFile) {
        if (inputFile) {
            int size;
            inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
            // cout << "set size: " << size << endl;
            for (int i = 0; i < size; ++i) {
                T tmp;
                readSerialize(tmp, inputFile);
                data.insert(tmp);
            }
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    template <typename T>
    bool readSerialize(vector<T>& data, ifstream& inputFile) {
        if (inputFile) {
            int size;
            inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
            // cout << "vector size: " << size << endl;
            for (int i = 0; i < size; ++i) {
                T tmp;
                readSerialize(tmp, inputFile);
                data.push_back(tmp);
            }
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    template <typename T1, typename T2>
    bool readSerialize(map<T1, T2>& data, ifstream& inputFile) {
        if (inputFile) {
            int size;
            inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
            // cout << "map size: " << size << endl;
            for (int i = 0; i < size; ++i) {
                T1 tmp1;
                T2 tmp2;
                readSerialize(tmp1, inputFile);
                readSerialize(tmp2, inputFile);
                data.insert(make_pair(tmp1, tmp2));
            }
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    static int cnt = 0;
    template <typename T1, typename T2>
    bool readSerialize(pair<T1, T2>& data, ifstream& inputFile) {
        cnt++;
        if (inputFile) {
            bool flag = false;
            // cout << "pair size: " << utils::size::getSize(data) << endl;
            readSerialize(data.first, inputFile);
            // cout <<"cnt1: " << cnt << endl;
            readSerialize(data.second, inputFile);
            if (!flag) {
                flag = true;
                // cout <<"cnt2: " << cnt << endl;
            }
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }

    template <typename T>
    bool Serialize(const T data, const string filename) {
        ofstream outputFile(filename, ios::binary);
        if (outputFile) {
            bool ok = writeSerialize(data, outputFile); // recursive call
            outputFile.close();
            return ok;
        } else {
            cerr << "Cannot open file: " << filename << endl;
            return false;
        }
    }
    template <typename T>
    bool Serialize(const unique_ptr<T>& data, const string filename) {
        bool ok = Serialize(*data, filename);
        return ok;
    }
    template <typename T>
    bool Serialize(const shared_ptr<T>& data, const string filename) {
        bool ok = Serialize(*data, filename);
        return ok;
    }
    template <typename T>
    bool Serialize(const weak_ptr<T>& data, const string filename) {
        shared_ptr<T> tmp = data.lock();
        return Serialize(tmp, filename);
    }

    template <typename T>
    bool Deserialize(T& data, const string filename) {
        ifstream inputFile(filename, ios::binary);
        data = T();
        if (inputFile) {
            bool ok = readSerialize(data, inputFile);
            inputFile.close();
            return ok;
        } else {
            cerr << "Cannot open file: " << filename << endl;
            return false;
        }
    }
    template <typename T>
    bool Deserialize(unique_ptr<T>& data, const string filename) {
        data = make_unique<T>();
        bool ok = Deserialize(*data, filename);
        return ok;
    }
    template <typename T>
    bool Deserialize(shared_ptr<T>& data, const string filename) {
        data = make_shared<T>();
        bool ok = Deserialize(*data, filename);
        return ok;
    }
    template <typename T>
    bool Deserialize(weak_ptr<T>& data, const string filename) {
        shared_ptr<T> tmp = data.lock();
        bool ok = Deserialize(tmp, filename);
        return ok;
    }
};

#endif