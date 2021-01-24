#include "MarkovChain.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cassert>


MarkovChain::MarkovChain()
    : m_keyLength(3)
{
    readTextFile("qrc:/brown.txt");
    createDictionary();
}
MarkovChain::MarkovChain(unsigned int keyLength, std::string fileName)
    : m_keyLength(keyLength)
{
    readTextFile(fileName);
    createDictionary();
}

void MarkovChain::readTextFile (std::string fileName)
{
    std::ifstream file (fileName);
    assert(!file.fail());
    std::string word;
    while (file >> word) {
        m_fileBuffer.push_back(word);
    }
    file.close();
}

void MarkovChain::createDictionary ()
{
    for(std::vector<std::string>::iterator it = m_fileBuffer.begin(); it != m_fileBuffer.end(); it++)
    {
        std::string key;
        std::vector<std::string>::iterator it2 = it;
        for(unsigned int i = 0; i != m_keyLength; i++)
        {
            if(it2 == m_fileBuffer.end())
            {
                it2 = m_fileBuffer.begin();
            }
            key += *it2;
            if(i != (m_keyLength - 1))
            {
                key += " ";
            }
            it2++;
        }
        if(it2 == m_fileBuffer.end())
        {
            it2 = m_fileBuffer.begin();
        }
        std::string suffix = *(it2);
        if(std::find(m_dictionary[key].begin(), m_dictionary[key].end(), suffix) == m_dictionary[key].end())
        {
            m_dictionary[key].push_back(suffix);
        }
    }
}

QString MarkovChain::generateText (unsigned int numberOfWords)
{
    std::map<std::string, std::vector<std::string> >::iterator it = m_dictionary.begin();
    srand (time(NULL));
    std::advance(it, rand() % m_dictionary.size());
    std::string output;

    std::string key = (*it).first;
    output = key;
    for(unsigned int i = 0; i < numberOfWords - m_keyLength; i++) {
        std::vector<std::string> values = m_dictionary[key];
        std::string suffix = values[rand() % values.size()];
        size_t pos = key.find_first_of(" ", 0);
        std::string newKey = key.substr(pos + 1);
        key = newKey + " " + suffix;
        output += " " + suffix;
    }
    return QString::fromStdString(output);
}
