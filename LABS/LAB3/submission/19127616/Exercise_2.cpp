#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Structure to hold a word and its definition
struct Word
{
    string name;
    string definition;
};

// Function to load the dictionary from a file
vector<Word> loadDictionary(const string &dictPath)
{
    ifstream dictFile(dictPath);
    vector<Word> dictionary;
    if (!dictFile)
    {
        // Error message if the dictionary file cannot be opened
        cerr << "Error opening dictionary file!" << endl;
        return dictionary;
    }

    string line;
    while (getline(dictFile, line))
    {
        size_t pos = line.find(":");
        if (pos != string::npos)
        {
            // Create a Word entry and add it to the dictionary
            Word entry;
            entry.name = line.substr(0, pos);
            entry.definition = line.substr(pos + 1);
            dictionary.push_back(entry);
        }
    }
    dictFile.close();
    return dictionary;
}

// Function to search for a word in the dictionary
string searchWord(const string &word, const vector<Word> &dictionary)
{
    for (const Word &entry : dictionary)
    {
        if (entry.name == word)
        {
            // Return the definition if the word is found
            return entry.definition;
        }
    }
    // Return "Not found" if the word is not in the dictionary
    return "Not found";
}

// Function to search for multiple words and write the results to an output file
void searchWords(const vector<string> &words, const vector<Word> &dictionary, const string &output_path)
{
    ofstream outputFile(output_path);
    if (!outputFile)
    {
        // Error message if the output file cannot be opened
        cerr << "Error opening output file!" << endl;
        return;
    }

    for (const string &word : words)
    {
        // Write each word and its definition to the output file
        outputFile << word << ": " << searchWord(word, dictionary) << endl;
    }
    outputFile.close();
}

// Main function
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        // Error message if the program is not used correctly
        cerr << "Usage: " << argv[0] << " word1 word2 ... output.txt" << endl;
        return 1;
    }

    vector<string> words;
    for (int i = 1; i < argc - 1; i++)
    {
        // Collect words from command line arguments
        words.push_back(argv[i]);
    }
    string output_path = argv[argc - 1];

    string dictionaryPath = "dictionary.txt"; // dictionary file path
    vector<Word> dictionary = loadDictionary(dictionaryPath);

    // Search for the words and write the results to the output file
    searchWords(words, dictionary, output_path);
    return 0;
}