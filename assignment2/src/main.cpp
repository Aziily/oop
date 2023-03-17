#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>

#define GAP "\t" // use what to split while printing
using namespace std;

/// @brief a function split a string by given char
/// @param str the string needs to be split
/// @param sign the char to split
/// @return the vector of split string items
vector<string> split(const string& str, char sign) {
    stringstream ss(str);
    string item;
    vector<string> res;
    while (getline(ss, item, sign)) { // split by sign
        if (!item.empty()) {
            res.push_back(item);
        }
    }
    return res;
}

/// @brief a class to store one record and offer some functions
class oneRecord{
public:
    int id; // the id
    string name; // the name
    map<string, int> score; // the scores

private:
    /// @brief calculate one's average score
    /// @return the average score
    double calAverage() {
        double all = 0.0;
        int num = 0;
        for (auto scoreItem:score) {
            num ++;
            all += double(scoreItem.second);
        }
        return all / num;
    }
    /// @brief judge whether a score is an int
    /// @param score the score
    /// @return true if is int
    bool isInt(double score) {
        if (score == int(score)) return true;
        return false;
    }

public:
    /// @brief basic init function for onerecord
    /// @param initId the id
    /// @param initName the name
    /// @param initScore the scores map of one person
    oneRecord(int initId, string initName, map<string, int> initScore){
        id = initId;
        name = initName;
        for (auto scoreItem:initScore) score[scoreItem.first] = scoreItem.second;
    }
    /// @brief use concated string to initialize onerecord
    /// @param initId the id
    /// @param all a string of name and scores in format
    oneRecord(int initId, string all) {
        id = initId;
        auto parts = split(all, '/'); // split by '/'
        if (parts.size() < 1) {
            cout << "Error Record" << endl;
            return;
        }
        name = parts[0];
        if (parts.size() >= 2) {
            for (int i = 1; i < parts.size(); i ++) {
                auto scoreMap = split(parts[i], ':');
                if (scoreMap.size() < 2) {
                    cout << "Error Record" << endl;
                    return;
                }
                stringstream ss(scoreMap[1]);
                int scoreNum; ss >> scoreNum;
                score[scoreMap[0]] = scoreNum;
            }
        }
    }

    /// @brief output one record in format
    /// @param scoreIds ids to be print
    void output(vector<string> scoreIds) {
        cout << id << GAP << name << GAP;
        for (auto scoreId:scoreIds) {
            if (score.count(scoreId)) {
                cout << score[scoreId] << GAP;
            } else {
                cout << GAP;
            }
        }
        cout << fixed << (isInt(calAverage()) ? setprecision(0) : setprecision(6))\
        << calAverage() << GAP << endl;
    }
};

/// @brief a database class for store all records
class dataBase{
private:
    map<int, oneRecord> records; // records of a database
    vector<string> scoreIds;

private:
    /// @brief a function help output scores
    /// @tparam T int/double
    /// @param prompt the prompt of what's the meaning of scores
    /// @param scores the scores to output
    template <typename T>
    void outputScores(string prompt, vector<T> scores) {
        cout << prompt << GAP;
        for (auto item : scores) {
            cout << fixed << setprecision(1) << item << GAP;
        }
        cout << endl;
    }

public:
    /// @brief a init function by offering a path of file
    /// @param path the path of file
    dataBase(string path) {
        ifstream input(path);
        string row;
        int no = 1;
        while(getline(input, row)) { //split by rows
            // add one record
            oneRecord record = oneRecord(no, row);
            for (auto scoreItem:record.score) {
                scoreIds.push_back(scoreItem.first);
            }
            records.insert(pair<int, oneRecord>(no, record));
            no ++;
        }
        set<string> tempSet(scoreIds.begin(), scoreIds.end());
        scoreIds.assign(tempSet.begin(), tempSet.end());
    }

    /// @brief calculate average scores of a database
    /// @return scores 
    vector<double> calAverageScores() {
        vector<double> res(scoreIds.size(), 0.0);
        vector<int> num(scoreIds.size(), 0);
        for (auto record : records) {
            for (int i = 0; i < scoreIds.size(); i ++) {
                if (record.second.score.count(scoreIds[i])) {
                    res[i] += record.second.score[scoreIds[i]];
                    num[i] ++;
                }
            }
        }
        for (int i = 0; i < res.size(); i ++) {
            res[i] /= num[i];
        }
        return res;
    }
    /// @brief calculate highest scores of a database
    /// @return scores 
    vector<int> getMaxScores() {
        vector<int> res(scoreIds.size(), 0);
        for (auto record : records) {
            for (int i = 0; i < scoreIds.size(); i ++) {
                if (record.second.score.count(scoreIds[i])) {
                    res[i] = max(res[i], record.second.score[scoreIds[i]]);
                }
            }
        }
        return res;
    }
    /// @brief calculate lowest scores of a database
    /// @return scores 
    vector<int> getMinScores() {
        vector<int> res(scoreIds.size(), 5);
        for (auto record : records) {
            for (int i = 0; i < scoreIds.size(); i ++) {
                if (record.second.score.count(scoreIds[i])) {
                    res[i] = min(res[i], record.second.score[scoreIds[i]]);
                }
            }
        }
        return res;
    }
    /// @brief output all records of the database in format
    void outputAllRecords() {
        cout << "no" << GAP << "name" << GAP ;
        for (auto scoreId:scoreIds) {
            cout << scoreId << GAP;
        }
        cout << "average" << GAP << endl;
        for (auto record : records) {
            record.second.output(scoreIds);
        }
    }
    /// @brief the function outputs all records in format and the average/max/min scores
    void outputAll() {
        outputAllRecords();
        vector<double> averages = calAverageScores();
        cout << GAP; outputScores("average", averages);
        vector<int> mins = getMinScores();
        cout << GAP; outputScores("min", mins);
        vector<int> maxs = getMaxScores();
        cout << GAP; outputScores("max", maxs);
    }
};

/// @brief main function
/// @param argc number of inputs
/// @param argv input strings
/// @return errcode, 0 if success
int main(int argc, char *argv[]) {
    // modify the path of records
    string path = "../data/basic_records.txt";
    if (argc == 2) path = argv[1];

    // initialize one database
    dataBase db = dataBase(path);
    db.outputAll();

    return 0;
}