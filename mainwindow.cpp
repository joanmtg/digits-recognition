/*
* Proyecto - Análisis y Métodos Numéricos
* Integrantes:
* Jhonier Andrés Calero Rodas 1424599
* Juan Pablo Moreno Muñoz     1423437
* Joan Manuel Tovar Guzmán    1423124
*
* Archivo: mainwindow.cpp
* Fecha de entrega: 12/07/2016
* Análisis y Métodos Numéricos
* Universidad del Valle
* EISC
*
*/


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Se crea un objeto de la clase Recognition
    //y se cargan y procesan las matrices

    recognizer = Recognition();
    recognizer.cargarMatrices();
    recognizer.procesarMatrices();

    // Se desactiva el botón de reconocer y
    // el lineEdit se pone en sólo lectura

    ui->areaInfo->setReadOnly(true);
    ui->botonReconocer->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_botonCargar_clicked()
{
    //Si se presiona el botón de cargar

    //Se obtiene la ruta con un FiileDialog
    QString fileName=QFileDialog::getOpenFileName(
                this,
                tr("Abrir imagen"),
                "../Digitos/images/",
                "Bitmap Images (*.bmp)",
                0,
                QFileDialog::DontUseNativeDialog);


    //Se crea una QImage y se carga con la ruta obtenida

    QImage imagen;
    bool carga = imagen.load(fileName);

    //Si la imagen se cargó

    if(carga){

        //Para mostrar la imagen en un label se utiliza QPixMap
        QPixmap pm1 = QPixmap::fromImage(imagen);
        ui->labelImage->setPixmap(pm1);
        ui->botonReconocer->setEnabled(true);

        //Se guarda el dígito de entrada en el recognizer

        recognizer.setDigito(imagen);
        ui->areaInfo->setText("");

    }
}



void MainWindow::on_botonReconocer_clicked(){

    //Si presiona el botón reconocer

    //Se llama al método recognize y se guarda su resultado en la variable numero
    int numero = recognizer.recognize();

    //Se muestra en el área de resultados el mensaje de reconocimiento:

    QString mensaje = "El número reconocido es el " + QString::number(numero);
    ui->areaInfo->setText(mensaje);

}

