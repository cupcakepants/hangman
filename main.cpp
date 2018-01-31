//
//  hangman2.cpp
//
//
//  Created by Sai Sameer Pusapaty on 1/28/18.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <random>

using namespace std;


int lives = 6;
int wrongs = 0;
char guess;

void state(int n)
{
    if (n == 6)
    {
        cout << "___________\n";
        cout << "|      |\n";
        cout << "|      |\n";
        cout << "|\n";
        cout << "|\n";
        cout << "|\n";
        cout << "|__________\n";
        cout << "___________\n";
    }
    if (n == 5)
    {
        cout << "___________\n";
        cout << "|      |\n";
        cout << "|      |\n";
        cout << "|      O\n";
        cout << "|\n";
        cout << "|\n";
        cout << "|__________\n";
        cout << "___________\n";
    }
    if (n == 4)
    {
        cout << "___________\n";
        cout << "|      |\n";
        cout << "|      |\n";
        cout << "|      O\n";
        cout << "|      |\n";
        cout << "|\n";
        cout << "|__________\n";
        cout << "___________\n";
    }
    if (n == 3)
    {
        cout << "___________\n";
        cout << "|      |\n";
        cout << "|      |\n";
        cout << "|     \\O\n";
        cout << "|      |\n";
        cout << "|\n";
        cout << "|__________\n";
        cout << "___________\n";
    }
    if (n == 2)
    {
        cout << "___________\n";
        cout << "|      |\n";
        cout << "|      |\n";
        cout << "|     \\O/\n";
        cout << "|      |\n";
        cout << "|\n";
        cout << "|__________\n";
        cout << "___________\n";
    }
    if (n == 1)
    {
        cout << "___________\n";
        cout << "|      |\n";
        cout << "|      |\n";
        cout << "|     \\O/\n";
        cout << "|      |\n";
        cout << "|     /\n";
        cout << "|__________\n";
        cout << "___________\n";
    }
    if (n == 0)
    {
        cout << "___________\n";
        cout << "|      |\n";
        cout << "|      |\n";
        cout << "|     \\O/\n";
        cout << "|      |\n";
        cout << "|     / \\\n";
        cout << "|__________\n";
        cout << "___________\n";
    }
}

int update(char guess, string word, string &blank)
{
    int matches = 0;
    for (int i = 0; i< word.length(); i++)
    {
        // Did we already match this letter in a previous guess?
        if (guess == blank[i]){
            cout << "You have already guessed this letter\n";
            return 0;
        }
        // Is the guess in the secret word?
        if (guess == word[i])
        {
            blank[i] = guess;
            matches++;
        }
    }
    return matches;
}


string createBlank(string word){
    string blank = "";
    for(int i=0;i<word.length();i++){
        blank += "*";
    }
    return blank;
}

string lower(string my_string){
    for(unsigned int i = 0; i < my_string.length(); ++i) {
        my_string[i] = tolower(my_string[i]);
    }
    return my_string;
}

void game(string word){
    string blank = createBlank(word);
    
    cout << "Welcome!\n";
    
    while(lives > wrongs){
        state(lives-wrongs);
        cout << "\nYou have " << (lives - wrongs) << " lives left.\n";
        cout << blank << "\n\n";
        cout << "Pick a letter: ";
        cin >> guess;
        
        if (update(guess, word, blank) == 0){
            cout << "Bad guess \n";
            wrongs += 1;
        }
        else{
            cout << "Good guess \n";
        }
        if (word == blank){
            cout << word << "\n";
            cout << "Yippee, you win. \n";
            break;
        }
    }
    if (lives == wrongs){
        state(lives-wrongs);
        cout << "You lose \n";
        cout << "Answer: " << word << "\n";
    }
}

int main()
{
    cout << "HANGMAN\n\n";
    int choice;
    cout << "What would you like to do?\n";
    cout << "1. Play game\n";
    cout << "2. Add new word\n";
    cout << "3. Play with custom word\n";
    cin >> choice;
    
    if (choice == 1){
        int difficulty;
        cout << "What is the difficulty you prefer?\n";
        cout << "1. easy\n";
        cout << "2. medium\n";
        cout << "3. hard\n";
        cin >> difficulty;
        
        string file;
        string line;
        vector <string> words;
        string word;
        
        if (difficulty == 1){
            file = "easy.txt";
        }
        else if (difficulty == 2){
            file = "medium.txt";
        }
        else if (difficulty == 3){
            file = "hard.txt";
        }
        else{
            cout << "Not a valid answer. Please restart game you pleb.\n";
        }
        
        ifstream fin(file);
        if(fin.is_open()){
            while(getline(fin,line)){
                line = lower(line);
                words.push_back(line);
            }
        }
        else{
            cout << "Error";
        }
        
        mt19937 rng (std::random_device{}());
        uniform_int_distribution<> dist (0, words.size());
        int num = dist(rng);
        word = words[num];
        
        game(word);
    }
    else if (choice == 2) {
        int list_choice;
        string word_choice;
        cout << "What list would you like to add to?\n";
        cout << "1. easy\n";
        cout << "2. medium\n";
        cout << "3. hard\n";
        cin >> list_choice;
        cout << "What is your word?\n";
        cin >> word_choice;
        
        string file;
        string line;
        string empty = "";
        vector <string> words;
        
        if (list_choice == 1){
            file = "easy.txt";
        }
        else if (list_choice == 2){
            file = "medium.txt";
        }
        else if (list_choice == 3){
            file = "hard.txt";
        }
        else{
            cout << "Not a valid answer. Please restart game you pleb.\n";
        }
        
        ifstream fin(file);
        if(fin.is_open()){
            while(getline(fin,line)){
                line = lower(line);
                words.push_back(line);
            }
        }
        else{
            cout << "Error";
        }
        
        words.push_back(word_choice);
        
        for(int i=0;i<words.size();i++){
            empty += words[i];
            empty += "\n";
        }
        
        ofstream outputFile(file);
        outputFile << empty;
        
    }
    else if (choice == 3){
        string custom;
        cout << "What word would you like to play with?\n";
        cin >> custom;
        custom = lower(custom);
        game(custom);
    }
    return 0;
}

