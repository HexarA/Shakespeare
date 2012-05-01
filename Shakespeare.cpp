// Shakespeare.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

inline string strlower(string s);

int _tmain(int argc, _TCHAR* argv[])
{
    // Open input file
    multimap<std::string, std::string> wordmap;
    srand(time(NULL));

    ifstream file;

    if (argc > 1)
    {
        file.open(argv[1]);
    }
    else
    {
        file.open("shakespeare.txt");
    }

    if (!file.is_open())
        return 0;

    std::string last = "";

    // Read from file
    while (!file.eof())
    {
        std::string s;

        file >> s;

        s = strlower(s);

        // Look for a period
        if (s.length() > 1 && s[s.length() - 1] == '.')
        {
            s = s.substr(0, s.length()-1);
            file.putback('.');
        }
        // Look for an exclamation
        else if (s.length() > 1 && s[s.length() - 1] == '!')
        {
            s = s.substr(0, s.length()-1);
            file.putback('!');
        }
        // Look for a question-mark
        else if (s.length() > 1 && s[s.length() - 1] == '?')
        {
            s = s.substr(0, s.length()-1);
            file.putback('?');
        }
        // Look for a comma
        else if (s.length() > 1 && s[s.length() - 1] == ',')
        {
            s = s.substr(0, s.length()-1);
            file.putback(',');
        }

        // Add the data to the map
        if (last != "" && last != "." && last != "!" && last != "?")
        {
            wordmap.insert(make_pair(last, s));
        }
        
        last = s;
    }

    // Close file
    file.close();

    // Now do the fun part!
    string word;

    while (word != "quit" && word != "QUIT")
    {
        cout << endl << "Type a word (\"quit\" to exit): ";
        cin >> word;

        word[0] = toupper(word[0]);
        cout << word;
        word[0] = tolower(word[0]);
        int wordcount = 0;

        if (word == "quit")
            break;

        while (true)
        {
            // Check to see if the word is in the multimap
            if (wordmap.find(word) != wordmap.end())
            {
                // Get first mapped value
                multimap<string, string>::iterator lb = wordmap.lower_bound(word);

                // Count how many there are
                long count = wordmap.count(word);

                // Select one of them
                long index = rand() % count;

                // Advance map iterator
                for (long i = 0; i < index; i++)
                {
                    lb++;
                }

                // Check for characters that would end a sentence
                if (lb->second == "." || lb->second == "!" || lb->second == "?")
                {
                    // If sentence is too short, select another word
                    if (wordcount < 3 && count > 1)
                    {
                        // Update the word count in case the only endings to this
                        // word are ! or . or ?
                        wordcount++;
                        continue;
                    }

                    // Print word
                    cout << lb->second << endl;
                    break;
                }
                else if (lb->second == ",")
                {
                    // Print commas
                    cout << lb->second;
                }
                else
                {
                    // Print the word with a space
                    cout << " " << lb->second;
                    wordcount++;
                }

                // Update the current word
                word = lb->second;
            }
            else
            {
                // Not found; end the sentence
                cout << ".\n";
                break;
            }
        }
    }

	return 0;
}

inline string strlower(string s)
{
    for (unsigned int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }

    return s;
}

