#include "starter.h"
#include "globalVariables.h"

void starter() {
    std::ifstream fin("../sources/program.txt");
    fin.seekg(0, std::ios::end);
    std::streampos fileSize = fin.tellg();
    fin.seekg(0, std::ios::beg);

    char* c = new char[fileSize];

    fin.read(c, fileSize);

    std::string program;

    for (int i = 0; i < fileSize; ++i) {
        if (c[i] == '\r') continue;
        program.push_back(c[i]);
    }

    text = program;

    delete[] c;



    fin.close();

}