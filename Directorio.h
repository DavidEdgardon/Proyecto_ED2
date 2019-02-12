//
// Created by ASUS on 1/30/2019.
//

#ifndef VIRTUALFILESYSTEM_DIRECTORIO_H
#define VIRTUALFILESYSTEM_DIRECTORIO_H
#include "iostream"
using namespace std;
#include "Structs.h"
#include "BitMap.h"

class Directorio {
public:
    int size;
    int PosActual;
    string Ubicacion;
    string discName;
    int sizeArchivos;
    int bloques;

    Directorio(int,string, int);
    void CreateDirectory(fileEntry array[]);
    void ListDirectory(fileEntry array[]);
    void ChangeDirectory(fileEntry array[]);
    void Goback(fileEntry array[]);
    void writeArray(fileEntry array[], int );
    void ListForFather(fileEntry array[]);
    void UpdateDisc(METADATA *,BitMap *,fileEntry array[]);
    void Delete(fileEntry array[], string );
    void DeleteArch(fileEntry array[], string , BitMap *, int );
    void updateArray(fileEntry array[]);
    void Import(fileEntry *array, BitMap *);
    void Export(fileEntry *array, BitMap *);

};



#endif //VIRTUALFILESYSTEM_DIRECTORIO_H
