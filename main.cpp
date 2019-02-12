#include <iostream>

#include <string>
#include <iostream>
#include "Disco.h"
#include "Directorio.h"
#include "BitMap.h"

using namespace std;

int main()
{
    string nombreDisco = "";
    Disco* disco = new Disco();
    string n;
      int opcion;
    string opc2;
    bool continuar = true;
    do
    {
        cout << "*** V I R T U A L  S Y S T E M  F I L E ***" << endl;
        cout << "1. Crear disco" << endl;
        cout << "2. Usar disco existente" << endl;
        cout << "3. Salir" << endl;
        cout << " Ingrese una opcion: " << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
            {
                nombreDisco = disco->CreateDisc();
            }
                break;
            case 2:
            {
                cout << "Ingrese nombre del disco a utilizar:" << endl;
                cin >> nombreDisco;
                string nombret = nombreDisco + ".dat";
                if (disco->ExisteDisco(nombreDisco))
                {
                    METADATA *metadata = new METADATA();
                    BitMap *map = new BitMap();

                    ifstream lectura(nombret, ios::in|ios::binary);
                    lectura.seekg(0,ios::beg);
                    lectura.read(reinterpret_cast<char *>(metadata), sizeof(METADATA));
                    lectura.seekg(sizeof(METADATA),ios::beg);
                    lectura.read(reinterpret_cast<char *>(map), sizeof(BitMap));


                    Directorio *dir=new Directorio(metadata->EntryAmount,disco->discName,metadata->BlockAmount);
                    dir->discName=nombreDisco;

                    fileEntry array[metadata->EntryAmount];
                    for(int i=0 ; i<metadata->EntryAmount; i++){
                        lectura.read(reinterpret_cast<char*>(&array[i]), sizeof(fileEntry));
                    }
                    lectura.close();

                    do {
                        cout <<endl<< "** M E N U  D E  D I R E C T O R I O S **" << endl;
                        cout <<"Disk :"<<dir->discName<<"://"<<dir->Ubicacion <<endl;
                        cout<< dir->PosActual<<endl;
                        cout << "\tmkdir (m)  .Crear Directorio" << endl;
                        cout << "\tcd (c)     .Cambiar Directorio" << endl;
                        cout << "\tls (l)     .Listar Directorio" << endl;
                        cout << "\trm (r)     .Eliminar Directorio/Archivo" << endl;
                        cout << "\timpor (i)  .Importar Archivo" << endl;
                        cout << "\texport (e) .Exportar Archivo" << endl;
                        cout << "\tback (b)   .Regresar" << endl;
                        cout << "\tmenu (p)   .Menu Principal" <<endl;
                        cout << "Ingrese su opcion: ";
                        cin >> opc2 ;

                        switch (opc2.at(0)) {
                            case 'm':
                               dir->CreateDirectory(array);
                                break;
                            case 'c':
                                dir->ChangeDirectory(array);
                                break;
                            case 'l':
                               dir->ListDirectory(array);
                              //  dir->ListForFather(array);
                                break;
                            case 'r':
                                cout<<" Ingrese directorio/archivo a eliminar :"<<endl;
                                cin>> n;
                                dir->Delete(array,n);
                                break;
                            case 'i':
                                dir->Import(array, map);
                                break;
                            case 'e':
                                dir->Export(array, map);
                                break;
                            case 'b':
                                dir->Goback(array);
                                break;
                            case 'p':
                                dir->UpdateDisc(metadata,map,array);
                                continuar = false;
                                break;

                        }
                    }while(continuar);
                }else
                {
                    cout << "No se encontro un disco con ese nombre." << endl;
                }


            }
                break;
            case 3:{

            }
                break;
        }
    } while (opcion!=3);

    return 0;
}
