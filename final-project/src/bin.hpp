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
    bool writeSerialize(const T data, ofstream& outputFile) {
        cout << "data size: " << getSize(data) << endl;
        if (outputFile) {
            int size = getSize(data);
            outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            outputFile.write(reinterpret_cast<const char*>(&data), size);
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T>
    bool writeSerialize(list<T> data, ofstream& outputFile) {
        cout << "list size: " << data.size() << endl;
        if (outputFile) {
            int size = data.size();
            outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            for (auto &it : data) {
                writeSerialize(it, outputFile);
            }
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T>
    bool writeSerialize(set<T> data, ofstream& outputFile) {
        cout << "set size: " << data.size() << endl;
        if (outputFile) {
            int size = data.size();
            outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            for (auto &it : data) {
                writeSerialize(it, outputFile);
            }
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T>
    bool writeSerialize(vector<T> data, ofstream& outputFile) {
        cout << "vector size: " << data.size() << endl;
        if (outputFile) {
            int size = data.size();
            outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            for (auto &it : data) {
                writeSerialize(it, outputFile);
            }
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T1, typename T2>
    bool writeSerialize(map<T1, T2> data, ofstream& outputFile) {
        cout << "map size: " << data.size() << endl;
        if (outputFile) {
            int size = data.size();
            outputFile.write(reinterpret_cast<const char*>(&size), sizeof(size));
            for (auto &it : data) {
                writeSerialize(it.first, outputFile);
                writeSerialize(it.second, outputFile);
            }
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T1, typename T2>
    bool writeSerialize(pair<T1, T2> data, ofstream& outputFile) {
        cout << "pair size: " << getSize(data) << endl;
        if (outputFile) {
            writeSerialize(data.first, outputFile);
            writeSerialize(data.second, outputFile);
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }

    template <typename T>
    bool readSerialize(T& data, ifstream& inputFile) {
        if (inputFile) {
            int size;
            inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
            inputFile.read(reinterpret_cast<char*>(&data), size);
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T>
    bool readSerialize(list<T>& data, ifstream& inputFile) {
        if (inputFile) {
            int size;
            inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
            cout << "list size: " << size << endl;
            for (int i = 0; i < size; ++i) {
                T tmp;
                readSerialize(tmp, inputFile);
                data.push_back(tmp);
            }
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T>
    bool readSerialize(set<T>& data, ifstream& inputFile) {
        if (inputFile) {
            int size;
            inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
            cout << "set size: " << size << endl;
            for (int i = 0; i < size; ++i) {
                T tmp;
                readSerialize(tmp, inputFile);
                data.insert(tmp);
            }
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T>
    bool readSerialize(vector<T>& data, ifstream& inputFile) {
        if (inputFile) {
            int size;
            inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
            cout << "vector size: " << size << endl;
            for (int i = 0; i < size; ++i) {
                T tmp;
                readSerialize(tmp, inputFile);
                data.push_back(tmp);
            }
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T1, typename T2>
    bool readSerialize(map<T1, T2>& data, ifstream& inputFile) {
        if (inputFile) {
            int size;
            inputFile.read(reinterpret_cast<char*>(&size), sizeof(size));
            cout << "map size: " << size << endl;
            for (int i = 0; i < size; ++i) {
                T1 tmp1;
                T2 tmp2;
                readSerialize(tmp1, inputFile);
                readSerialize(tmp2, inputFile);
                data.insert(make_pair(tmp1, tmp2));
            }
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T1, typename T2>
    bool readSerialize(pair<T1, T2>& data, ifstream& inputFile) {
        if (inputFile) {
            cout << "pair size: " << getSize(data) << endl;
            readSerialize(data.first, inputFile);
            readSerialize(data.second, inputFile);
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }

    template <typename T>
    bool Serialize(const T data, const string filename) {
        ofstream outputFile(filename, ios::binary);
        if (outputFile) {
            bool ok = writeSerialize(data, outputFile);
            return ok;
        } else {
            cerr << "无法打开文件：" << filename << endl;
            return false;
        }
    }

    template <typename T>
    bool Deserialize(T& data, const string filename) {
        ifstream inputFile(filename, ios::binary);
        if (inputFile) {
            bool ok = readSerialize(data, inputFile);
            return ok;
        } else {
            cerr << "无法打开文件：" << filename << endl;
            return false;
        }
    }
};

#endif