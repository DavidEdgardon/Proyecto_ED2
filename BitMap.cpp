//
// Created by ASUS on 2/6/2019.
//

#include "BitMap.h"
#include "Structs.h"

void BitMap::initBitMap(char *bitMap, int Block_Amount) {
    for(int i = 0; i < Block_Amount/8; i++){
        bitMap[i] = 0;
    }
}

void BitMap::setOn(char *bitMap, int nBlock) {
    int positionByte = nBlock/8;
    int iniPosition = (nBlock/8) * 8;

    for(int i = iniPosition, x = 7; i < (positionByte * 8) + 8; i++, x--){
        if(i == nBlock){
            bitMap[positionByte] |= 1 << x;
            break;
        }
    }
}

void BitMap::setOff(char *bitMap, int nBlock) {
    int positionByte = nBlock/8;
    int iniPosition = (nBlock/8) * 8;

    for(int i = iniPosition, x = 7; i < (positionByte * 8) + 8; i++, x--){
        if(i == nBlock){
            bitMap[positionByte] &= ~(1 << x);
            break;
        }
    }
}