//
// Created by ASUS on 1/22/2019.
//

#ifndef VIRTUALFILESYSTEM_STRUCTS_H
#define VIRTUALFILESYSTEM_STRUCTS_H


struct blockData
{
    char data[4096];
    int siguiente = -1;
};

struct DataBlock_I1{
    blockData points[16];
};

struct DataBlock_I2{
    DataBlock_I1 points[32];
};

struct DataBlock_I3{
    DataBlock_I2 points[64];
};

struct Date{
    char day[2];
    char month[2];
    char year[4];
};

struct fileEntry
{
    char FileName[30];
    char type= ' ';
    Date Creation_date;
    unsigned int size;
    unsigned int DB_directs[12]; //48
    unsigned int DB_indirects[3]; //12
    int padre =-1;
    int primerHijo = -1;
    int hermanoDerecho= -1;
    bool ocupado = false;

};//117

struct METADATA
{
    int EntryAmount;
    int BlockSize = 4096;
    int BlockAmount;
    int DiscSize ;
    int BlockL1;
    int BlockL2;
    int BlockL3;
};





#endif //VIRTUALFILESYSTEM_STRUCTS_H
