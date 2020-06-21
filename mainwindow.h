/**
* Proyecto - Programación Interactiva
* Integrantes:
* Jhonier Andrés Calero Rodas 1424599
* Juan Pablo Moreno Muñoz 1423437
* Joan Manuel Tovar Guzmán 1423124
*
* Archivo: Servidor.java
* Fecha de entrega: 11/06/2015
* Programación Interactiva Universidad del Valle EISC
* */



#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QString>
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QRgb>
#include "recognition.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    


private slots:
    void on_botonCargar_clicked();
    void on_botonReconocer_clicked();

private:
    Recognition recognizer;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
