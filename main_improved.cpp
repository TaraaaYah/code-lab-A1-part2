#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <cctype>
using namespace std;

struct Joke { string question, punchline; };

// Remove trailing \r or whitespace (handles files saved on Windows)
string trim(string text) {
    while (!text.empty() && (text.back() == '\r' || text.back() == '\n' || text.back() == ' '))
        text.pop_back();
    return text;
}

// Load jokes from the text file
vector<Joke> loadJokes(const string& filename) {
    ifstream file(filename);
    vector<Joke> jokes;
    string line;
    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << "\n";
        return jokes;
    }
    while (getline(file, line)) {
        line = trim(line);
        size_t q = line.find('?');
        if (!line.empty() && q != string::npos)
            jokes.push_back({line.substr(0, q + 1), line.substr(q + 1)});
    }
    return jokes;
}

// Convert text to lowercase
string toLowerCase(string text) {
    transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) { return tolower(c); });
    return text;
}

int main() {
    vector<Joke> jokes = loadJokes("randomJokes.txt");
    if (jokes.empty()) {
        cout << "No valid jokes found in the file.\n";
        return 1;
    }

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> pick(0, static_cast<int>(jokes.size()) - 1);

    int lastIndex = -1;
    string command;
    char again = 'y';

    while (again == 'y') {
        cout << "\nType 'Alexa, tell me a joke' or 'quit': ";
        getline(cin, command);
        command = toLowerCase(trim(command));

        if (command == "quit" || command == "exit")
            break;

        if (command != "alexa, tell me a joke") {
            cout << "Sorry, I didn't understand that.\n";
            continue;
        }

        int index = pick(generator);
        if (jokes.size() > 1)
            while (index == lastIndex) index = pick(generator);
        lastIndex = index;

        cout << "\n" << jokes[index].question << endl;
        cout << "Press Enter to reveal the punchline...";
        getline(cin, command);
        cout << jokes[index].punchline << endl;

        cout << "\nWould you like another joke? (y/n): ";
        getline(cin, command);
        command = toLowerCase(trim(command));
        again = (command == "y" || command == "yes") ? 'y' : 'n';
    }

    cout << "Goodbye!\n";
    return 0;
}
