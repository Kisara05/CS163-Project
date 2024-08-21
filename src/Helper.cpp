#include "Helper.h"
using namespace std;
string convertToNonAccentVN(string str) {
    // Initialize a map to include the first is the single character and the second is this character with its accent.
    static std::vector<std::pair<std::string, std::vector<std::string>>> mapAccent;
    if (mapAccent.empty()) {
        mapAccent.emplace_back("A", std::vector<std::string>({"A", "Á", "À", "Ã", "Ạ", "Â", "Ấ", "Ầ", 
                                                                "Ẫ", "Ậ", "Ă", "Ắ", "Ằ", "Ẵ", "Ặ"}));
        mapAccent.emplace_back("a", std::vector<std::string>({"à", "á", "ạ", "ả", "ã", "â", "ầ", "ấ", "ậ",
                                                                "ẩ", "ẫ", "ă", "ằ", "ắ", "ặ", "ẳ", "ẵ"}));
        mapAccent.emplace_back("E", std::vector<std::string>({"E", "É", "È", "Ẽ", "Ẹ", "Ê", "Ế", "Ề", "Ễ", "Ệ"}));
        mapAccent.emplace_back("e", std::vector<std::string>({"è", "é", "ẹ", "ẻ", "ẽ", "ê", "ề", "ế", "ệ", "ể", "ễ"}));
        mapAccent.emplace_back("I", std::vector<std::string>({"I", "Í", "Ì", "Ĩ", "Ị"}));
        mapAccent.emplace_back("i", std::vector<std::string>({"ì", "í", "ị", "ỉ", "ĩ"}));
        mapAccent.emplace_back("O", std::vector<std::string>({"O", "Ó", "Ò", "Õ", "Ọ", "Ô", "Ố", "Ồ",
                                                                "Ỗ", "Ộ", "Ơ", "Ớ", "Ờ", "Ỡ", "Ợ"}));
        mapAccent.emplace_back("o", std::vector<std::string>({"ò", "ó", "ọ", "ỏ", "õ", "ô", "ồ", "ố", "ộ",
                                                                "ổ", "ỗ", "ơ", "ờ", "ớ", "ợ", "ở", "ỡ"}));
        mapAccent.emplace_back("U", std::vector<std::string>({"U", "Ú", "Ù", "Ũ", "Ụ", "Ư", "Ứ", "Ừ", "Ữ", "Ự"}));
        mapAccent.emplace_back("u", std::vector<std::string>({"ù", "ú", "ụ", "ủ", "ũ", "ư", "ừ", "ứ", "ự", "ử", "ữ"}));
        mapAccent.emplace_back("Y", std::vector<std::string>({"Y", "Ý", "Ỳ", "Ỹ", "Ỵ"}));
        mapAccent.emplace_back("y", std::vector<std::string>({"ỳ", "ý", "ỵ", "ỷ", "ỹ"}));
        mapAccent.emplace_back("D", std::vector<std::string>({"Đ"}));
        mapAccent.emplace_back("d", std::vector<std::string>({"đ"}));
        // Some system encode vietnamese combining accent as individual utf-8 characters
        mapAccent.emplace_back("", std::vector<std::string>({"\u0300", "\u0301", "\u0303", "\u0309", "\u0323"})); 
                                                            // Huyền, sắc, hỏi, ngã, nặng
        mapAccent.emplace_back("", std::vector<std::string>({"\u02C6", "\u0306", "\u031B"})); // Â, Ê, Ă, Ơ, Ư
    }
    for (pair<std::string, std::vector<std::string>> &charConverter : mapAccent) {
        const std::string &replacecString = charConverter.first;
        for (std::string &toSearch : charConverter.second) {
            int position = str.find(toSearch);
            while (position != std::string::npos) {
                str.replace(position, toSearch.size(), replacecString);
                position = str.find(toSearch, position + replacecString.size());
            }
        }
    }
    return str;
}

// Convert from capital character to lowercase
string normalize(std::string str) {
    str = convertToNonAccentVN(str);
    std::string normalizeString = "";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
        if ((str[i] >= 'a' && str[i] <= 'z') || str[i] == ' ') {
            normalizeString += str[i];
        }
    }
    return normalizeString;
}

// Function to split the string by the delimiter character
vector<string> &split(const string &str, char delimiter) {
    std::vector<std::string> resString;
    int position = 0;
    while (true) {
        int nextPosition = str.find(delimiter, position);
        resString.push_back(str.substr(position, nextPosition - position));
        if (nextPosition == std::string::npos)
            break;
        position += nextPosition + 1;
    }
    return resString;
}
// serialize and deserialize data structure (Trie --> JSON)