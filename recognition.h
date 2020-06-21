/*
* Proyecto - Análisis y Métodos Numéricos
* Integrantes:
* Jhonier Andrés Calero Rodas 1424599
* Juan Pablo Moreno Muñoz     1423437
* Joan Manuel Tovar Guzmán    1423124
*
* Archivo: recognition.h
* Fecha de entrega: 12/07/2016
* Análisis y Métodos Numéricos
* Universidad del Valle
* EISC
*
*/


#ifndef RECOGNITION_H
#define RECOGNITION_H

#include "TNT&JAMA/tnt.h"
#include "TNT&JAMA/jama_cholesky.h"
#include "TNT&JAMA/jama_eig.h"
#include "TNT&JAMA/jama_lu.h"
#include "TNT&JAMA/jama_qr.h"
#include "TNT&JAMA/jama_svd.h"
#include <QFileDialog>
#include <QImage>
#include <QString>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QRgb>
#include <QTextEdit>

class Recognition
{
public:
    Recognition();
    ~Recognition();

    void setDigito(QImage);
    TNT::Array2D<double> identidad(int);
    TNT::Array2D<double> traspuesta(TNT::Array2D<double>);
    TNT::Array2D<double> imageToMatrix(QImage);
    int menorDelArreglo(double[]);
    double norma2(TNT::Array2D<double>);
    int recognize();
    void cargarMatrices();
    void procesarMatrices();


private:
    TNT::Array1D<TNT::Array2D<double> > matrices;
    TNT::Array1D<TNT::Array2D<double> > matricesProcesadas;
    TNT::Array2D<double> digitoEntrada;

};

#endif // RECOGNITION_H
