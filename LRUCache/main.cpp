//
//  main.cpp
//  LRUCache
//
//  Created by Akshat Bhatia on 9/18/13.
//  Copyright (c) 2013 Zonked. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "LRUCache.h"

using namespace std;

/**
 * This method parses the imput file and feeds the commands to LRUCache class. Assumption has been made that the input provided in the file is correct and only some basic checks have been done to verify that the passed in strings are valid input commands for the LRUCache class. It has been assumed that there is just a single space between various parameters on a single line. If the number of parameters are incorrect, then this function prints an exception and returns an error value.
 
 inputFilePath - This parameter provides the path of the input file that needs to be passed.
 
 lruCache - This parameter points to the cache object on which all the input operations are performed.
 *
 */
int ParseInputAndFeedCache(string inputFilePath, LRUCache& lruCache)
{
    string line;
    ifstream myfile (inputFilePath);
    if (myfile.is_open())
    {
        getline(myfile, line);
        int numberOfCommands = 0;
        try
        {
            numberOfCommands = stoi(line);
        }
        catch (exception e)
        {
            cout << "Exception while parsing first line of input file as integer" << e.what();
            return -1;
        }
        //TODO: upper limit of 10 on key-value length
        
        for (int i = 0; i < numberOfCommands; i++)
        {
            getline(myfile, line); //TODO: what if numberOfCommands was incorrect?? If it is inaccurate, throw exception
            std::transform(line.begin(), line.end(), line.begin(), ::tolower);
            size_t pos = line.find(" ");
            string cmd = line.substr(0, pos);
            
            
            if (cmd.compare("bound") == 0)
            {
                try {
                    lruCache.Bound(stoi(line.substr(pos + 1)));
                } catch (exception e) {
                    cout << "Exception while parsing the bound command" << e.what();
                    return -1;
                }
            }
            else if (cmd.compare("get") == 0)
            {
                if (pos == std::string::npos || pos == line.length() - 1)
                {
                    cout << "Exception while parsing the GET command. Get should be followed by a \"key\"";
                    return -1;
                }
                
                string key = line.substr(pos + 1);
                if (key.length() > 10)
                {
                    cout << "Invalid key: " << key << "\n";
                    cout << "Key length should be less or equal to 10 chars \n";
                    return -1;
                }
                
                lruCache.Get(key);
            }
            else if (cmd.compare("set") == 0)
            {
                if (pos == std::string::npos || pos == line.length() - 1)
                {
                    cout << "Exception while parsing the SET command. Set should be followed by a \"key\"";
                    return -1;
                }
                size_t keyPos = line.substr(pos + 1).find(" "); 
                
                if (keyPos == std::string::npos || keyPos == line.length() - pos - 2)
                {
                    cout << "Exception while parsing the SET command. Set should be followed by a \"key\" and \"value\"";
                    return -1;
                }
                
                string key = line.substr(pos + 1).substr(0, keyPos);
                string value = line.substr(pos + 1).substr(keyPos + 1);
                
                if (key.length() > 10)
                {
                    cout << "Invalid key: " << key << "\n";
                    cout << "Key length should be less or equal to 10 chars \n";
                    return -1;
                }

                if (value.length() > 10)
                {
                    cout << "Invalid value: " << value << "\n";
                    cout << "Value length should be less or equal to 10 chars \n";
                    return -1;
                }


                lruCache.Set(make_pair(key, value));
            }
            else if (cmd.compare("peek") == 0)
            {
                if (pos == std::string::npos || pos == line.length() - 1)
                {
                    cout << "Exception while parsing the PEEK command. PEEK should be followed by a \"key\"";
                    return -1;
                }
                
                string key = line.substr(pos + 1);
                if (key.length() > 10)
                {
                    cout << "Invalid key: " << key << "\n";
                    cout << "Key length should be less or equal to 10 chars \n";
                    return -1;
                }
                
                lruCache.Peek(line.substr(pos + 1));
            }
            else if (cmd.compare("dump") == 0)
            {
                lruCache.Dump();
            } else {
                cout << "Exception while parsing the command. Unknow command found \n";
                return -1;
            }
        }
        
        myfile.close();
    }
    else
    {
        cout << "Unable to open file \n";
        return -1;
    }
    return 0;
}

int main(int argc, const char * argv[])
{
    if (argc != 3)
    {
        cout << "This program needs two arguments.\n";
        cout << "Usage: LRUCache.out <inputfile> <outputfile>";
        return -1;
    }
    
    if (strcmp(argv[1], "") == 0)
    {
        cout << "Input file cannot be empty \n";
        return -1;
    }
    
    if (strcmp(argv[2], "") == 0)
    {
        cout << "Output file cannot be empty \n";
        return -1;
    }
    
    ofstream outStream(argv[2]);
    
    if (outStream.is_open())
    {
        LRUCache lruCache(0, outStream);
        int parseInput = ParseInputAndFeedCache(argv[1], lruCache);
        if (parseInput != 0)
        {
            return parseInput;
        }
        outStream.close();
    }
    
    return 0; 
}

