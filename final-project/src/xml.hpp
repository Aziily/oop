#ifndef _XML_HPP_
#define _XML_HPP_

#define DEBUG true

#include "utils.hpp"

using namespace std;

namespace xml {
    static const int TAB_SPACE = 2;

    template <typename T>
    bool writeSerialize(const T data, stringstream& outputFile, int tabCount);
    bool writeSerialize(const string data, stringstream& outputFile, int tabCount);
    template <typename T>
    bool writeSerialize(const vector<T> data, stringstream& outputFile, int tabCount);
    template <typename T>
    bool writeSerialize(const list<T> data, stringstream& outputFile, int tabCount);
    template <typename T>
    bool writeSerialize(const set<T> data, stringstream& outputFile, int tabCount);
    template <typename T1, typename T2>
    bool writeSerialize(const map<T1, T2> data, stringstream& outputFile, int tabCount);
    template <typename T1, typename T2>
    bool writeSerialize(const pair<T1, T2> data, stringstream& outputFile, int tabCount);

    template <typename T>
    bool readSerialize(T& data, stringstream& inputFile);
    bool readSerialize(string& data, stringstream& inputFile);
    template <typename T>
    bool readSerialize(vector<T>& data, stringstream& inputFile);
    template <typename T>
    bool readSerialize(list<T>& data, stringstream& inputFile);
    template <typename T>
    bool readSerialize(set<T>& data, stringstream& inputFile);
    template <typename T1, typename T2>
    bool readSerialize(map<T1, T2>& data, stringstream& inputFile);
    template <typename T1, typename T2>
    bool readSerialize(pair<T1, T2>& data, stringstream& inputFile);

    template <typename T>
    bool writeSerialize(const T data, stringstream& outputFile, int tabCount) {
        if (outputFile) {
            outputFile << string(tabCount * TAB_SPACE, ' ') << "<" << utils::judge::GetType(data) << ">" << fixed << setprecision(20) << data << "</" << utils::judge::GetType(data) << ">" << endl;
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    bool writeSerialize(const string data, stringstream& outputFile, int tabCount) {
        if (outputFile) {
            int size = utils::size::getSize(data);
            outputFile << string(tabCount * TAB_SPACE, ' ') << "<" << utils::judge::GetType(data) << ">"\
                       << data\
                       << "</" << utils::judge::GetType(data) << ">" << endl;
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T>
    bool writeSerialize(const vector<T> data, stringstream& outputFile, int tabCount) {
        if (outputFile) {
            outputFile << string(tabCount * TAB_SPACE, ' ') << "<" << utils::judge::GetType(data) << " size=\"" << data.size() << "\">" << endl;
            for (auto it = data.begin(); it != data.end(); ++it) {
                writeSerialize(*it, outputFile, tabCount + 1);
            }
            outputFile << string(tabCount * TAB_SPACE, ' ') << "</" << utils::judge::GetType(data) << ">" << endl;
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T>
    bool writeSerialize(const list<T> data, stringstream& outputFile, int tabCount) {
        if (outputFile) {
            outputFile << string(tabCount * TAB_SPACE, ' ') << "<" << utils::judge::GetType(data) << " size=\"" << data.size() << "\">" << endl;
            for (auto it = data.begin(); it != data.end(); ++it) {
                writeSerialize(*it, outputFile, tabCount + 1);
            }
            outputFile << string(tabCount * TAB_SPACE, ' ') << "</" << utils::judge::GetType(data) << ">" << endl;
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T>
    bool writeSerialize(const set<T> data, stringstream& outputFile, int tabCount) {
        if (outputFile) {
            outputFile << string(tabCount * TAB_SPACE, ' ') << "<" << utils::judge::GetType(data) << " size=\"" << data.size() << "\">" << endl;
            for (auto it = data.begin(); it != data.end(); ++it) {
                writeSerialize(*it, outputFile, tabCount + 1);
            }
            outputFile << string(tabCount * TAB_SPACE, ' ') << "</" << utils::judge::GetType(data) << ">" << endl;
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T1, typename T2>
    bool writeSerialize(const map<T1, T2> data, stringstream& outputFile, int tabCount) {
        if (outputFile) {
            outputFile << string(tabCount * TAB_SPACE, ' ') << "<" << utils::judge::GetType(data) << " size=\"" << data.size() << "\">" << endl;
            for (auto it = data.begin(); it != data.end(); ++it) {
                writeSerialize(*it, outputFile, tabCount + 1);
            }
            outputFile << string(tabCount * TAB_SPACE, ' ') << "</" << utils::judge::GetType(data) << ">" << endl;
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T1, typename T2>
    bool writeSerialize(const pair<T1, T2> data, stringstream& outputFile, int tabCount) {
        if (outputFile) {
            outputFile << string(tabCount * TAB_SPACE, ' ') << "<" << utils::judge::GetType(data) << ">" << endl;
            outputFile << string((tabCount + 1) * TAB_SPACE, ' ') << "<first>" << endl;
            writeSerialize(data.first, outputFile, tabCount + 2);
            outputFile << string((tabCount + 1) * TAB_SPACE, ' ') << "</first>" << endl;
            outputFile << string((tabCount + 1) * TAB_SPACE, ' ') << "<second>" << endl;
            writeSerialize(data.second, outputFile, tabCount + 2);
            outputFile << string((tabCount + 1) * TAB_SPACE, ' ') << "</second>" << endl;
            outputFile << string(tabCount * TAB_SPACE, ' ') << "</" << utils::judge::GetType(data) << ">" << endl;
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    

    template <typename T>
    bool readSerialize(T& data, stringstream& inputFile) {
        if (inputFile) {
            string line;
            while (getline(inputFile, line)) {
                if (line.find("<" + utils::judge::GetType(data)) != string::npos) {
                    string temp = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
                    data = utils::trans::toType<T>(temp);
                }
                if (line.find("</" + utils::judge::GetType(data)) != string::npos) {
                    return true;
                }
            }
            return false;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    bool readSerialize(string& data, stringstream& inputFile) {
        if (inputFile) {
            string line;
            while (getline(inputFile, line)) {
                if (line.find("<" + utils::judge::GetType(data)) != string::npos) {
                    string temp = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
                    data = temp;
                }
                if (line.find("</" + utils::judge::GetType(data)) != string::npos) {
                    return true;
                }
            }
            return false;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T>
    bool readSerialize(vector<T>& data, stringstream& inputFile) {
        if (inputFile) {
            string line;
            while (getline(inputFile, line))
            {
                if (line.find("<" + utils::judge::GetType(data)) != string::npos) {
                    int size = stoi(line.substr(line.find("size=\"") + 6, line.find("\">") - line.find("size=\"") - 6));
                    for (int i = 0; i < size; ++i) {
                        T temp;
                        readSerialize(temp, inputFile);
                        data.push_back(temp);
                    }
                }
                if (line.find("</" + utils::judge::GetType(data)) != string::npos) {
                    return true;
                }
            }
            return false;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T>
    bool readSerialize(list<T>& data, stringstream& inputFile) {
        if (inputFile) {
            string line;
            while (getline(inputFile, line))
            {
                if (line.find("<" + utils::judge::GetType(data)) != string::npos) {
                    int size = stoi(line.substr(line.find("size=\"") + 6, line.find("\">") - line.find("size=\"") - 6));
                    for (int i = 0; i < size; ++i) {
                        T temp;
                        readSerialize(temp, inputFile);
                        data.push_back(temp);
                    }
                }
                if (line.find("</" + utils::judge::GetType(data)) != string::npos) {
                    return true;
                }
            }
            return false;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T>
    bool readSerialize(set<T>& data, stringstream& inputFile) {
        if (inputFile) {
            string line;
            while (getline(inputFile, line))
            {
                if (line.find("<" + utils::judge::GetType(data)) != string::npos) {
                    int size = stoi(line.substr(line.find("size=\"") + 6, line.find("\">") - line.find("size=\"") - 6));
                    for (int i = 0; i < size; ++i) {
                        T temp;
                        readSerialize(temp, inputFile);
                        data.insert(temp);
                    }
                }
                if (line.find("</" + utils::judge::GetType(data)) != string::npos) {
                    return true;
                }
            }
            return false;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T1, typename T2>
    bool readSerialize(pair<T1, T2>& data, stringstream& inputFile) {
        if (inputFile) {
            string line;
            while (getline(inputFile, line))
            {
                if (line.find("<" + utils::judge::GetType(data)) != string::npos) {
                    while (getline(inputFile, line)) {
                        if (line.find("<first>") != string::npos) {
                            T1 temp;
                            readSerialize(temp, inputFile);
                            data.first = temp;
                        }
                        if (line.find("</first>") != string::npos) {
                            continue;
                        }
                        if (line.find("<second>") != string::npos) {
                            T2 temp;
                            readSerialize(temp, inputFile);
                            data.second = temp;
                        }
                        if (line.find("</second>") != string::npos) {
                            break;
                        }
                    }
                }
                if (line.find("</" + utils::judge::GetType(data)) != string::npos) {
                    return true;
                }
            }
            return false;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
    template <typename T1, typename T2>
    bool readSerialize(map<T1, T2>& data, stringstream& inputFile) {
        if (inputFile) {
            string line;
            while (getline(inputFile, line))
            {
                if (line.find("<" + utils::judge::GetType(data)) != string::npos) {
                    int size = stoi(line.substr(line.find("size=\"") + 6, line.find("\">") - line.find("size=\"") - 6));
                    for (int i = 0; i < size; ++i) {
                        pair<T1, T2> temp;
                        readSerialize(temp, inputFile);
                        data.insert(temp);
                    }
                }
                if (line.find("</" + utils::judge::GetType(data)) != string::npos) {
                    return true;
                }
            }
            return false;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }

    template <typename T>
    bool Serialize(const T data, const string filename) {
        ofstream outputFile(filename);
        stringstream origin, encoded;
        if (outputFile) {
            origin << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
            origin << "<serialization>" << endl;
            bool ok = writeSerialize(data, origin, 1);
            origin << "</serialization>" << endl;
            if (DEBUG) {
                ofstream debugFile(filename + ".debug");
                debugFile << origin.str();
                debugFile.close();
            }
            utils::base64::encode(origin, encoded);
            outputFile << encoded.str();
            outputFile.close();
            return ok;
        } else {
            cerr << "无法打开文件" << endl;
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
        bool ok = Serialize(tmp, filename);
        return ok;
    }

    template <typename T>
    bool Deserialize(T& data, const string filename) {
        ifstream inputFile(filename);
        stringstream origin, decoded;
        data = T();
        if (inputFile) {
            origin << inputFile.rdbuf();
            utils::base64::decode(origin, decoded);
            bool ok = readSerialize(data, decoded);
            inputFile.close();
            return ok;
        } else {
            cerr << "无法打开文件" << endl;
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
}

#define BEGIN_REGISTER_STRUCT_SERIALIZE_XML(className)              bool SerializeXml(className data, const string filename) {\
                                                                        ofstream outputFile(filename, ios::binary);\
                                                                        stringstream origin, encoded;\
                                                                        if (outputFile) {\
                                                                            origin << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;\
                                                                            origin << "<serialization>" << endl;\
                                                                            bool ok = true;
#define REGISTER_STRUCT_MEMBER_SERIALIZE_XML(memberName)                    ok = xml::writeSerialize(data.memberName, origin, 1);\
                                                                            if (!ok) {\
                                                                                return false;\
                                                                            }
#define END_REGISTER_STRUCT_SERIALIZE_XML()                                 origin << "</serialization>" << endl;\
                                                                            if (DEBUG) {\
                                                                                ofstream debugFile(filename + ".debug");\
                                                                                debugFile << origin.str();\
                                                                                debugFile.close();\
                                                                            }\
                                                                            utils::base64::encode(origin, encoded);\
                                                                            outputFile << encoded.str();\
                                                                            outputFile.close();\
                                                                            return ok;\
                                                                        } else {\
                                                                            cerr << "无法打开文件：" << filename << endl;\
                                                                            return false;\
                                                                        }\
                                                                    }

#define BEGIN_REGISTER_STRUCT_DESERIALIZE_XML(className)            bool DeserializeXml(className& data, const string filename) {\
                                                                        ifstream inputFile(filename, ios::binary);\
                                                                        stringstream origin, decoded;\
                                                                        data = className();\
                                                                        if (inputFile) {\
                                                                            origin << inputFile.rdbuf();\
                                                                            utils::base64::decode(origin, decoded);\
                                                                            bool ok = true;
#define REGISTER_STRUCT_MEMBER_DESERIALIZE_XML(memberName)                  ok = xml::readSerialize(data.memberName, decoded);\
                                                                            if (!ok) {\
                                                                                return false;\
                                                                            }
#define END_REGISTER_STRUCT_DESERIALIZE_XML()                               inputFile.close();\
                                                                            return ok;\
                                                                        } else {\
                                                                            cerr << "无法打开文件：" << filename << endl;\
                                                                            return false;\
                                                                        }\
                                                                    }   

#endif