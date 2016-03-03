#include "markov_header.h"

NextWordElement::NextWordElement(string initial1)
{
    word=initial1; //word in nextwordelement
    next=NULL;      //make it a last element by default
}


NextWordList::NextWordList()
{
    first1 = NULL; //start of list will be NULL
}

string NextWordList::getRandomWord()
{
    int totalcount = 0;
    int choice;
    int runningcount = 0;
    NextWordElement* current = first1;
    while(current!=NULL) //go through list
    {
        totalcount++; //count each element
        current=current->next; //next element
    }
    choice = rand() % totalcount; //random number between 0 and totalcount or count of the number of nextwordelements
    NextWordElement* current2 = first1;
    while(current2!=NULL) //go though list again
    {
        runningcount++; //count each element
        if(runningcount>=choice)//if this count is equal to the random number choice
        {
            return current2->word;//return the word of the nextwordelement
        }
        current2=current2->next;//next element

    }

}

NextWordElement* NextWordList::findWord(string word)
{
    int index=0;
    NextWordElement* current = first1;
    //I need it to point to the previous word, go through the list
    while(current!=NULL) //go through nextwordelement list
    {
        if(current->word == word)//if nextwordelement's word is equal to word, or if we found the word
            return current;//reutrn the element
            //return index;
        current=current->next;//next element
        index++;//increment index count
    }
    return NULL;//if we didn't find the word return null
}


void NextWordList::foundNextWord(string nextword)
{
    NextWordElement* word = findWord(nextword);//call findword to see if we can find the word in nextwordlist
    if(word==NULL) //if we didn't find repeat of word
    {
        add(nextword);//add to the list
    }
    else
    {
        word->count++;//if we did find the word again, increment count by 1
    }


}

void NextWordList::add(string nextword)
{
    NextWordElement* newelement1 = new NextWordElement(nextword);//previously using word,creates new element, taking value and putting a linked list element around it so we can plug it in
    newelement1 -> count = 1;
    newelement1->next=first1;//copying the previous element into first spot, make it's next element the beginning of my exisiting list
    first1 = newelement1;
}

void NextWordList::printlist()
{
    NextWordElement* Value = first1;//start with the first elements (first of every element, the only part we know)

    while(Value!=NULL)//while we haven't reached the end of the list
    {
        cout << Value->word << ": " << Value-> count << endl;//print the word and the number of times it's appeared
        Value=Value->next;//next element
    }

}


KeyWordElement::KeyWordElement(string initial)
{
    word=initial;
    next=NULL;      //make it a last element by default
    nextwordlist = new NextWordList(); //create a nextwordlist for each keyword because every keyword will have a nextword to it
}


KeyWordList::KeyWordList()
{
    first=NULL; //initially first will hold NULL
}

string KeyWordList::getRandomNextWord(string keyword)
{
    KeyWordElement* current = first; //start at first element of list
    while(current!=NULL) //go through keywordlist
    {
        if(current->word==keyword) //if keywordelement's word matches the keyword
        {
            return current->nextwordlist->getRandomWord();//send the nextwordlist of that element to getRandomWord function
        }
        current = current->next; //next element
    }
}

string KeyWordList::getRandomKeyword()
{
    int keywordelementcount = 0;
    KeyWordElement* current = first;
    while(current!=NULL)//go through keywordlist
    {
        keywordelementcount++;//count number of elements in keywordlist
        current=current->next;//next element
    }
    int choice=0;
    choice = rand()%keywordelementcount;//get random number between 0 and number of keywordelements

    KeyWordElement* current2 = first;
    int count=0;
    while(current2!=NULL) //go through keywordlist again
    {
        count++;//count number of elements again
        if(count>=choice)//if our count is greater or equal to our random number
        {
            return current2->word; //return that keywordelement's word
        }
        current2=current2->next;//next element

    }

}


void KeyWordList::addUnique(string keyword)//this is just keyword
{

    if (findWord(keyword)==NULL)//if we didn't find the word in the keywordlist already
    {
        add(keyword);//add it to the list using add function
    }
}

int KeyWordList::findWordIndex(string word)
{
    int index=0;
    KeyWordElement* current = first;
    //I need it to point to the previous word, go through the list
    while(current!=NULL)//go through keywordlist
    {
        if(current->word == word)//if current keywordelement's word is equal to word
            return index; //return the index in where it's at on our list
        current=current->next;//next element
        index++;//increment index count
    }
    return -1;//if we didn't find the index return -1
   //safe number to use for not found because it can't possibly be an index
}

KeyWordElement* KeyWordList::findWord(string word) //was an int I changed to string KeyWordList
{

    KeyWordElement* current = first;
    //I need it to point to the previous word, go through the list
    while(current!=NULL)
    {
        if(current->word == word)
            return current;
            //return index;
        current=current->next;

    }
    return NULL;
}

void KeyWordList::add(string keyword)
{
    //encapsulate value as a Lego
    KeyWordElement* newelement = new KeyWordElement(keyword);//previously using word,creates new element, taking value and putting a linked list element around it so we can plug it in
    newelement->next=first;//copying the previous element into first spot, make it's next element the beginning of my exisiting list
    first = newelement;//redirecting first so the first element is the new element
}


void KeyWordList::printList()
{
    KeyWordElement* currentValue = first;//start with the first elements (first of every element, the only part we know)

    while(currentValue!=NULL)//while we haven't reached the end of the list
    {
        cout << "Key Word: " << currentValue->word << endl;//print the value
        currentValue->nextwordlist->printlist();
        currentValue=currentValue->next;//the next element
    }
}

void KeyWordList::foundNextWord(string keyword, string nextword)
{
   addUnique(keyword);
   KeyWordElement* word = findWord(keyword);
   word->nextwordlist->foundNextWord(nextword);

}

string preprocess(string word)
{
    //I am getting just a w in output need to figure out what it is also getting just an m
    string newword;
    int i;
    for(i=0;i<word.length();i++)//go through the word character by character
    {
        if('a'<=word[i] && word[i] <='z')//if letter is lowercase copy it to newword
        {
            newword=word;//copy

        }
        if ('A' <= word[i] && word[i] <= 'Z')//if letter is uppercase change to lowercase and copy
        {
            word[i]=char(((int)word[i]+32));//robelle.com for the ascii
            //take ascii of capital letter add 32 which makes it its lowercase letter
            newword=word;
        }
        if('!'<= word[i] && word[i] <= '@') //if character is between ! and @ on ascii table delete it
        {
            //cplusplus.com for use of erase and begin
            word.erase(word.begin()+i);//if I set word[i] to NULL, find word will still pass the word, .erase works though

            if('A' <= word[i] && word[i] <= 'Z')
            {
                word[i]=char(((int)word[i]+32));
            }
            if('!'<= word[i] && word[i] <= '@')
            {
                word.erase(word.begin()+i);
                if('!'<= word[i] && word[i] <= '@')
                {
                    word.erase(word.begin()+i);
                    if('!'<= word[i] && word[i] <= '@')
                    {
                        word.erase(word.begin()+i);
                    }
                }
            }

            newword=word;
        }
        if('[' <= word[i] && word[i] <= '_')//if character is between [ and _ on ascii table delete it
        {
            word.erase(word.begin()+i);
            newword=word;
        }
    }
    return newword;



}


int main()
{
    srand(time(0));
    ifstream book("11.txt");
        string word,word1,word2;
        string keyword;
        string startword;
        string nextword;
        KeyWordList* keywordlist = new KeyWordList();

        book >> word1;
        book >> word2;

        while(!book.eof())
        {
            keyword = word1 + " " + word2;
            book >> nextword;
            nextword = preprocess(nextword);
            keywordlist->foundNextWord(keyword,nextword);
            word1=word2;
            word2=nextword;
        }

        int i;
        for(i=0;i<100;i++)
        {
            startword = keywordlist->getRandomKeyword(); //get random pair of startwords
            startword.substr(startword.find(" ")+1,startword.size());
            nextword = keywordlist->getRandomNextWord(startword);//find nextword from startword pair
            startword = startword + " " + nextword; //add startword pair with next word
            cout << startword << " "; //print them out

        }


}

