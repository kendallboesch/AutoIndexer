#include "DSString.h"

using namespace std;

/**********
 *                                  DEFAULT CONSTRUCTOR
 **********/
DSString::DSString()
{
    cstr = nullptr;
}
/**********
 *                                  SIZE CONSTRUCTOR
 * @param n
 **********/
DSString::DSString(int n)
{
    cstr = new char[n + 1];
//    cstr[strlen(cstr)] = '\0';
    cstr[n] = '\0';
}
/**********
*                                   ARGUMENT CONSTRUCTOR
**********/
DSString::DSString(const char* cIn)
{

    this->cstr = new char[strlen(cIn) + 1];
   // strcpy(cstr, cIn);
    int i;
    for( i = 0; i < strlen(cIn); i++)
    {
        this->cstr[i] = cIn[i];
    }
    cstr[i] = '\0';
    //this->cstr[strlen(cIn) + 1] = '\0';
//    if(cstr == cIn)
//    {
//        strcpy(cstr, cIn);
//    }
//    else
//    {
//
//        if (cstr != nullptr || cstr != NULL || cstr != "")
//        {
//           // delete [] cstr;
//        }
//
//        cstr = new char[strlen(cIn)];
//        strcpy(cstr, cIn);
//    }
}
/**********
*                                   COPY CONSTRUCTOR
**********/
DSString::DSString(const DSString& sIn)
{
    cstr = new char[strlen(sIn.cstr) + 1];
    strcpy(cstr, sIn.cstr);
  //  cstr[strlen(sIn.cstr)] = '\0';
}
/**********
*                                  DECONSTRUCTOR
**********/
DSString::~DSString()
{

    if(cstr != nullptr)
    {
        delete [] cstr;
    }

}
/**********
 *                                  GET LENGTH
 * @return int
 **********/
int DSString::getLength()
{
    return strlen(cstr);
}
/**********
 *                                  OVERLOADED GREATER THAN OPERATOR >
 * @param arg
 * @return
 **********/
bool DSString::operator> (const char* arg) const
{
    return strcmp(cstr, arg) > 0;
}
/*********
 *
 * @param arg
 * @return
 */
bool DSString::operator<(const char* arg) const
{
    return strcmp(cstr, arg) < 0;
}
/******************
 *
 * @param arg
 * @return
 */
bool DSString::operator>(const DSString& arg) const
{
    return strcmp(cstr,arg.cstr) > 0;
}
bool DSString::operator<(const DSString& arg) const
{
    return strcmp(cstr, arg.cstr) < 0;
}
/**********
 *                                  OVERLOADED COMPARISON OPERATOR W CHAR* PARAM
 * @param arg
 * @return
 */
bool DSString::operator== (const char* arg) const
{

    return strcmp(this->cstr, arg) == 0;
}
/**********
 *                              OVERLOADED COMPARISON OPERATOR W DSSTRING PARAM
 * @param arg
 * @return
 *********/
bool DSString::operator== (const DSString& arg) const
{
    return strcmp(this->cstr, arg.cstr) == 0;
}
/**********
 *                          OVERLOADED ASSIGNMENT OPERATOR W CHAR* PARAM
 * @param arg
 * @return
 */
DSString &DSString::operator= (const char* arg)
{
    if (cstr != nullptr)
    {
        delete [] cstr;
    }
    cstr = new char[strlen(arg) + 1];
    strcpy(cstr, arg);
    //cstr[strlen(arg) + 1] = '\0';
    return *this;
}
/**********
 *                         OVERLOADED ASSIGNMENT OPERATOR W DSSTRING& PARAM
 * @param arg
 * @return
 */
DSString &DSString::operator= (const DSString& arg)
{
    if (cstr != nullptr)
    {
        delete [] cstr;
    }

    if(arg.cstr == "")
    {
        cstr = "";
    }
    else
    {


        cstr = new char[strlen(arg.cstr) + 1];
        strcpy(cstr, arg.cstr);
        //cstr[strlen(arg.cstr) + 1] = '\0';
    }
    return *this;
}
/**********
 *                      OVERLOADED INDEXING OPERATOR
 * @param n
 * @return
 **********/
char& DSString::operator[] (const int n) const
{
    return this->cstr[n];
}
/**********
 *                      OVERLOADED CONCATENATION OPERATOR
 * @param arg
 * @return
 */
DSString DSString::operator+ (const DSString& arg)
{
    int length = strlen(this->cstr) + strlen(arg.cstr);
    char* temp = new char[length + 1];
    strcpy(temp, this->cstr);
    strcat(temp, arg.cstr);
    DSString dest(temp);
    delete [] temp;
    return dest;
}
/**********
 *                              SUBSTRING
 * @param start
 * @param numChars
 * @return
 */
DSString DSString::substring(int start, int numChars)
{
    // start is the index that the substring will start on
    // numChars is the total number of chars INCLUDING start that will be copied
    //into a new substring
    if(cstr == nullptr)
    {
        return nullptr;
    }
    char* temp = new char[numChars + 1];
    int i = 0;
    // edit: have to make sure that you do not overwrite the original string here
    while(i < numChars && i+start < strlen(cstr))
    {
        temp[i] = cstr[i + start];
        i++;
    }
    temp[i] = '\0';
    DSString s(temp);

    delete [] temp;

    return s;
}
/**********
 *                              SUBSTRING FROM N TO END
 * @param s
 * @return
 */
DSString DSString::substring(int s)
{
    int newLen = strlen(cstr) - s;
    char* temp = new char[newLen + 1];

    for(int i = 0; i < newLen; i++)
    {
        temp[i] = cstr[s + i];
    }
    temp[newLen] = '\0';
    DSString sub(temp);
    delete [] temp;
    return sub;
}
/**********
 *                      C_STR
 * @return
 */
char* DSString::c_str()
{
    return cstr;
}
/**********
 *                          OVERLOADED STREAM INSERTION OPERATOR
 * @param out
 * @param c
 * @return
 */
ostream& operator<< (ostream &out, const DSString& c)
{
    out << c.cstr;
    return out;
}
/**********
 *                          INDEX OF
 *
 *                          RETURNS INDEX OF CHAR PASSED IN
 * @param c
 * @return
 */
int DSString::indexOf(char c)
{
    if(cstr != nullptr)
    {
        for(int i = 0; i < strlen(cstr); i++)
        {
            if(cstr[i] == c)
            {
                return i;
            }
        }
        return -1;
    }
    return -1;
}
/*********
 *
 *      CONSTAINS
 *
 *      RETURNS TRUE IF THIS CONTAINS
 *      KEY PARAMETER PASSED IN
 *
 * @param key
 * @return
 */
bool DSString::contains(char* key)
{
    DSString tmp(cstr); // CREATE A MUTABLE COPY OF THE CURRENT CSTR
    int length = 0;
    char c = key[0];    // HOLDS CHAR AT 0 FOR
    int keySize = strlen(key);  //LENGTH OF THE WORD BEING SEARCHED
    int index;
    //char* testCstr = new char[keySize + 1];
    DSString test(keySize + 1); // DSSTRING WILL BE USED TO COMPARE
    bool searching = true;
    while(searching)
    {
        length = strlen(tmp.cstr); // LENGTH OF THE CURRENT STRING
        index = tmp.indexOf(c); // FIND INDEX OF C (FIRST CHAR OF KEY) IN THE
        // STRING BEING SEARCHED

        if(keySize == length)   // IF THE KEY AND THE STRING BEING SEARCHED
        {                           // ARE OF EQUAL LENGTH
            // test(tmp);
            if(tmp == key)  // CHECK IF THE SEARCH STRING & THE KEY
            {                   // ARE THEY SAME, IF THEY ARE
                return true;    // FUNCTION RETURNS TRUE
            }
            else        // IF THE STRING BEING SEACRHED & THE KEY ARE NOT THE SMAE
            {               // RETURN FALSE AS TEHERE ARE NO OTHER CHARS TO CHECK
                return false;
            }
        }
        else if(index == -1 || keySize > length) // IF THE INDEX IS NOT FOUND, OR THE
        {                                   // KEY BEING SEARCHGED FOR IS LONGER THAN THE
            // STRING BEING SEARCHED
            //  std::cout << "String not found: " << key << std::endl;
            return false;       // RETURN FALSE, THE STRING DOES NOT CONTAIN THE KEY
        }
        else
        {
            tmp = tmp.substring(index);
            if (test.cstr != nullptr)
            {
                test.cstr = nullptr;
            }
            test = tmp.substring(0, keySize);
           // test[keySize + 1] = '\0';

            if(test == key)
            {
                std::cout << "FOUND: " << key << std::endl;
                return true;
                // searching = false;
            }
            else if (tmp.substring(1).indexOf(c) == -1 || tmp.substring(1).getLength() > keySize)
            {
                return false;
            }
            else
            {
                tmp = tmp.substring(1);
            }

        }
    }
}
/**********
 * BEGIN
 *
 * RETURNS FIRST CHAR IN DSSTING
 *
 * @return
 */
char DSString::begin()
{
    return cstr[0];
}
/****
 *  END
 *
 *  RETURNS LAST CHAR OF STRING
 *
 * @return
 */
char DSString::end()
{
    return cstr[strlen(cstr) - 1];
}
/*********
 *
 * OVERLOADED CONCATENATION OPERATOR
 *
 * WITH CHAR PARAMETER
 *
 *
 * @param c
 * @return
 */
DSString DSString::operator+ (const char c)
{
    int length = strlen(cstr) + 2;
    char* temp = new char[length];
    strcpy(temp, cstr);
    temp[length - 1] = c;
    temp[length] = '\0';

    DSString dest(temp);
    delete [] temp;
    return dest;
}
/********
 *      TO LOWER
 *
 *      CHANGE EACH CHAR IN DSSTRING TO
 *      LOWWER CASE
 *
 *
 */
void DSString::makeLower()
{
    // vector<char> upper;

    for(int i = 0; i < strlen(cstr); i++)
    {
        cstr[i] = tolower(cstr[i]);
    }
}
/*****
 *      MAKE UPPER
 *
 *      CHANGE EACH CHAR IN DSSTRING
 *      TO UPPERCASE
 *
 */
void DSString::makeUpper()
{
    for(int i = 0; i < strlen(cstr); i++)
    {
        cstr[i] = toupper(cstr[i]);
    }
}
/*********
 *      TOINT
 *
 * TURNS DSTRING TO INT
 *
 * @return
 */
int DSString::toInt()
{
    char* temp = new char[10];
    for(int i = 0; i < this->getLength() ; i++)
    {
        temp[i] = cstr[i];
    }
    int asInt = atoi(temp);
    return asInt;
}

/*****
 *          REMOVE FACES
 *
 *          REMOVES SPACES FROM DSTRING
 *
 */
void DSString::removeSpaces()
{
    int size = strlen(cstr);
    char temp[size + 1];
    int nIndex = 0;
    for(int i = 0; i < size; i++)
    {
        if(cstr[i] != ' ')
        {
            temp[nIndex] = cstr[i];
            nIndex++;

        }
    }
    temp[nIndex] = '\0';
    if (cstr != nullptr)
    {
        delete [] cstr;
    }
    cstr = new char[nIndex + 1];

    for(int i = 0; i < strlen(temp); i ++)
    {
        cstr[i] = temp[i];
    }
    cstr[nIndex + 1] = '\0';
}
/****
 *      CONTAINSz
 *
 *
 *
 * @param key
 * @return
 */
bool DSString::containsz(DSString key)
{
    DSString tmp(cstr); // MUTABLE COPY OF THIS->CSTR
    int origLength = this->getLength();   // ORIGINAL LENGTH OF STRING PASSED
    int keyLength = strlen(key.c_str());    //LENGTH OF THE KEY BEING SEARCHED FOR
    char beginKey = key[0];         // FIRST CHAR IN KEY


    DSString testStr(keyLength);    // TEST STRING W LENGTH OF KEY

    bool searching = true;
    while(searching)
    {
        int startIndex = tmp.indexOf(beginKey);
        int tempLength = tmp.getLength();

        if(startIndex == -1 || keyLength > origLength || (startIndex + keyLength) > tempLength)
        {
            searching = false;
        }
        else
        {
            testStr = tmp.substring(startIndex, keyLength);

            if(testStr == key)
            {
                return true;
            }
            else
            {
                tmp = tmp.substring(startIndex + 1);
            }
        }
    }
    return false;
}
/*****
 * OVERLOADED NOT EQUAL OPERATOR
 *
 * @param arg
 * @return
 */
bool DSString::operator!=(const char* arg) const
{
    return cstr != arg;
}
/****
 *  OVERLOADED NOT EQUAL OPERATOR
 *
 * @param arg
 * @return
 */
bool DSString::operator!=(const DSString& arg) const
{
    return cstr != arg.cstr;
}