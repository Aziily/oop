#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <iostream>
#include <map>
#include <list>
#include <set>
#include <vector>
#include <string>
#include <type_traits>
#include <memory>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

/// @brief namespace utils contains some useful functions and classes.
namespace utils {
    /// @brief namespace judge contains some functions to judge the type of data.
    namespace judge{
        // define the type of data
        // 0: base type
        // 1: list
        // 2: set
        // 3: vector
        // 4: map
        // 5: pair
        // 6: string
        static const int BASE_TYPE = 0;
        static const int LIST_TYPE = 1;
        static const int SET_TYPE = 2;
        static const int VECTOR_TYPE = 3;
        static const int MAP_TYPE = 4;
        static const int PAIR_TYPE = 5;
        static const int STRING_TYPE = 6;

        // structs to judge the type of data
        template<typename T>
        struct is_list : false_type {};
        template<typename... Args>
        struct is_list<list<Args...>> : true_type {};

        template<typename T>
        struct is_set : false_type {};
        template<typename... Args>
        struct is_set<set<Args...>> : true_type {};

        template<typename T>
        struct is_vector : false_type {};
        template<typename... Args>
        struct is_vector<vector<Args...>> : true_type {};

        template<typename T>
        struct is_map : false_type {};
        template<typename Key, typename Value>
        struct is_map<map<Key, Value>> : true_type {};

        template<typename T>
        struct is_pair : false_type {};
        template<typename First, typename Second>
        struct is_pair<pair<First, Second>> : true_type {};
        
        /// @brief Check the type of data.
        /// @tparam T the type of data
        /// @param data the data
        /// @return the code of type
        template<typename T>
        int CheckType(T data) {
            if (is_list<T>::value) {
                return LIST_TYPE;
            } else if (is_set<T>::value) {
                return SET_TYPE;
            } else if (is_vector<T>::value) {
                return VECTOR_TYPE;
            } else if (is_map<T>::value) {
                return MAP_TYPE;
            } else if (is_pair<T>::value) {
                return PAIR_TYPE;
            } else if (is_same<T, string>::value) {
                return STRING_TYPE;
            } else if (is_same<T, int>::value || is_same<T, float>::value || is_same<T, double>::value || is_same<T, char>::value || is_same<T, bool>::value) {
                return BASE_TYPE;
            } else {
                return -1;
            }
        }

        /// @brief Get the type of data.
        /// @tparam T the type of data
        /// @param data the data
        /// @return the string of type
        template<typename T>
        string GetType(T data) {
            switch (CheckType(data)) {
                case BASE_TYPE:
                    if (is_same<T, int>::value) {
                        return "int";
                    } else if (is_same<T, float>::value) {
                        return "float";
                    } else if (is_same<T, double>::value) {
                        return "double";
                    } else if (is_same<T, char>::value) {
                        return "char";
                    } else if (is_same<T, bool>::value) {
                        return "bool";
                    } else {
                        return "unknown";
                    }
                case LIST_TYPE:
                    return "std_list";
                case SET_TYPE:
                    return "std_set";
                case VECTOR_TYPE:
                    return "std_vector";
                case MAP_TYPE:
                    return "std_map";
                case PAIR_TYPE:
                    return "std_pair";
                case STRING_TYPE:
                    return "std_string";
                default:
                    return "unknown";
            }
        }
    }

    /// @brief trans namespace contains some functions to transform the data type.
    namespace trans {
        /// @brief transform a string to T type.
        /// @tparam T the type to be transformed to
        /// @param data the string to transform
        /// @return the T type data
        template <typename T>
        T toType(string data) {
            if (is_same<T, int>::value) {
                return stoi(data);
            } else if (is_same<T, float>::value) {
                return stof(data);
            } else if (is_same<T, double>::value) {
                return stod(data);
            } else if (is_same<T, char>::value) {
                return data[0];
            } else if (is_same<T, bool>::value) {
                // 1: true, 0: false
                // but I think "true" and "false" are better :(
               if (data == "1") {
                   return true;
               } else {
                   return false;
               }
            } else {
                return T();
            }
        }
    }
    
    /// @brief size namespace contains some functions to get the size of data.
    namespace size {
        /// @brief Get the size of basic type data.
        /// @tparam T the type of data
        /// @param data the data
        /// @return the size of data
        template <typename T>
        int getSize(T data);
        /// @brief Get the size of string.
        /// @param data the string
        /// @return the size of string
        int getSize(string data);
        /// @brief Get the size of list.
        /// @tparam T the type of list item
        /// @param data the list
        /// @return the size of list
        template <typename T>
        int getSize(list<T> data);
        /// @brief Get the size of set.
        /// @tparam T the type of set item
        /// @param data the set
        /// @return the size of set
        template <typename T>
        int getSize(set<T> data);
        /// @brief Get the size of vector.
        /// @tparam T the type of vector item
        /// @param data the vector
        /// @return the size of vector
        template <typename T>
        int getSize(vector<T> data);
        /// @brief Get the size of map.
        /// @tparam T1 the type of map key
        /// @tparam T2 the type of map value
        /// @param data the map
        /// @return the size of map
        template <typename T1, typename T2>
        int getSize(map<T1, T2> data);
        /// @brief Get the size of pair.
        /// @tparam T1 the type of pair first
        /// @tparam T2 the type of pair second
        /// @param data the pair
        /// @return the size of pair
        template <typename T1, typename T2>
        int getSize(pair<T1, T2> data);

        template <typename T>
        int getSize(T data) {
            return sizeof(data);
        }
        int getSize(string data) {
            return data.length();
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
    }

    /// @brief base64 namespace contains some functions to encode and decode with base64.
    namespace base64 {
        // the base64 chars
        static const string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        /// @brief encode the data with base64.
        /// @param data the data to be encoded
        /// @param dst the encoded data
        void encode(stringstream& data, stringstream &dst) {
            int i = 0, j = 0;
            stringstream temp;
            string tmp = data.str(); // to trans ' ' and '\n'
            unsigned char origin[3], encoded[4]; // 3 bytes to 4 bytes
            while (i < tmp.length()) {
                origin[j++] = tmp[i++];
                if (j == 3) {
                    // encode 3 bytes to 4 bytes
                    encoded[0] = (origin[0] & 0xfc) >> 2;
                    encoded[1] = ((origin[0] & 0x3) << 4) + ((origin[1] & 0xf0) >> 4);
                    encoded[2] = ((origin[1] & 0xf) << 2) + ((origin[2] & 0xc0) >> 6);
                    encoded[3] = origin[2] & 0x3f;
                    for (j = 0; j < 4; j++) {
                        temp << base64_chars[encoded[j]];
                    }
                    j = 0;
                }
            }
            // encode the last bytes
            if (j) {
                // fill 0
                for (i = j; i < 3; i++) {
                    origin[i] = '\0';
                }
                encoded[0] = (origin[0] & 0xfc) >> 2;
                encoded[1] = ((origin[0] & 0x3) << 4) + ((origin[1] & 0xf0) >> 4);
                encoded[2] = ((origin[1] & 0xf) << 2) + ((origin[2] & 0xc0) >> 6);
                encoded[3] = origin[2] & 0x3f;
                for (i = 0; i < j + 1; i++) {
                    temp << base64_chars[encoded[i]];
                }
                // fill '='
                while (j++ < 3) {
                    temp << '=';
                }
            }
            dst.str(temp.str()); // copy
        }

        /// @brief decode the data with base64.
        /// @param data the data to be decoded
        /// @param dst the decoded data
        void decode(stringstream& data, stringstream &dst) {
            int i = 0, j = 0;
            stringstream temp;
            string tmp = data.str(); // to trans ' ' and '\n'
            unsigned char origin[4], decoded[3]; // 4 bytes to 3 bytes
            while (i < tmp.length()) {
                if (tmp[i] == '=') {
                    break;
                }
                origin[j++] = tmp[i++];
                if (j == 4) {
                    for (j = 0; j < 4; j++) {
                        origin[j] = base64_chars.find(origin[j]);
                    }
                    // decode 4 bytes to 3 bytes
                    decoded[0] = (origin[0] << 2) + ((origin[1] & 0x30) >> 4);
                    decoded[1] = ((origin[1] & 0xf) << 4) + ((origin[2] & 0x3c) >> 2);
                    decoded[2] = ((origin[2] & 0x3) << 6) + origin[3];
                    for (j = 0; j < 3; j++) {
                        temp << decoded[j];
                    }
                    j = 0;
                }
            }
            // decode the last bytes
            if (j) {
                // fill 0
                for (i = j; i < 4; i++) {
                    origin[i] = '\0';
                }
                for (i = 0; i < 4; i++) {
                    origin[i] = base64_chars.find(origin[i]);
                }
                decoded[0] = (origin[0] << 2) + ((origin[1] & 0x30) >> 4);
                decoded[1] = ((origin[1] & 0xf) << 4) + ((origin[2] & 0x3c) >> 2);
                decoded[2] = ((origin[2] & 0x3) << 6) + origin[3];
                for (i = 0; i < j - 1; i++) {
                    temp << decoded[i];
                }
            }
            dst.str(temp.str()); // copy
        }
    }
}

#endif