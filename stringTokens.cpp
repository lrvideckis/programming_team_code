//this function takes in a string of words seperated by single spaces and
//seperates it into a vector of those space seperated strings

vector<string> seperate(string &line) {
    int prev = -1;
    vector<string> answer;
    for (int i = 0; i < (int)line.size(); i++) {
        if (line[i] == ' ') {
            answer.push_back(line.substr(prev + 1, i - prev - 1));
            prev = i;
        }
    }
    answer.push_back(line.substr(prev + 1));
    return answer;
}
