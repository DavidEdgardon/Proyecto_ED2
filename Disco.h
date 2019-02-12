//
// Created by ASUS on 1/22/2019.
//

#ifndef VIRTUALFILESYSTEM_DISCO_H
#define VIRTUALFILESYSTEM_DISCO_H
#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
#include<string>
#include "Structs.h"
using namespace std;

class Disco {
public:

    string discName;
    bool CreateDisc();
    bool ExisteDisco(string);
    void createMetaDataDisk(string);
    void imprimirMETADATA(string, METADATA*);

};


#endif //VIRTUALFILESYSTEM_DISCO_H
