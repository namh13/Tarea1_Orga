// queue::push/pop
#include "Mascota.h"
#include "Evaluador.h"
#include <iostream>
#include <list>
#include <fstream>
using namespace std;

//Escribe los datos del objeto mascota dado en un archivo binario con el nombre dado en la posicion dada
//Nota: Se deben poder agregar varias mascotas en un solo archivo
void escribir(string nombre_archivo, Mascota*mascota, int posicion)
{
    ofstream out(nombre_archivo.c_str(),ios::in | ios::binary); //Abrimos el archivo en modo de escritura,entrada y le especificamos que es binario(necesario para que funcione en windows)
    out.seekp(posicion*34); //asignamos la poscion que tendra la mascota pero multiplicada por 34
    out.write((char*)&mascota->edad,4); //escribimos en el archivo la edad de la mascota
    out.write(mascota->nombre.c_str(),30); //escribimos en el archivo el nombre de la mascota
    out.close(); //cerramos el archivo
}

//Devuelve una mascota previamente escrita (con la funcion escribir()) en un archivo binario con nombre dado en la posicion dada
//Nota: Se deben poder leer varias mascotas de un solo archivo
Mascota* leer(string nombre_archivo, int posicion)
{
    // Me guie de la funcion de Imprimir de clase pero imprimimos de uno en uno/////
    ifstream in(nombre_archivo.c_str()); //abrimos el archivo en modo lectura
    in.seekg(posicion*34); //le decimos que la posicion del archivo se va a multiplicar por 34 para seguir la secuencia de las mascotas

    char nombre[30]; //variable para guardar el nombre de la mascota
    int edad=0; //variable para guardar la edad de la mascota

    in.read((char*)&edad,4); //leemos el archivo y obtenemos la edad de la mascota
    in.read(nombre,30); //leemos el archivo y obtenemos el nombre de la mascota
    in.close(); //cerramos el archivo

    Mascota *m = new Mascota(edad,nombre); //creamos una nueva mascota en la clase Mascota
    return m; //retornamos las mascotas
}

//Devuelve un vector que contenga todas las mascotas previamente escritas (con la funcion escribir()) en un archivo binario con nombre dado
//Nota: El vector debe contener las mascotas ordenadas de acuerdo a la posicion en la que se escribieron
vector<Mascota*> leerTodos(string nombre_archivo)
{
    //Me Guie de la Funcion Imprimir que hicimos en clase//
    vector<Mascota*>respuesta; //vector donde se guardan las mascotas

    ifstream in(nombre_archivo.c_str()); //Abrimos el archivo en modo lectura
    in.seekg(0,in.end); //Nos vamos al final del archivo

    int tam = in.tellg()/34; // variable donde donde guardamos la cantidad de mascotas que hay en el archivo.
    // La cual obtenemos con la funcion tellg que nos dice la secuencia del archivo y la dividimos entre 34 para saber cuantas mascotas hay

    in.seekg(0,in.beg);//Volvemos al inicio del archivo

    int edad=0; //variable para guardar la edad de la mascota
    char nombre[30]; //variable para guardar el nombre de la mascota

    for(int i=0; i<tam; i++) //ciclo en donde sacamos las mascotas del archivo
    {
        in.read((char*)&edad,4); //sacamos la edad del archivo y la guardamos en la variable edad
        in.read(nombre,30); //sacamos el nombre del archivo y la guardamos en la variable nombre
        respuesta.push_back(new Mascota(edad,nombre)); //enviamos al final del vector la edad y el nombre de la mascota
    }
    return respuesta; //retornamos el vector respuesta
}

int main ()
{
    //Funcion evaluadora
    evaluar();
    return 0;
}
