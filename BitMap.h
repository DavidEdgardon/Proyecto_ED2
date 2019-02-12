//
// Created by ASUS on 2/6/2019.
//

#ifndef VIRTUALFILESYSTEM_BITMAP_H
#define VIRTUALFILESYSTEM_BITMAP_H


class BitMap {
public:
    int a, b, c , d, ocupados;

    char* DBlock = new char[a];
    char* BlockLvl1 = new char[b];
    char* BlockLvl2 = new char[c];
    char* BlockLvl3 = new char[d];



    void initBitMap(char*, int);
    void setOn(char*, int);
    void setOff(char*, int);

};


#endif //VIRTUALFILESYSTEM_BITMAP_H
