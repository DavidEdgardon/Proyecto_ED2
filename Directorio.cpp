//
// Created by ASUS on 1/30/2019.
//

#include <fstream>
#include "Directorio.h"
#include "iostream"
#include "BitMap.h"
#include "Disco.h"

using namespace std;
int cantOcupado = 0;

Directorio::Directorio(int tam , string DiscName, int block ) {
    this->size=tam;
    this->PosActual=-1;
    this->bloques = block;
    this->discName=DiscName;
}

void Directorio::CreateDirectory(fileEntry array[])  {
    fileEntry tmp;
    int actual = this->PosActual;
    cout<<"Ingrese el nombre del directorio"<<endl;
    cin>>tmp.FileName ;
    tmp.type = 'D';
    tmp.padre=actual; //-1
    tmp.size = 117;
    int cont=0; //SI tiene mas entradas libres
    for(int d; d<size;d++){
        if(array[d].ocupado==true) //Saber cuantos hay ocupados
            cantOcupado++;
    }

    for(int i=0; i<this->size ; i++){
        if(array[i].ocupado == false){
            if(i<cantOcupado){ //
                array[i].ocupado = true;
                tmp.ocupado = true;
                tmp.primerHijo = -1;
                tmp.hermanoDerecho = -1;
                array[i] = tmp;
                cout << "Se creo la carpeta: " << tmp.FileName << "\n";
                for (int h = 0; h < this->size; h++) {
                    if (h != i && array[h].hermanoDerecho == -1 && array[h].padre==array[i].padre) { //posiciona el hermano del nuevo, si este esta antes que el
                        array[h].hermanoDerecho = i;
                        return;
                    }
                    if(array[h].primerHijo==-1 && h==actual){ //actualiza el hijo del padre si esta antes de el
                        array[h].primerHijo=i;
                        return;
                    }
                }
                break;
            }
            array[i].ocupado = true;
            tmp.ocupado = true;
            tmp.primerHijo = -1;
            tmp.hermanoDerecho = -1; //Creando uno tras otro
            array[i] = tmp;
            cout << "Se creo la carpeta: " << tmp.FileName << "\n";
            if(cantOcupado>0) {
                for (int j = 0; j < this->size; j++) {
                    if (array[j].padre == array[i].padre && array[j].hermanoDerecho == -1) { //Actualiza el hermano anterios de tmp
                        array[j].hermanoDerecho = i;
                        return;
                    }
                    if(array[j].primerHijo ==-1 && j==actual){
                        array[j].primerHijo =i;
                        return;
                    }
                }
            }
            break;
        }
        cont++;
        if(cont==this->size)
            cerr<<"Espacio Insuficiente!"<<endl;
    }
    cantOcupado=0;
}

void Directorio::writeArray(fileEntry *array, int tam) {
    ofstream directorios(discName + ".dat",ios::out|ios::binary);
    for(int a=0;a<size;a++) {
        fileEntry arr=array[a];
         directorios.write(reinterpret_cast<char *>(&arr),sizeof(fileEntry));
    }
}

void Directorio::UpdateDisc(METADATA *metadata,BitMap * map,fileEntry *array) {
    ofstream disco(discName + ".dat", ios::out | ios::binary);
    if (!disco.is_open()) {
        cout<<"No se pudo abrir!"<<endl;
    }

    disco.seekp(0, ios::end);
    disco.write(reinterpret_cast<char*>(metadata), sizeof(METADATA));
   // disco.write(reinterpret_cast<char*>(map), sizeof(BitMap));
    disco.seekp(sizeof(BitMap) , ios::end);


    //Escribir arreglo en el disco
    for(int a=0;a<size;a++) {
        fileEntry arr=array[a];
        disco.write(reinterpret_cast<char *>(&arr),sizeof(fileEntry));
    }
    //bloques
    for (int i = 0; i < metadata->BlockAmount; i++) {
        blockData *dataEscribir = new blockData();
        disco.write((char*)dataEscribir, sizeof(blockData));
    }

    Disco *disc;
    disco.close();
   cout << " * B I T  M A P * "<<endl;
    cout<<" LVL 1: " << map->b;
    cout<<" LVL 2: " << map->c;
    cout<<" LVL 3: " << map->d<<endl;
  disc->imprimirMETADATA(discName,metadata);
}

void Directorio::ChangeDirectory(fileEntry *array) {
    string nom;
    cout<<"Ingrese nombre de Carpeta:";
    cin>>nom;
    for(int i=0; i<size; i++) {
        if (array[i].FileName == nom ) {
            Ubicacion = nom;
                    this->PosActual = i;
                break;
        }/*else{
            cerr << "Carpeta inexistente!" << endl;
            break;
        }*/
    }
}

void Directorio::Goback(fileEntry *array) {
    for(int i=0; i<size ; i++){
        if(i==this->PosActual) { //Regresar una posicion atras
            if(array[i].padre==-1) //Raiz
                Ubicacion=" ";
            else{
               this->PosActual = array[i].padre; //lo coloca en la pos del padre
                Ubicacion=array[PosActual].FileName;
                break;
            }
        }
    }
}

void Directorio::ListDirectory(fileEntry array[]) {
cout<<"** L I S T A  D E  D I R E C T O R I O S **"<<endl;
    for (int i = 0; i < this->size; i++) {
        if(array[i].ocupado) {
            cout << "Nombre: " << array[i].FileName << endl;
            cout << "Tipo: " << array[i].type << endl;
            cout << "Padre: "  << array[i].padre <<endl;
            cout << "Hermano Derecho: " << array[i].hermanoDerecho << endl;
            cout << "Primer Hijo:" <<array[i].primerHijo <<endl;
            cout << "Tamano:"<<array[i].size << " bytes" <<endl;
            cout << "================================"<<endl;
        }else{

        }

    }
}

void Directorio::ListForFather(fileEntry *array) {
    cout<<"** L I S T A  D E  D I R E C T O R I O S **"<<endl;
   cout << "Carpeta \t\t Tipo \t\tTamano" << endl;
    for (int i = 0; i < this->size; i++) {
        if (array[i].padre == this->PosActual) {
            if (array[i].ocupado) {
                cout << "   " << array[i].FileName << "  \t\t " << array[i].type << "  \t\t " << array[i].size << " bytes"<< endl;
            } else
                cout<<"";
        }
    }
}

void Directorio::updateArray(fileEntry *array) {
    fileEntry tmp;
    for(int i=0; i<size ; i++) {
        for (int j = 0; j < size; j++) {
            if (array[j].padre == tmp.padre && tmp.hermanoDerecho == -1 && array[j].hermanoDerecho == i) {
                array[j].hermanoDerecho = -1;
                break;
            }
            if (array[j].padre == tmp.padre && tmp.hermanoDerecho != 1 && array[j].hermanoDerecho == i) {
                array[j].hermanoDerecho = tmp.hermanoDerecho;
                break;
            }
            if (tmp.hermanoDerecho != -1 && array[j].primerHijo == i) {
                array[j].primerHijo = tmp.hermanoDerecho;
                break;
            }
            if (tmp.hermanoDerecho == -1 && array[j].primerHijo == i) {
                array[j].primerHijo = -1;
                break;
            }
        }
    }
}

void Directorio::Delete(fileEntry *array, string name) {
    int actual = this->PosActual;
    int x=0;
    for(int i=0; i<size ; i++){
        fileEntry tmp , tmp2;
        if(array[i].FileName==name){ //Si el directorio existe en el arreglo
            fileEntry empty;
            tmp= array[i];//tmp almacena la pos de la raiz

            if(tmp.primerHijo!=-1) { //si la raiz es !=1, es por que tiene hijo
                if(array[tmp.primerHijo].hermanoDerecho!=-1){ // si el hijo !=1, es porque tiene hermano
                    actual=tmp.primerHijo; //Se guarda la posicion del primer hijo
                    x=array[actual].hermanoDerecho; //se guarda la poscion del hermano
                    tmp2=array[x]; //aqui agarra el hermano derecho del primer hijo
                    Delete(array,tmp2.FileName); //recursividad
                }//Solo cuando el padre tiene un hijo
                actual = tmp.primerHijo;
                delete (&tmp);
                empty.ocupado = false;
                array[i] = empty;
                Delete(array, array[actual].FileName);
            }//BORRA EL PADRE
            delete (&tmp);
            empty.ocupado = false;
            array[i] = empty;
            for(int i=0; i<size ; i++) {
                for (int j = 0; j < size; j++) {
                    if (array[j].padre == tmp.padre && tmp.hermanoDerecho == -1 && array[j].hermanoDerecho == i) {
                        array[j].hermanoDerecho = -1;
                        break;
                    }
                    if (array[j].padre == tmp.padre && tmp.hermanoDerecho != 1 && array[j].hermanoDerecho == i) {
                        array[j].hermanoDerecho = tmp.hermanoDerecho;
                        break;
                    }
                    if (tmp.hermanoDerecho != -1 && array[j].primerHijo == i) {
                        array[j].primerHijo = tmp.hermanoDerecho;
                        break;
                    }
                    if (tmp.hermanoDerecho == -1 && array[j].primerHijo == i) {
                        array[j].primerHijo = -1;
                        break;
                    }
                }
            }

            //Actualizar las carpetas sobrantes
            //updateArray(array);
        }
    }
}

void Directorio::Import(fileEntry *array, BitMap *bitmap) {

    fileEntry tmp;
    int bloquesAOcupar=0;
    cout<<"Nombre del documento:";
    cin>>tmp.FileName;
    ifstream lectura(tmp.FileName, ios::in | ios::binary);
    if(lectura) {
        lectura.seekg(0 , ios::end);
        sizeArchivos=lectura.tellg();

        if(sizeArchivos<= ((this->bloques)*4096)){
            /*****************Guardando- en Arreglo****************/
            int actual = this->PosActual;
            tmp.padre=actual;
            tmp.type='A';
            tmp.size=sizeArchivos;
            int cont=0;
            for(int d; d<size;d++){
                if(array[d].ocupado==true)
                    cantOcupado++;
            }
            for(int i=0; i<this->size; i++){
                if(array[i].ocupado == false){
                    if(i<cantOcupado){
                        array[i].ocupado = true;
                        tmp.ocupado = true;
                        tmp.primerHijo = -1;
                        tmp.hermanoDerecho = -1;
                        array[i] = tmp;
                        cout << "Se importo el archivo: " << tmp.FileName << "\n";
                        for (int h = 0; h < this->size; h++) {
                            if (h != i && array[h].hermanoDerecho == -1 && array[h].padre==array[i].padre) {
                                array[h].hermanoDerecho = i;
                                return;
                            }
                            if(array[h].primerHijo==-1 && h==actual){
                                array[h].primerHijo=i;
                                return;
                            }
                        }break;
                    }
                    array[i].ocupado = true;
                    tmp.ocupado= true;
                    tmp.primerHijo = -1;
                    tmp.hermanoDerecho = -1;
                    array[i] = tmp;
                    cout << "Se importo el archivo: " << tmp.FileName << "\n";
                    if(cantOcupado>0) {
                        for (int j = 0; j < this->size; j++) {
                            if (array[j].padre == array[i].padre && array[j].hermanoDerecho == -1) {
                                array[j].hermanoDerecho= i;
                                return;
                            }
                            if(array[j].primerHijo==-1 && j==actual){
                                array[j].primerHijo=i;
                             return;
                            }
                        }
                    }break;
                }cont++;
                if(cont==this->size)
                    cout<<"Ya no hay suficiente espacio\n";
            }cantOcupado=0;

            bloquesAOcupar=tmp.size/4096;
            for(int x=bitmap->ocupados+1; x<bloquesAOcupar; x++) {
                bitmap->setOn(bitmap->DBlock, x);
                bitmap->ocupados++;
            }

        }else{
            cerr<<"Espacio Insuficiente!"<<endl;
        }
    }else{
        cerr<<"No se importo!"<<endl;
    }
}

void Directorio::DeleteArch(fileEntry *array, string name, BitMap *map, int blockOFF) {
    for(int i=blockOFF; i<=0 ; i--){
        map->setOff(map->DBlock,i);
    }
}

void Directorio::Export(fileEntry *array, BitMap *map) {
    fileEntry tmp;
    char name[30];
    cout<<"Nombre del documento a exportar:"<<endl;
    cin>>tmp.FileName;
    cout << "Ingrese nombre del archivo con su formato que desea copiar" << endl;
    cin >> name;
    ofstream discDat(name, ios::in | ios::binary);
    discDat.seekp(0, ios::beg);

}