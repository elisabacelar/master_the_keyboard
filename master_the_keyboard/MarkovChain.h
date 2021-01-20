#ifndef MARKOV_CHAIN_HEADER_FILE
#define MARKOV_CHAIN_HEADER_FILE

#include <string>
#include <vector>
#include <map>
#include <QString>

class MarkovChain {
    public:
        MarkovChain();
        MarkovChain(unsigned int keyLength, std::string fileName);
        QString generateText (unsigned int numberOfWords);

    private:
        void createDictionary();
        void readTextFile (std::string fileName);

        unsigned int m_keyLength;
        std::vector<std::string> m_fileBuffer;
        std::map<std::string, std::vector<std::string>> m_dictionary;
};

#endif //MARKOV_CHAIN_HEADER_FILE
