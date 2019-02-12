//
// Created by ASUS on 1/22/2019.
//

#include "Disco.h"
#include "BitMap.h"
#include "Directorio.h"


bool Disco::CreateDisc()
{
    string nombreDisco;
    cout << "Ingrese nombre del Disco:";
    cin >> nombreDisco;
    if (ExisteDisco(nombreDisco)) {
        cerr << "Ya existe disco!" << endl;
        return false;
    }

    createMetaDataDisk(nombreDisco);
    cout << "Se creo exitosamente!" << endl<<endl;
    return true;
}

void Disco:: createMetaDataDisk(string discoNombre){
    ofstream disco(discoNombre + ".dat",ios::app | ios::out | ios::binary);
    if (!disco.is_open()) {
        cout<<" No se pudo crear!"<<endl;
    }

    METADATA *metadata = new METADATA();
    cout << "Ingrese cantidad de entradas:";
    cin >> metadata->EntryAmount;

    metadata->BlockAmount=metadata->EntryAmount*33308;
    // 12+16+(32*16)+(64*32*16) = 33308 Cantidad de bloques
  //  metadata->BitMapSize= (metadata->BlockAmount/8); //bytes
    metadata->BlockL1 = (metadata->EntryAmount * 2081);
    metadata->BlockL2 = (metadata->EntryAmount * 65);
    metadata->BlockL3 = (metadata->EntryAmount * 1);
    metadata->DiscSize=((4096 * metadata->BlockAmount)/1024)/1024; //byte a kb a mb


    BitMap *map ;
    map->ocupados = 0;
    map->a=metadata->BlockAmount/8;
    map->b=metadata->BlockL1/8;
    map->c=metadata->BlockL2/8;
    map->d=metadata->BlockL3/8;
    map->DBlock= new char[map->a];
    map->initBitMap(map->DBlock,metadata->BlockAmount);

    disco.seekp(0, ios::end);
    disco.write(reinterpret_cast<char*>(metadata), sizeof(METADATA));
    disco.seekp(sizeof(METADATA), ios::end);
    disco.write(reinterpret_cast<char*>(map), sizeof(BitMap));
    cerr<<"Espere un momento..."<<endl;

    //bloques
    for (int i = 0; i < metadata->BlockAmount; i++) {
        blockData *dataEscribir = new blockData();
        disco.write((char*)dataEscribir, sizeof(blockData));
    }

    disco.close();
    cout << " * B I T  M A P * "<<endl;
    cout<<" LVL 1:  " << map->b;
    cout<<" LVL 2:  " << map->c;
    cout<<" LVL 3:  " << map->d<<endl;
    imprimirMETADATA(discoNombre,metadata);
}

bool Disco::ExisteDisco(string directoryName)
{
    string temporal = directoryName + ".dat";
    ifstream archivo(temporal, ios::in | ios::binary);
    if (!archivo) {
        return false;
    }
    return true;
}

void Disco::imprimirMETADATA(string discon,METADATA *md ) {
    cerr<< "* M E T A  D A T A *"<<endl;
    cout<<"Nombre del disco :"<< discon<<endl;
    cout<<"Cantidad de entradas :"<< md->EntryAmount<<endl;
    cout<<"Tamano del disco :"<< md->DiscSize<< " mb" <<endl ;
    cout<<"Tamano de los bloques :"<<md->BlockSize<<endl;
    cout<<"Cantidad de bloques :"<< md->BlockAmount<<endl;
    cout<<"Bloques de primer nivel :"<<md->BlockL1<<endl; //En bits
    cout<<"Bloques de segundo nivel :"<<md->BlockL2<<endl;
    cout<<"Bloques de tercer nivel :"<<md->BlockL3<<endl<<endl;
   }