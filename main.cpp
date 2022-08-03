/**
 * Fall 2021 PA 02 Template Repo.
 */

#include <iostream>
#include <fstream>

/**
 * catch_setup.h and catch_setup.cpp contain the #define directive for
 * the CATCH2 framework.  You can see in main below how I'm calling the
 * runCatchTests() function which is declared in this header.
 *
 * On average, this should reduce the build time for your project on your local
 * machine.
 */
#include "catch_setup.h"
#include "DSString.h"
#include "DSVector.h"
#include "Autoindexer.h"

int main(int argc, char** argv)
{
    if(argc == 0)
    {
        runCatchTests();
    }
    else if(argc == 5)
    {
        // TODO: ORDER ARGUMENTS CORRECTLY

        Autoindexer *indexer = new Autoindexer();
        indexer->readInKeyWords(argv);
        indexer->runAutoIndex(argv);
        indexer->beginIndexing();
        indexer->generateIndex();

        delete indexer;


    }
    return 0;
}

// int x = new int[10]
