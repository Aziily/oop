#include "bin.hpp"
#include "xml.hpp"

using namespace std;

#define HEAD(name)  changeColor(CYAN);\
                    cout << "================================================================================" << endl;\
                    cout << "Begin eval of " << name << " serialization and deserialization" << endl;\
                    cout << "================================================================================" << endl;
#define BEGIN(name) changeColor(YELLOW);\
                    cout << "[begin] eval " << name << endl;

/// @brief the namespace of evaler contains the functions to evaluate the performance
namespace evaler {
    static const string DATA_PATH = "../output/";     // the prefix of output file
    static const string RECORD_PATH = "../record/";   // the prefix of record file

    static const string WHITE = "\033[0m";      // white color
    static const string RED = "\033[31m";       // red color
    static const string GREEN = "\033[32m";     // green color
    static const string CYAN = "\033[36m";      // cyan color
    static const string YELLOW = "\033[33m";    // yellow color
    static const string PURPLE = "\033[35m";    // purple color

    /// @brief change the color of output
    /// @param color the color to change
    void changeColor(string color) {
        cout << color;
    }

    /// @brief evaluate the performance of a specific type
    /// @tparam T the type of data
    /// @param binfile the file to record the performance of bin
    /// @param xmlfile the file to record the performance of xml
    /// @param data the data to serialize and deserialize
    /// @param repeat_times the times to repeat
    template <typename T>
    void evalType(ofstream &binfile, ofstream &xmlfile, T data, int repeat_times) {
        BEGIN(utils::judge::GetType(data));

        time_t start, end;
        T deserialize_data;

        changeColor(PURPLE);
        start = clock();
        for (int i = 0; i < repeat_times; i++) {
            bin::Serialize(data, DATA_PATH + "temp.bin");
        }
        end = clock();
        cout << "Serialize " << utils::judge::GetType(data) << " bin: " << (double) (end - start) / CLOCKS_PER_SEC << "s" << endl;
        binfile << "Serialize " << utils::judge::GetType(data) << " bin: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
        start = clock();
        for (int i = 0; i < repeat_times; i++) {
            bin::Deserialize(deserialize_data, DATA_PATH + "temp.bin");
        }
        end = clock();
        cout << "Deserialize " << utils::judge::GetType(data) << " bin: " << (double) (end - start) / CLOCKS_PER_SEC << "s" << endl;
        binfile << "Deserialize " << utils::judge::GetType(data) << " bin: " << (double) (end - start) / CLOCKS_PER_SEC << endl;

        changeColor(GREEN);
        start = clock();
        for (int i = 0; i < repeat_times; i++) {
            xml::Serialize(data, DATA_PATH + "temp.xml");
        }
        end = clock();
        cout << "Serialize " << utils::judge::GetType(data) << " xml: " << (double) (end - start) / CLOCKS_PER_SEC << "s" << endl;
        xmlfile << "Serialize " << utils::judge::GetType(data) << " xml: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
        start = clock();
        for (int i = 0; i < repeat_times; i++) {
            xml::Deserialize(deserialize_data, DATA_PATH + "temp.xml");
        }
        end = clock();
        cout << "Deserialize " << utils::judge::GetType(data) << " xml: " << (double) (end - start) / CLOCKS_PER_SEC << "s" << endl;
        xmlfile << "Deserialize " << utils::judge::GetType(data) << " xml: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
    }

    /// @brief evaluate the performance both about type and size
    void AllEvals() {
        ofstream binfile(RECORD_PATH + "bin.txt");
        ofstream xmlfile(RECORD_PATH + "xml.txt");
        if (!binfile.is_open() || !xmlfile.is_open()) {
            cout << "Fail to open file" << endl;
            return;
        }

        // type eval
        HEAD("type");
        bool serialize_bool = true;
        char serialize_char = 'a';
        int serialize_int = 0;
        float serialize_float = 0;
        double serialize_double = 0;
        string serialize_string = "length 8";
        vector<double> serialize_vector = {1.0};
        list<double> serialize_list = {1.0};
        set<double> serialize_set = {1.0};
        map<float, float> serialize_map = {{1.0, 1.0}};
        pair<float, float> serialize_pair = {1.0, 1.0};

        int repeat_times = 1000;
        // all types
        evalType(binfile, xmlfile, serialize_bool, repeat_times * 8);
        evalType(binfile, xmlfile, serialize_char, repeat_times * 8);
        evalType(binfile, xmlfile, serialize_int, repeat_times * 2);
        evalType(binfile, xmlfile, serialize_float, repeat_times * 2);
        evalType(binfile, xmlfile, serialize_double, repeat_times);
        evalType(binfile, xmlfile, serialize_string, repeat_times);
        evalType(binfile, xmlfile, serialize_vector, repeat_times);
        evalType(binfile, xmlfile, serialize_list, repeat_times);
        evalType(binfile, xmlfile, serialize_set, repeat_times);
        evalType(binfile, xmlfile, serialize_map, repeat_times);
        evalType(binfile, xmlfile, serialize_pair, repeat_times);

        // split
        binfile << "===" << endl;
        xmlfile << "===" << endl;

        // size eval
        HEAD("size");
        string serialize_string_eight, deserialize_string_eight;
        vector<double> serialize_vector_double, deserialize_vector_double;
        list<double> serialize_list_double, deserialize_list_double;
        set<double> serialize_set_double, deserialize_set_double;
        map<float, float> serialize_map_float_float, deserialize_map_float_float;

        clock_t start, end;
        // string length
        {
            BEGIN("string length");
            changeColor(PURPLE);
            cout << "Serialize string length bin:";
            binfile << "Serialize string length bin:";
            for (int i = 10; i < 10000; i *= 10) {
                cout << " ";
                binfile << " ";
                serialize_string_eight = string(i * 8, 'a');
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    bin::Serialize(serialize_string_eight, DATA_PATH + "temp.bin");
                }
                end = clock();
                cout <<  (double) (end - start) / CLOCKS_PER_SEC << "s" << "|";
                binfile << (double) (end - start) / CLOCKS_PER_SEC << "|";
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    bin::Deserialize(deserialize_string_eight, DATA_PATH + "temp.bin");
                }
                end = clock();
                cout << (double) (end - start) / CLOCKS_PER_SEC << "s";
                binfile << (double) (end - start) / CLOCKS_PER_SEC;
            }
            cout << endl;
            binfile << endl;
            changeColor(GREEN);
            cout << "Serialize string length xml:";
            xmlfile << "Serialize string length xml:";
            for (int i = 10; i < 10000; i *= 10) {
                cout << " ";
                xmlfile << " ";
                serialize_string_eight = string(i * 8, 'a');
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    xml::Serialize(serialize_string_eight, DATA_PATH + "temp.xml");
                }
                end = clock();
                cout <<  (double) (end - start) / CLOCKS_PER_SEC << "s" << "|";
                xmlfile << (double) (end - start) / CLOCKS_PER_SEC << "|";
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    xml::Deserialize(deserialize_string_eight, DATA_PATH + "temp.xml");
                }
                end = clock();
                cout << (double) (end - start) / CLOCKS_PER_SEC << "s";
                xmlfile << (double) (end - start) / CLOCKS_PER_SEC;
            }
            cout << endl;
            xmlfile << endl;
        }
        
        // vector size
        {
            BEGIN("vector size");
            changeColor(PURPLE);
            cout << "Serialize vector double bin:";
            binfile << "Serialize vector double bin:";
            for (int i = 10; i < 10000; i *= 10) {
                cout << " ";
                binfile << " ";
                serialize_vector_double = vector<double>(i, 1.0);
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    bin::Serialize(serialize_vector_double, DATA_PATH + "temp.bin");
                }
                end = clock();
                cout <<  (double) (end - start) / CLOCKS_PER_SEC << "s" << "|";
                binfile << (double) (end - start) / CLOCKS_PER_SEC << "|";
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    bin::Deserialize(deserialize_vector_double, DATA_PATH + "temp.bin");
                }
                end = clock();
                cout << (double) (end - start) / CLOCKS_PER_SEC << "s";
                binfile << (double) (end - start) / CLOCKS_PER_SEC;
            }
            cout << endl;
            binfile << endl;
            changeColor(GREEN);
            cout << "Serialize vector double xml:";
            xmlfile << "Serialize vector double xml:";
            for (int i = 10; i < 10000; i *= 10) {
                cout << " ";
                xmlfile << " ";
                serialize_vector_double = vector<double>(i, 1.0);
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    xml::Serialize(serialize_vector_double, DATA_PATH + "temp.xml");
                }
                end = clock();
                cout <<  (double) (end - start) / CLOCKS_PER_SEC << "s" << "|";
                xmlfile << (double) (end - start) / CLOCKS_PER_SEC << "|";
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    xml::Deserialize(deserialize_vector_double, DATA_PATH + "temp.xml");
                }
                end = clock();
                cout << (double) (end - start) / CLOCKS_PER_SEC << "s";
                xmlfile << (double) (end - start) / CLOCKS_PER_SEC;
            }
            cout << endl;
            xmlfile << endl;
        }

        // list size
        {
            BEGIN("list size");
            changeColor(PURPLE);
            cout << "Serialize list double bin:";
            binfile << "Serialize list double bin:";
            for (int i = 10; i < 10000; i *= 10) {
                cout << " ";
                binfile << " ";
                serialize_list_double = list<double>(i, 1.0);
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    bin::Serialize(serialize_list_double, DATA_PATH + "temp.bin");
                }
                end = clock();
                cout <<  (double) (end - start) / CLOCKS_PER_SEC << "s" << "|";
                binfile << (double) (end - start) / CLOCKS_PER_SEC << "|";
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    bin::Deserialize(deserialize_list_double, DATA_PATH + "temp.bin");
                }
                end = clock();
                cout << (double) (end - start) / CLOCKS_PER_SEC << "s";
                binfile << (double) (end - start) / CLOCKS_PER_SEC;
            }
            cout << endl;
            binfile << endl;
            changeColor(GREEN);
            cout << "Serialize list double xml:";
            xmlfile << "Serialize list double xml:";
            for (int i = 10; i < 10000; i *= 10) {
                cout << " ";
                xmlfile << " ";
                serialize_list_double = list<double>(i, 1.0);
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    xml::Serialize(serialize_list_double, DATA_PATH + "temp.xml");
                }
                end = clock();
                cout <<  (double) (end - start) / CLOCKS_PER_SEC << "s" << "|";
                xmlfile << (double) (end - start) / CLOCKS_PER_SEC << "|";
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    xml::Deserialize(deserialize_list_double, DATA_PATH + "temp.xml");
                }
                end = clock();
                cout << (double) (end - start) / CLOCKS_PER_SEC << "s";
                xmlfile << (double) (end - start) / CLOCKS_PER_SEC;
            }
            cout << endl;
            xmlfile << endl;
        }

        // set size
        {
            BEGIN("set size");
            changeColor(PURPLE);
            cout << "Serialize set double bin:";
            binfile << "Serialize set double bin:";
            for (int i = 10; i < 10000; i *= 10) {
                cout << " ";
                binfile << " ";
                serialize_set_double = set<double>();
                for (int j = 0; j < i; j++) {
                    serialize_set_double.insert(j);
                }
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    bin::Serialize(serialize_set_double, DATA_PATH + "temp.bin");
                }
                end = clock();
                cout <<  (double) (end - start) / CLOCKS_PER_SEC << "s" << "|";
                binfile << (double) (end - start) / CLOCKS_PER_SEC << "|";
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    bin::Deserialize(deserialize_set_double, DATA_PATH + "temp.bin");
                }
                end = clock();
                cout << (double) (end - start) / CLOCKS_PER_SEC << "s";
                binfile << (double) (end - start) / CLOCKS_PER_SEC;
            }
            cout << endl;
            binfile << endl;
            changeColor(GREEN);
            cout << "Serialize set double xml:";
            xmlfile << "Serialize set double xml:";
            for (int i = 10; i < 10000; i *= 10) {
                cout << " ";
                xmlfile << " ";
                serialize_set_double = set<double>();
                for (int j = 0; j < i; j++) {
                    serialize_set_double.insert(j);
                }
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    xml::Serialize(serialize_set_double, DATA_PATH + "temp.xml");
                }
                end = clock();
                cout <<  (double) (end - start) / CLOCKS_PER_SEC << "s" << "|";
                xmlfile << (double) (end - start) / CLOCKS_PER_SEC << "|";
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    xml::Deserialize(deserialize_set_double, DATA_PATH + "temp.xml");
                }
                end = clock();
                cout << (double) (end - start) / CLOCKS_PER_SEC << "s";
                xmlfile << (double) (end - start) / CLOCKS_PER_SEC;
            }
            cout << endl;
            xmlfile << endl;
        }

        // map size
        {
            BEGIN("map size");
            changeColor(PURPLE);
            cout << "Serialize map float float bin:";
            binfile << "Serialize map float float bin:";
            for (int i = 10; i < 10000; i *= 10) {
                cout << " ";
                binfile << " ";
                serialize_map_float_float = map<float, float>();
                for (int j = 0; j < i; j++) {
                    serialize_map_float_float.insert(pair<float, float>(j, j));
                }
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    bin::Serialize(serialize_map_float_float, DATA_PATH + "temp.bin");
                }
                end = clock();
                cout <<  (double) (end - start) / CLOCKS_PER_SEC << "s" << "|";
                binfile << (double) (end - start) / CLOCKS_PER_SEC << "|";
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    bin::Deserialize(deserialize_map_float_float, DATA_PATH + "temp.bin");
                }
                end = clock();
                cout << (double) (end - start) / CLOCKS_PER_SEC << "s";
                binfile << (double) (end - start) / CLOCKS_PER_SEC;
            }
            cout << endl;
            binfile << endl;
            changeColor(GREEN);
            cout << "Serialize map float float xml:";
            xmlfile << "Serialize map float float xml:";
            for (int i = 10; i < 10000; i *= 10) {
                cout << " ";
                xmlfile << " ";
                serialize_map_float_float = map<float, float>();
                for (int j = 0; j < i; j++) {
                    serialize_map_float_float.insert(pair<float, float>(j, j));
                }
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    xml::Serialize(serialize_map_float_float, DATA_PATH + "temp.xml");
                }
                end = clock();
                cout <<  (double) (end - start) / CLOCKS_PER_SEC << "s" << "|";
                xmlfile << (double) (end - start) / CLOCKS_PER_SEC << "|";
                start = clock();
                for (int j = 0; j < repeat_times; j++) {
                    xml::Deserialize(deserialize_map_float_float, DATA_PATH + "temp.xml");
                }
                end = clock();
                cout << (double) (end - start) / CLOCKS_PER_SEC << "s";
                xmlfile << (double) (end - start) / CLOCKS_PER_SEC;
            }
            cout << endl;
            xmlfile << endl;
        }
        
        binfile << "===" << endl;
        xmlfile << "===" << endl;

        binfile.close();
        xmlfile.close();

        changeColor(WHITE);
    }
}

int main() {
    evaler::AllEvals();
    return 0;
}