#include <iostream>
#include <string>
#include <fstream>

#include "BinaryTree.h"

binaryTree bt;
Item item;

void Acommand(std::string str){
    for(char &c : str) {
        item.letter = c;
        bt.Insert(item);
    }
}

void readFile(std::ifstream &entryFile){
    std::string command;
    std::string str;

    while (!entryFile.eof()) {
        std::getline(entryFile, command, ' ');
        std::getline(entryFile, str);
        if (command=="A:"){
            Acommand(str);
        }
        else if (command=="D:"){
            bt.dCommand(str);
        }
        else if (command=="C:"){
            bt.cCommand(str);
        }
    }
    entryFile.close();
}

int main(int argc, char const *argv[]) {
    std::ifstream entryFile(argv[1]);

    readFile(entryFile);


    return 0;
}