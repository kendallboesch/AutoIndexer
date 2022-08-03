#ifndef INC_21F_PA02_AUTOINDEXER_H
#define INC_21F_PA02_AUTOINDEXER_H
#include "DSString.h"
#include "DSVector.h"
#include <iostream>
#include <fstream>
#include <map>

    //TODO: COMMENTS

using namespace std;

class Autoindexer
{
public:
    Autoindexer();
    void readInKeyWords(char*[]);
    void sortKeys();
    void runAutoIndex(char*[]);
    void beginIndexing();
    void wordParse(DSVector<DSString>&, DSString&);
    bool isPageNum(DSString);
    bool endOfBook(DSString);
    int addPage(DSString);
    void updatePageKeys(int, DSVector<DSString>&);
    void fillKeyLocations();
    void printPageKeys();
    void makeKeyVec();
    void printKeyPages();
    void generateIndex();



private:
    DSVector<DSString> keyWords;
    map<int, DSVector<DSString>> pageKeys;
    map<DSString, DSVector<int>> keyLocations;


};

Autoindexer::Autoindexer()
{

}
/****************
 *  READ IN KEY WORDS
 *
 *  OPENS TERMS FILE & READS IN TERMS TO BE INDEXED
 *  ADDS EACH TERM TO THE KEYWORD VECTOR
 * @param argv
 */
void Autoindexer::readInKeyWords(char* argv[])
{
    ifstream inFS;
    inFS.open(argv[2]); //OPEN KEY WORDS FILE


    if(inFS.is_open())  // CHECK IF OPEN
    {
        cout << "FILE OPENED" << endl;
    }
    else
    {
        cout << "ERROR OPENING FILE" << endl;
    }
    char keyword [100];
    while(!inFS.eof())
    {


        inFS.getline(keyword, 100); // READ IN KEY WORDS
        DSString key(keyword);
        if(key.getLength() > 1)
        {
            keyWords.push_back(key);    // ADD KEYWORD TO VECTOR OF KEYWORDS
            cout << keyword << endl;
        }

    }
    inFS.close();       // CLOSE TERMS.TXT
    //alphabetizeKeywords();
}
/**********
 *
 * WORDPARSE
 *
 * IDENTIFIES KEYWORDS IN DATA PASSED IN
 * & ADDS THEM TO VECTOR
 *
 *
 * @param words
 * @param data
 */
void Autoindexer::wordParse(DSVector<DSString>& words, DSString &data)
{
    DSString temp(data); // MUTABLE COPY OF DATA
    temp.makeLower();
    if(temp.getLength() > 1)
    {


        for (int i = 0; i < keyWords.getSize(); i++) // ITERATE THROUGH THE KEY WORDS
        {
            DSString key = keyWords[i];  // MUTABLE COPY OF KEYWORDS
            key.makeLower(); // MAKE LOWERCASE
            if (temp.containsz(key))   // IF THE LINE CONTAINS THE KEY WORD AT I
            {
                words.push_back(keyWords[i]); // ADD THE KEY WORD TO THE VECTOR
                cout << "pushed: " << keyWords[i] << endl;
            }

        }
    }
}
/**********
 *      ISPAGENUM
 *
 *      RETURNS TRUE IF LINE READ IN
 *      IS A PAGE NUMBER AND NOT CONTENT
 * @param arg
 * @return
 */
bool Autoindexer::isPageNum( DSString arg)
{

    if(arg.substring(0,4) == "<-1>")        // CHECK TO SEE IF END OF FILE
    {
        // is end of file
        return false;
    }
    else if(arg[0] == '<')
    {
        return true;
    }
    return false;
}
/**********
 *      END OF BOOK
 *
 *      RETURNS TRUE IF THE LINE PASSED
 *      IN IS THE END OF THE BOOK
 * @param arg
 * @return
 */
bool Autoindexer::endOfBook(DSString arg)
{
    if(arg.contains("<-1>"))
    {
        return true;
    }
    return false;
}
/**********
 *
 *      ADD PAGE
 *
 *      RETURNS THE PAGE NUMBER AS
 *      AN INT THAT WAS PASSED IN
 *      AS A DSSTRING
 *
 * @param pNum
 * @return
 */
int Autoindexer::addPage(DSString pNum)
{
    int endIndex = pNum.indexOf('>') - 1;
    DSString num = pNum.substring(1, endIndex);
    cout << "NUM: " << num << endl;
    int pageNum = num.toInt();
    cout << "page Num: " << pageNum << endl;
    return pageNum;
}
/***********
 *
 *      RUN AUTOINDEX
 *
 *      OPENS THE BOOK FILE AND READS IN LINES; ADDS
 *      PAGES TO MAP IF READS IN NEW PAGE NUMBER;
 *      SEARCHES LINE FOR KEYWORDS IF CONTENT;
 *      ENDS RUN IF END OF BOOK
 *
 * @param argv
 */

void Autoindexer::runAutoIndex(char* argv[])
{
    ifstream inFS;
    inFS.open(argv[1]);
    if(!inFS.is_open())
    {
        cout << "ERROR OPENING TEST BOOK FILE" << endl;
    }
    else if(inFS.is_open())
    {
        DSString lineIn;
        DSVector<DSString> keysFound;
        int currentPage = -1;
        char readIn[400];
        //READ IN FIRST LINE
        inFS.getline(readIn, 400);
        lineIn = readIn;

        if(endOfBook(lineIn))    // IF FIRST LINE IS END OF BOOK
        {
            ofstream out;
            out.open("output.txt");
            out << "No new terms to input" << endl;
        }
        else        // FIRST LINE WILL BE A PAGE NUMBER
        {
            currentPage = addPage(lineIn);   // UPDATE CURRENT PAGE


            bool newPage = false;
            bool bookEnd = false;
            while (!bookEnd)    // WHILE NOT END OF BOOK
            {

                inFS.getline(readIn, 400);
                lineIn = readIn;
                newPage = isPageNum(lineIn);
                bookEnd = endOfBook(lineIn);

                while(!newPage && !bookEnd)
                {
                    if(lineIn.getLength() > 1)
                    {
                        wordParse(keysFound, lineIn);       // CHECK FOR KEYWORDS IN LINE READ
                    }


                    inFS.getline(readIn, 400);
                    lineIn = readIn;
                    newPage = isPageNum(lineIn);        // CHECK IF IS A PAGE NUMBER
                    bookEnd = endOfBook(lineIn);        // CHECK IF IS END OF BOOK

                }
                updatePageKeys(currentPage, keysFound);     // UPDATE MAP WITH PAGE NUMBER AS KEY,
                                                                        // DSVECTOR OF KEYWORDS FOUND ON CURRENT PAGE
                                                                        // AS MAP NODE VALUE

                currentPage = addPage(lineIn);          // UPDATE CURRENT PAGE
                keysFound.empty();                      // EMPTY VECTOR OF WORDS READ
            }
        }
    }
}
/**************
 *      UPDATE PAGE KEYS
 *
 *
 *
 * @param page
 * @param words
 **************/
void Autoindexer::updatePageKeys(int page , DSVector<DSString> &words)
{
    if(pageKeys.find(page) == pageKeys.end())       // CHECK IF PAGE NODE HAS ALREADY BEEN MADE
    {
        int p = page;
        DSVector<DSString> iWords;     // CREATE NEW DSVECTOR
        for(int i = 0; i < words.getSize(); i++)
        {
            DSString s(words[i]);      // CREATE NEW DSTRING
            s.makeLower();      // MAKE LOWERCASE
            iWords.push_back(s);    // PUSH TO NEW VECTOR
        }
        pair<int, DSVector<DSString>> node;     // CREATE NEW NODE WITH PAGE NUMBR & VECTOR OF KEYWORDS FOUND
        node = make_pair(p, iWords);
        pageKeys.insert(node);          // INSERT PAIR INTO MAP
    }
    else        // IF PAGE NUMBER IS ALREADY A KEY ON MAP
    {
       auto itr = pageKeys.find(page);
       for(int i = 0; i < words.getSize(); i++) // ITERATE THROUGH VECTOER PASSED
       {
          DSString w(words[i]);         // MAKE NEW DSTRING OF EACH ELEMENT IN VECTOR PASSED
          w.makeLower();        // MAKE LOWER
           itr->second.push_back(w);        // PUSH BACK NEW FOUND KEYS ON EXISTING VECTOR
       }
    }

}
/***************
 *      BEGIN INDEXING
 *
 *      ITERATE THROUGH MAP OF KEYWORDS ADDING
 *      TO THE DSVECTOR OF INTS EACH PAGE IT
 *      IS FOUND ON.
 *
 *
 */
void Autoindexer::beginIndexing()
{
    makeKeyVec();



   for(auto itr = keyLocations.begin(); itr != keyLocations.end(); itr++)
   {
       DSString currentKey = itr->first;    // THE KEY BEGING SEARCHED FOR;
       currentKey.makeLower();
       cout << "CURRENY KEY: " << currentKey << endl;
       for (auto inItr = pageKeys.begin(); inItr != pageKeys.end(); inItr++)    // ITERATING THROUGH MAP W PAGE NUM AS KEY
       {
           int currentPage = inItr->first;
          // cout << "SEARCHING CONTENTS OF PAGE " << currentPage << endl;

           int indexOfKeyword = inItr->second.search(currentKey);       // SEE IF WORD IS ON THIS PAGE;
                                                                        // IF IT IS, SAVE INDEX

           if(indexOfKeyword != -1)     // IF IT EXISTS ON MAP
           {
               itr->second.push_back(currentPage);  // PUSH BACK NEW PAGE  NUMBER ONTO EXISTING VECTOR
               cout << "KEY FOUND AT INDEEX " << indexOfKeyword <<  " PAGE: " << currentPage << endl;
               cout << inItr->second[indexOfKeyword] << endl;
           }
       }
   }
}
/*********
 *      MAKE KEY VEC
 *
 *      ITERATE THROUGH KEYWORD VECTOR
 *      AND CREATE NEW NODE IN INDEX MAP
 *
 *
 */
void Autoindexer::makeKeyVec()
{
    for(int i = 0; i < keyWords.getSize(); i++)
    {
        DSString key(keyWords[i]);
        key.makeUpper();
        DSVector<int> found;
        pair<DSString, DSVector<int>> mapNode;
        mapNode = make_pair(key, found);
        keyLocations.insert(mapNode);
    }


}
/***************
 *      PRINT PAGE KEYS
 *
 *      PRINT PAGE AND VECTOR OF KEYWORDS
 *      FOUND ON THAT PAGE
 *
 */
void Autoindexer::printPageKeys()
{
    for(auto itr = pageKeys.begin(); itr != pageKeys.end(); itr++)
    {
        cout << "PAGE: " << itr->first << endl;
        for(int i = 0; i < itr->second.getSize(); i++)
        {
            cout << itr->second[i] << endl;
        }
        cout << endl;
    }
}
/*******
 * PRINT KEY PAGES
 *
 * PRINT KEYWORD AND VECTOR OF
 * INTS REPRESENTING PAGE NUMBERS
 * THE KEYWORD IS FOUND ON
 *
 */
void Autoindexer::printKeyPages() {
    for (auto itr = keyLocations.begin(); itr != keyLocations.end(); itr++)
    {
        cout << "KEY " << itr->first << endl;
        for (int i = 0; i < itr->second.getSize(); i++)
        {
            cout << itr->second[i] << endl;
        }
        cout << endl;
    }
}
/*******
 *
 *      GENERATE INDEX
 *
 *      PRINTS OUT INDEX MAP IN ALPHABETICAL
 *      ORDER & GENERATES HEADERS FOR EACH
 *      NEW LETTER
 *
 */
void Autoindexer::generateIndex()
{
    ofstream out;

    out.open("output.txt");     // OPEN OUTPUT FILE

    if(!out.is_open())
    {
        cout << "FAILED TO OPEN OUTPUT FILE" << endl;
    }
    else
    {
        auto itr = keyLocations.begin();    // ITERATE THROUGH THE MAP
        char prev = itr->first[0];
        char label = prev;          // GET FIRST CHAR OF FIRST WORD IN ALPHABETIZED MAP
        out << '[' << prev << ']' << endl;

        for(auto itr = keyLocations.begin(); itr != keyLocations.end(); itr++)
        {
            DSString keyword = itr->first;
            label = keyword[0];

            if(label != prev)
            {
                out << '[' << label << ']' << endl;
                prev = label;
            }
            out << itr->first << ": ";

            for(int j = 0; j < itr->second.getSize(); j++)
            {
                out << itr->second[j];
                if(j != itr->second.getSize() - 1)
                {
                    out << ", ";
                }
            }

            out << endl;



        }
    }
}



#endif //INC_21F_PA02_AUTOINDEXER_H