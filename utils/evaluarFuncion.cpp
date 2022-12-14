/* Si hay errores al calcular, verificar por sobre todo el MAXROW */

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
/* RECORDAR CAMBIAR VALORES INICIALES Y CANTIDAD DE SUBINTERVALOS */
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#define MAXROW 10000

using namespace std;

double f(double x);
void funcionIntervalo();

int main(){
    cout << "Valuacion de puntos" << endl;
    funcionIntervalo();
    return 0;
}

///////////////////////////     FUNCIONES MATEMATICAS      ///////////////////////////////
double f(double x){
    return exp(sqrt(1 + x)) * log(1 + 2 * pow(x, 2));
}
//////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////                                //////////////////////////////
///////////////////////////     FUNCION PARA SACAR PUNTOS   ///////////////////////////////
///////////////////////////        (CARGA CON TABLA)       ///////////////////////////////

void funcionIntervalo(){
    string nombre = "puntos.txt";
    ofstream archivo;
    archivo.open(nombre.c_str(), fstream::out);
    archivo << "xi\t\tyi" << endl;

    double num = 0;
    double x1 = 0, x2 = 1;
    double n = 6;
    double h;
    h = (x2-x1)/n;

    num = f(x1);

    archivo << x1 << "\t\t" << num << endl;

    for (int i = 0; i < n; i++)
    {
        x1 = x1 + h;
        num = f(x1);
        archivo << x1 << "\t" << num;
        archivo << endl;
    }
    archivo.close();
}