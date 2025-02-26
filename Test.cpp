#include<bits/stdc++.h>

using namespace std;

unordered_set<string> wordSet;
queue<pair<string, string>> wordQueue;

string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos)
        return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}


vector<string> getPrefixes(const string &word) {
    vector<string> prefixes;
    string currentPrefix;
    for (char c : word) {
        currentPrefix.push_back(c);
        if (wordSet.find(currentPrefix) != wordSet.end()) {
            prefixes.push_back(currentPrefix);
        }
    }
    return prefixes;
}

void addWordsFromFile(const string &filePath) {
    ifstream inFile(filePath);
    if (!inFile.is_open()) {
        cout << "An error occurred while reading the file!" << endl;
        exit(0);
    }
    string line;
    while (getline(inFile, line)) {
        string word = trim(line);
        if (word.empty())
            continue;
        wordSet.insert(word);
        vector<string> prefixes = getPrefixes(word);
        for (const string &prefix : prefixes) {
            wordQueue.push(make_pair(word, word.substr(prefix.length())));
        }
    }
    inFile.close();
}

pair<string, string> findLongestCompoundWords() {
    string longestCompoundWord = "";
    int longestCompoundWordLength = 0;
    string secondLongestCompoundWord = "";

    while (!wordQueue.empty()) {
        pair<string, string> wp = wordQueue.front();
        wordQueue.pop();
        const string &currentWord = wp.first;
        const string &remainder = wp.second;
        if (!remainder.empty() && wordSet.find(remainder) != wordSet.end() &&
            currentWord.length() > static_cast<size_t>(longestCompoundWordLength)) {
            secondLongestCompoundWord = longestCompoundWord;
            longestCompoundWord = currentWord;
            longestCompoundWordLength = currentWord.length();
        } else {
            vector<string> prefixes = getPrefixes(remainder);
            for (const string &prefix : prefixes) {
                wordQueue.push(make_pair(currentWord, remainder.substr(prefix.length())));
            }
        }
    }

    return make_pair(longestCompoundWord, secondLongestCompoundWord);
}

int main() {
    auto startTime = chrono::high_resolution_clock::now();

    // Change name of the file ("Input_01.txt" or "Input_02.txt")
    string fileName = "Input_02.txt";
    addWordsFromFile(fileName);
    pair<string, string> result = findLongestCompoundWords();

    auto endTime = chrono::high_resolution_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

    cout << "Longest Compound Word " << result.first << endl;
    cout << "Second Longest Compound Word " << result.second << endl;
    cout << "Time taken to process file " << fileName << " " << elapsed << " milli seconds" << endl;

    return 0;
}
