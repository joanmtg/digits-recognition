/*
* Proyecto - Análisis y Métodos Numéricos
* Integrantes:
* Jhonier Andrés Calero Rodas 1424599
* Juan Pablo Moreno Muñoz     1423437
* Joan Manuel Tovar Guzmán    1423124
*
* Archivo: recognition.cpp
* Fecha de entrega: 12/07/2016
* Análisis y Métodos Numéricos
* Universidad del Valle
* EISC
*
*/


#include "recognition.h"

//Constructor de la clase

Recognition::Recognition(){

    //Se inicializan los atributos de la clase

    matrices = TNT::Array1D<TNT::Array2D<double> >(10);
    matricesProcesadas = TNT::Array1D<TNT::Array2D<double> >(10);
    digitoEntrada = TNT::Array2D<double> (784,1);
}

//Destructor de la clase

Recognition::~Recognition(){

}


// Método setDigito: QImage --> void
// Recibe una QImage y guarda un arreglo 2D
// de 784X1 en el atributo digitoEntrada de la clase

void Recognition::setDigito(QImage imagen){

    digitoEntrada = imageToMatrix(imagen);

}

// Método identidad: int --> Array2D<double>
// Recibe un entero n y devuelve un arreglo2D
// de nxn que representa a la matriz identidad nxn

TNT::Array2D<double> Recognition::identidad(int n){

    //Se inicializan todos los valores de la matriz en 0

    TNT::Array2D<double> matrizI(n,n,0.0);

    //For para poner 1's en la diagonal

    for(int i=0; i<n;i++){
        matrizI[i][i]=1;
    }

    return matrizI;

}


// Método traspuesta: Array2D<double> --> Array2D<double>
// Recibe una matriz (Array2D) y devuelve su traspuesta

TNT::Array2D<double> Recognition::traspuesta(TNT::Array2D<double> matriz){

    int filas = matriz.dim1();
    int columnas = matriz.dim2();

    TNT::Array2D<double> traspuesta(columnas,filas);

    // For que recorre la matriz y guarda la traspuesta en una nueva matriz
    // traspuesta j,i será matriz i,j   para todo i,j

    for(int i=0; i<filas; i++){

        for(int j=0; j<columnas; j++){
            traspuesta[j][i]=matriz[i][j];
        }

    }

    //Se retorna el resultado

    return traspuesta;

}


// Método imageToMatrix: QImage -> Array2D<double>
// Reciba una QImage y guarda los valores de color de los pixeles
// de la imagen como 1's y 0's en una matriz 784x1.

TNT::Array2D<double> Recognition::imageToMatrix(QImage imagen){

    int width  = imagen.width();
    int height = imagen.height();

    //Se convierte el formato de imagen a monocromático, para que sólo haya
    //valores de 255's y 0's

    QImage image= imagen.convertToFormat(QImage::Format_Mono);

    //Se crea la matriz donde se van a guardar los bits

    TNT::Array2D<double> matrix(width*height,1);

    //En una imagen en escala de grises R=G=B, por lo que da igual
    //con cuál de estos 3 valores se rellene la matriz

    int indice=0;

    //For para guardar los valores de colo de los pixeles

    for(int i=0; i<width ; i++){
        for(int j=0; j<height ; j++){

            //Se obtiene el color del pixel j,i
            double color = qRed(image.pixel(j,i));

            //Se cambian los 255's por 1's
            if(color==255){
                color=1;
            }

            //Se guarda el color en la matriz
            matrix[indice][0] = color;
            indice++;
        }
    }

    //Se retorna la matriz

    return matrix;

}


// Método menorDelArreglo: double[] -> int
// Se recibe un arreglo de double y se retorna
// la posición del número menor en el arreglo


int Recognition::menorDelArreglo(double arreglo[]){

    //Se sobreestima el menor, al asumir que el primero es el menor
    int posMenor=0;
    double menor = arreglo[0];
    int length = 10;

    //Se recorre el arreglo para identificar el menor número y su posición

    for(int i=1; i<length; i++){

        if(arreglo[i]<menor){

            menor=arreglo[i];
            posMenor=i;
        }
    }

    //Se retorna la posición del menor

    return posMenor;

}


// Método norma2: Array2D<double> --> double
// Se recibe un arreglo 2D y se retorna su norma2
// sqrt(X0^2+X1^2+...+ Xn^2)

double Recognition::norma2(TNT::Array2D<double> arreglo){

    double norma=0;

    //For para calcular el cuadrado de cada elemento y sumarlo
    //de manera acumulada en la variable norma

    for(int i=0; i<arreglo.dim1(); i++){

        norma+=pow(arreglo[i][0],2);
    }

    //Se saca la raíz cuadrada de la suma y se retorna el resultado

    norma=sqrt(norma);

    return norma;

}



// Método recognize:   --> int
// Este método es el que se encarga de reconocer el dígito de entrada


int Recognition::recognize(){

    //Se crea un arreglo de double para guardar cada residual obtenido

    double residuales[10];

    //En este for, haciendo uso de las fórmulas para calcular el residual relativo,
    //se calcula cada uno de los residuales relativos teniendo las matrices base
    //ya porcesadas y los pixeles de la imagen a reconocer guardados en una matriz (784x1), un vector

    //Esto se hace con las matrices base de 0,1,2...9

    for(int k=0; k<10; k++){

        //Se multiplica la matriz procesada con el dígito de entrada (Z)
        TNT::Array2D<double> resultado = matmult(matricesProcesadas[k] , digitoEntrada);

        //Se calcula el residual dividiendo la norma2 del resultado obtenido entre la norma2 del dígito de entrada
        double residual = norma2(resultado)/norma2(digitoEntrada);

        //Se guarda el residual en el arreglo de residuales
        residuales[k]=residual;

    }

    //Se identifica la posición del menor residual del arreglo con un método auxiliar

    int menorResidual = menorDelArreglo(residuales);

    //Se retorna la posición del menor resiudal. Dicha posición puede er 0,1...9
    //En resumen, esta posición determina el dígito reconocido

    return menorResidual;
}


// Método cargarMatrices
// Este método se encarga de cargar las matrices base de cada uno de los dígitos 0,1,2,...,9
// Guarda los colores de los pixeles de las imágenes de entrenamiento de cada dígito
// Cada columna de la matriz representa una imagen de entrenamiento

void Recognition::cargarMatrices(){

    //Se inicializan variables a usar

    QImage imagen;
    QString fileName = "../Digitos/images/";
    QString path;

    //Con este for, que va de 0 a 9, se calculan y guardan las matrices base de cada dígito

    for(int i=0; i<10; i++){

        //Matriz base del dígito actual
        TNT::Array2D<double> matrix(784,50);

        //Se cargan n imagenes de entrenamiento con este for, donde n es el límite del for

        for(int k=0; k<50; k++){

            //Matriz 784x1 para guardar los colores de los pixeles de cada imagen
            TNT::Array2D<double> digito(784,1);

            //Se obtiene la ruta de la imagen de entrenamiento actual
            path = fileName+QString::number(i)+"_"+QString::number(k)+".bmp";


            //Si se carga la imagen
            if(imagen.load(path)){

                //Se convierte a matriz
                digito = imageToMatrix(imagen);


                //Se guardan los valores de la matriz en la columna k de la matriz base
                for(int j=0; j<784; j++){

                    matrix[j][k]= digito[j][0];

                }
            }
        }

        //Finalmente, se guarda la matriz base actual en el arreglo matrices de la clase, en la posición correspondiente (0,1,..9)

        matrices[i] = matrix;

    }
}

// Método procesarMatrices:
// Este método se encarga de calcular una parte de la ecuación para calcular el residual
// Cada matriz base se llama An, donde n es el dígíto correspondiente
//
// Para cada An, se va a hacer la descomposición SVD, para retornar el valor de la operación
//
// (I -  Uk * transpuesta(Uk))
//

void Recognition::procesarMatrices(){

    //Se obtiene la identidad de 784x784

    TNT::Array2D<double> identity = identidad(784);

    //Con este for, se procesa cada una de las matrices base de los dígitos (0,1...9)

    for(int k=0; k<10; k++){

        //Se obtiene la matriz base en la posición k, es decir, del dígito k
        TNT::Array2D<double> A = matrices[k];

        //Se crea un objto SVD de JAMA para hacer la descomposición

        JAMA::SVD<double> descomposicion = JAMA::SVD<double>(A);

        //Se obtiene la matriz U de la descomposición

        descomposicion.getU(A);

        //Se obtiene el rango de A

        int rango = descomposicion.rank();

        //Se conservan sólo k filas de la matriz U en Uk, las que son LI

        TNT::Array2D<double> UK(784,rango);

        for(int i=0; i<A.dim1(); i++){

            for(int j=0; j<rango; j++){

                UK[i][j]=A[i][j];
            }

        }

        //Se hace la operacón ya mencionada  (I -  Uk * transpuesta(Uk))

        TNT::Array2D<double> resultado = (identity - matmult(UK,traspuesta(UK)));

        //Se guarda el resultado en el arreglo de matrices procesadas.
        //Se guarda en la posición k, es decir, la del dígito k.

        matricesProcesadas[k]= resultado;

    }


}







