# code-lab-A1-part2
Alexa tell me a joke

# Random Joke Teller

A C++ console program that loads jokes from a text file and tells a random one on request, Alexa-style — the user types a wake phrase, the joke is revealed in two parts (question, then punchline) with a pause in between.

Created as part of the Programming Skills Portfolio assessment for CodeLab II (Bath Spa University).

## Features

- Loads jokes from an external text file (`randomJokes.txt`), filtering out any invalid/malformed lines
- Responds to the wake phrase "Alexa, tell me a joke" (case-insensitive)
- Picks a random joke using `<random>` (`mt19937` + `uniform_int_distribution`) rather than `rand()`
- Splits each joke into question and punchline, revealing the punchline only after the user presses Enter
- Lets the user request as many jokes as they like, or type "quit" to exit
- Gracefully handles missing input files and empty/invalid command entries

## How It Works

| Function | Purpose |
|---|---|
| `loadJokes()` | Opens `randomJokes.txt`, reads it line by line, and stores only lines containing a `?` as valid jokes in a `vector<string>` |
| `toLowerCase(string)` | Converts a string to lowercase using `transform` and a lambda, so user input is matched case-insensitively |

`main()` loads the jokes, then loops: it waits for the wake phrase, picks a random joke, splits it at the `?` to separate the question from the punchline, and reveals the punchline after the user presses Enter. The user can repeat this as many times as they like.

## Joke File Format

Each joke is stored on its own line, with the question and punchline separated by a single `?`:

```
Why did the chicken cross the road?To get to the other side.
What happens if you boil a clown?You get a laughing stock.
```

## Example Output

```
Type 'Alexa, tell me a joke' or 'quit': Alexa, tell me a joke

Why did the chicken cross the road?
Press Enter to reveal the punchline...
To get to the other side.

Would you like another joke? (y/n): n
Goodbye!
```

## Build & Run

```bash
g++ -o joke_teller main.cpp
./joke_teller
```

Ensure `randomJokes.txt` is in the same directory as the executable.

## Author

Tara ([TaraaaYah](https://github.com/TaraaaYah))
