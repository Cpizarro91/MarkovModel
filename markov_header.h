#ifndef MARKOV_HEADER
#define MARKOV_HEADER

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;


class NextWordElement
{
public:
    NextWordElement(string);//dont know if I actually need this
    string word;
    int count;
    NextWordElement* next;
};
class NextWordList
{
public:
    NextWordList();
    friend class KeyWordList;
private:
    void foundNextWord(string nextword);
    void add(string nextword);
    void printlist();
    NextWordElement* first1;
    NextWordElement* findWord(string);
    string getRandomWord();
};


class KeyWordElement
{
    friend class KeyWordList;
private:
    KeyWordElement(string);
    string word;
    KeyWordElement* next;
    NextWordList* nextwordlist;
};

class KeyWordList
{

public:
    KeyWordList();
    void addUnique(string keyword);//only true public function
    void foundNextWord(string keyword, string nextword);
    string getRandomNextWord(string keyword);
    string getRandomKeyword();
private:

    void add(string keyword);//keyword
    void printList();
    KeyWordElement* first;
    KeyWordElement* findWord(string word);//get an error about return type
    int findWordIndex(string word);


};


#endif // MARKOV_HEADER
