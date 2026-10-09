#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <cctype>
using namespace std;

// A single joke, split into its question and punchline
struct Joke {
    string question;
    string punchline;
};

// Function 1: Remove trailing \r or whitespace (handles files saved on Windows)
string trim(string text) {
    while (!text.empty() && (text.back() == '\r' || text.back() == '\n' || text.back() == ' '))
        text.pop_back();
    return text;
}

// Function 2: Load jokes from the text file
vector<Joke> loadJokes(const string& filename) {
    ifstream file(filename);
    vector<Joke> jokes;
    string line;

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << "\n";
        return jokes; // empty vector signals failure to caller
    }

    while (getline(file, line)) {
        line = trim(line);
        size_t question = line.find('?');

        if (!line.empty() && question != string::npos) {
            Joke joke;
            joke.question = line.substr(0, question + 1);
            joke.punchline = line.substr(question + 1);
            jokes.push_back(joke);
        }
    }

    file.close();
    return jokes;
}

// Function 3: Convert text to lowercase
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

    int lastIndex = -1; // tracks the previous joke so we can avoid repeats
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
        if (jokes.size() > 1) {
            while (index == lastIndex)
                index = pick(generator);
        }
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
