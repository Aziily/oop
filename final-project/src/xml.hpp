#ifndef _XML_HPP_
#define _XML_HPP_

#include "utils.hpp"

using namespace std;

namespace xml {
    static const int TAB_SPACE = 2;

    template <typename T>
    bool writeSerialize(const T data, ofstream& outputFile, int tabCount) {
        if (outputFile) {
            outputFile << string(tabCount * TAB_SPACE, ' ') << "<" << utils::judge::GetType(data) << ">" << endl;
            outputFile << string(tabCount * TAB_SPACE, ' ') << data << endl;
            outputFile << string(tabCount * TAB_SPACE, ' ') << "</" << utils::judge::GetType(data) << ">" << endl;
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }

    template <typename T>
    bool readSerialize(T& data, ifstream& inputFile) {
        if (inputFile) {
            string line;
            while (getline(inputFile, line)) {
                if (line.find("<" + utils::judge::GetType(data) + ">") != string::npos) {
                    getline(inputFile, line);
                    data = utils::trans::toType<T>(line);
                    getline(inputFile, line);
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
        if (outputFile) {
            outputFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
            outputFile << "<serialization>" << endl;
            writeSerialize(data, outputFile, 1);
            outputFile << "</serialization>" << endl;
            outputFile.close();
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }

    template <typename T>
    bool Deserialize(T& data, const string filename) {
        ifstream inputFile(filename);
        if (inputFile) {
            string line;
            while (getline(inputFile, line)) {
                if (line.find("<serialization>") != string::npos) {
                    readSerialize(data, inputFile);
                }
            }
            inputFile.close();
            return true;
        } else {
            cerr << "无法打开文件" << endl;
            return false;
        }
    }
}

#endif