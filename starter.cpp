#include "starter.h"
#include "globalVariables.h"

void starter()
{
    std::ifstream fin("../sources/program.txt");
    fin.seekg(0, std::ios::end);
    std::streampos fileSize = fin.tellg();
    fin.seekg(0, std::ios::beg);

    char* c = new char[fileSize];

    fin.read(c, fileSize);

    std::string program;
    for (int i = 0; i < fileSize; ++i)
    {
        if (c[i] == '\r') continue;
        program.push_back(c[i]);
    }
    global::text = program;
    std::ifstream service_words_in("../sources/services_words"),
                  types_in("../sources/types");
    std::string word;
    while (!service_words_in.eof())
    {
        service_words_in >> word;
        global::service_words_trie.addString(word);
    }
    while (!types_in.eof())
    {
        types_in >> word;
        global::types_trie.addString(word);
    }
    delete[] c;
    fin.close();
}
