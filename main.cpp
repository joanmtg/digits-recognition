/*
* Proyecto - Análisis y Métodos Numéricos
* Integrantes:
* Jhonier Andrés Calero Rodas 1424599
* Juan Pablo Moreno Muñoz     1423437
* Joan Manuel Tovar Guzmán    1423124
*
* Archivo: main.cpp
* Fecha de entrega: 12/07/2016
* Análisis y Métodos Numéricos
* Universidad del Valle
* EISC
*
*/


#include "mainwindow.h"
#include <QApplication>

//Función main

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
