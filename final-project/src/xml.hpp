#ifndef _XML_HPP_
#define _XML_HPP_

// the signal whether to output the file before encoding
#define DEBUG false

#include "utils.hpp"

using namespace std;

// macro for serialize
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

// macro for deserialize
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

/// @brief namespace for xml serialize and deserialize
namespace xml {
    static const int TAB_SPACE = 2; // tab space for xml

    /// @brief writeSerialize for basic type
    /// @tparam T the type of data
    /// @param data the data to be serialized
    /// @param outputFile the stringstream to output
    /// @param tabCount the tab count for xml
    /// @return true if success, false if fail
    template <typename T>
    bool writeSerialize(const T data, stringstream& outputFile, int tabCount);
    /// @brief writeSerialize for string
    /// @param data the string to be serialized
    /// @param outputFile the stringstream to output
    /// @param tabCount the tab count for xml
    /// @return true if success, false if fail
    bool writeSerialize(const string data, stringstream& outputFile, int tabCount);
    /// @brief writeSerialize for vector
    /// @tparam T the type of vector item
    /// @param data the vector to be serialized
    /// @param outputFile the stringstream to output
    /// @param tabCount the tab count for xml
    /// @return true if success, false if fail
    template <typename T>
    bool writeSerialize(const vector<T> data, stringstream& outputFile, int tabCount);
    /// @brief writeSerialize for list
    /// @tparam T the type of list item
    /// @param data the list to be serialized
    /// @param outputFile the stringstream to output
    /// @param tabCount the tab count for xml
    /// @return true if success, false if fail
    template <typename T>
    bool writeSerialize(const list<T> data, stringstream& outputFile, int tabCount);
    /// @brief writeSerialize for set
    /// @tparam T the type of set item
    /// @param data the set to be serialized
    /// @param outputFile the stringstream to output
    /// @param tabCount the tab count for xml
    /// @return true if success, false if fail
    template <typename T>
    bool writeSerialize(const set<T> data, stringstream& outputFile, int tabCount);
    /// @brief writeSerialize for map
    /// @tparam T1 the type of map key
    /// @tparam T2 the type of map value
    /// @param data the map to be serialized
    /// @param outputFile the stringstream to output
    /// @param tabCount the tab count for xml
    /// @return true if success, false if fail
    template <typename T1, typename T2>
    bool writeSerialize(const map<T1, T2> data, stringstream& outputFile, int tabCount);
    /// @brief writeSerialize for pair
    /// @tparam T1 the type of pair first
    /// @tparam T2 the type of pair second
    /// @param data the pair to be serialized
    /// @param outputFile the stringstream to output
    /// @param tabCount the tab count for xml
    /// @return true if success, false if fail
    template <typename T1, typename T2>
    bool writeSerialize(const pair<T1, T2> data, stringstream& outputFile, int tabCount);

    /// @brief readSerialize for basic type
    /// @tparam T the type of data
    /// @param data the data to be deserialized
    /// @param inputFile the stringstream to input
    /// @return true if success, false if fail
    template <typename T>
    bool readSerialize(T& data, stringstream& inputFile);
    /// @brief readSerialize for string
    /// @param data the string to be deserialized
    /// @param inputFile the stringstream to input
    /// @return true if success, false if fail
    bool readSerialize(string& data, stringstream& inputFile);
    /// @brief readSerialize for vector
    /// @tparam T the type of vector item
    /// @param data the vector to be deserialized
    /// @param inputFile the stringstream to input
    /// @return true if success, false if fail
    template <typename T>
    bool readSerialize(vector<T>& data, stringstream& inputFile);
    /// @brief readSerialize for list
    /// @tparam T the type of list item
    /// @param data the list to be deserialized
    /// @param inputFile the stringstream to input
    /// @return true if success, false if fail
    template <typename T>
    bool readSerialize(list<T>& data, stringstream& inputFile);
    /// @brief readSerialize for set
    /// @tparam T the type of set item
    /// @param data the set to be deserialized
    /// @param inputFile the stringstream to input
    /// @return true if success, false if fail
    template <typename T>
    bool readSerialize(set<T>& data, stringstream& inputFile);
    /// @brief readSerialize for map
    /// @tparam T1 the type of map key
    /// @tparam T2 the type of map value
    /// @param data the map to be deserialized
    /// @param inputFile the stringstream to input
    /// @return true if success, false if fail
    template <typename T1, typename T2>
    bool readSerialize(map<T1, T2>& data, stringstream& inputFile);
    /// @brief readSerialize for pair
    /// @tparam T1 the type of pair first
    /// @tparam T2 the type of pair second
    /// @param data the pair to be deserialized
    /// @param inputFile the stringstream to input
    /// @return true if success, false if fail
    template <typename T1, typename T2>
    bool readSerialize(pair<T1, T2>& data, stringstream& inputFile);

    /// @brief Serialize
    /// @tparam T the type of data
    /// @param data the data to be serialized
    /// @param filename the filename to output
    /// @return true if success, false if fail
    template <typename T>
    bool Serialize(const T data, const string filename);
    /// @brief Serialize
    /// @tparam T the type of data
    /// @param data unique_ptr of type T to be serialized
    /// @param filename the filename to output
    /// @return true if success, false if fail
    template <typename T>
    bool Serialize(const unique_ptr<T>& data, const string filename);
    /// @brief Serialize
    /// @tparam T the type of data
    /// @param data shared_ptr of type T to be serialized
    /// @param filename the filename to output
    /// @return true if success, false if fail
    template <typename T>
    bool Serialize(const shared_ptr<T>& data, const string filename);
    /// @brief Serialize
    /// @tparam T the type of data
    /// @param data weak_ptr of type T to be serialized
    /// @param filename the filename to output
    /// @return true if success, false if fail
    template <typename T>
    bool Serialize(const weak_ptr<T>& data, const string filename);
    /// @brief Deserialize
    /// @tparam T the type of data
    /// @param data the data to be deserialized
    /// @param filename the filename to input
    /// @return true if success, false if fail
    template <typename T>
    bool Deserialize(T& data, const string filename);
    /// @brief Deserialize
    /// @tparam T the type of data
    /// @param data unique_ptr of type T to be deserialized
    /// @param filename the filename to input
    /// @return true if success, false if fail
    template <typename T>
    bool Deserialize(unique_ptr<T>& data, const string filename);
    /// @brief Deserialize
    /// @tparam T the type of data
    /// @param data shared_ptr of type T to be deserialized
    /// @param filename the filename to input
    /// @return true if success, false if fail
    template <typename T>
    bool Deserialize(shared_ptr<T>& data, const string filename);
    /// @brief Deserialize
    /// @tparam T the type of data
    /// @param data weak_ptr of type T to be deserialized
    /// @param filename the filename to input
    /// @return true if success, false if fail
    template <typename T>
    bool Deserialize(weak_ptr<T>& data, const string filename);

    template <typename T>
    bool writeSerialize(const T data, stringstream& outputFile, int tabCount) {
        if (outputFile) {
            // set precision to 20 to avoid precision loss
            // ignore the error made by the extra precision
            outputFile << string(tabCount * TAB_SPACE, ' ') << "<" << utils::judge::GetType(data) << ">" << fixed << setprecision(20) << data << "</" << utils::judge::GetType(data) << ">" << endl;
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
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
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    template <typename T>
    bool writeSerialize(const vector<T> data, stringstream& outputFile, int tabCount) {
        if (outputFile) {
            // output with the size of vector
            outputFile << string(tabCount * TAB_SPACE, ' ') << "<" << utils::judge::GetType(data) << " size=\"" << data.size() << "\">" << endl;
            for (auto it = data.begin(); it != data.end(); ++it) {
                writeSerialize(*it, outputFile, tabCount + 1);
            }
            outputFile << string(tabCount * TAB_SPACE, ' ') << "</" << utils::judge::GetType(data) << ">" << endl;
            return true;
        } else {
            cerr << "Cannot open the file!" << endl;
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
            cerr << "Cannot open the file!" << endl;
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
            cerr << "Cannot open the file!" << endl;
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
            cerr << "Cannot open the file!" << endl;
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
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }
    

    template <typename T>
    bool readSerialize(T& data, stringstream& inputFile) {
        if (inputFile) {
            string line;
            while (getline(inputFile, line)) {
                // find the data prompt
                if (line.find("<" + utils::judge::GetType(data)) != string::npos) {
                    string temp = line.substr(line.find(">") + 1, line.find("</") - line.find(">") - 1);
                    data = utils::trans::toType<T>(temp);
                }
                // find the end of the data
                if (line.find("</" + utils::judge::GetType(data)) != string::npos) {
                    return true;
                }
            }
            return false;
        } else {
            cerr << "Cannot open the file!" << endl;
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
            cerr << "Cannot open the file!" << endl;
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
            cerr << "Cannot open the file!" << endl;
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
            cerr << "Cannot open the file!" << endl;
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
            cerr << "Cannot open the file!" << endl;
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
            cerr << "Cannot open the file!" << endl;
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
            cerr << "Cannot open the file!" << endl;
            return false;
        }
    }

    template <typename T>
    bool Serialize(const T data, const string filename) {
        ofstream outputFile(filename);
        stringstream origin, encoded; // origin is the original file, encoded is the encoded file
        if (outputFile) {
            // write the file
            origin << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl; // head
            origin << "<serialization>" << endl; // serialization
            bool ok = writeSerialize(data, origin, 1); // recursive write
            origin << "</serialization>" << endl; // end
            if (DEBUG) { // whether to write the unencoded file
                ofstream debugFile(filename + ".debug");
                debugFile << origin.str();
                debugFile.close();
            }
            utils::base64::encode(origin, encoded); // encode
            outputFile << encoded.str(); // write
            outputFile.close();
            return ok;
        } else {
            cerr << "Cannot open the file: " << filename << endl;
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
        stringstream origin, decoded; // origin is the original file, decoded is the decoded file
        data = T(); // clear the data
        if (inputFile) {
            origin << inputFile.rdbuf(); // read the file
            utils::base64::decode(origin, decoded); // decode
            bool ok = readSerialize(data, decoded); // recursive read
            inputFile.close();
            return ok;
        } else {
            cerr << "Cannot open the file: " << filename << endl;
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

#endif