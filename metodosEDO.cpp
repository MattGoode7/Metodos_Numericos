#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

double f(double x, double y);
double fp(double x, double y);
void euler();
void heun();
void puntoMedio();
int menu();

int main(){
    int op;
    do
    {
        op = menu();
        switch (op)
        {
        case 0:
            cout << "\nCierre del programa\n" << endl;
            break;
        case 1:
            euler();
            break;
        case 2:
            heun();
            break;
        case 3:
            puntoMedio();
            break;
        default:
            cout << "\nSe ha ingresado una opcion invalida" << endl;
            break;
        }
    } while (op != 0);
    
    return 0;
}

int menu(){
    int op;

    cout << "\nIngrese una opcion a realizar" << endl;
    cout << "\n1. Metodo de Euler" << endl;
    cout << "2. Metodo de Heun" << endl;
    cout << "3. Metodo del punto medio" << endl;
    cout << "\n0. Salir" << endl;
    cout << "\nOpcion: ";
    cin >> op;
    return op;
}

double f(double x, double y){
    return -2*x*y;
}

double fp(double x, double y){
    return -2*y;
}

void euler(){
    double x0, xf, y0, h, xn, yn, xv, yv;
    int n;

    string nombre = "euler.txt";
    ofstream archivo;
    archivo.open(nombre.c_str(), fstream::out);
    archivo << "xi\tyi" << endl;

    cout << "Ingrese x0, xf. y0" << endl;
    cout << "\nx0: ";
    cin  >> x0;
    cout << "\nxf: ";
    cin  >> xf;
    cout << "\ny0: ";
    cin  >> y0;

    cout << "\nIngrese la cantidad de intervalos" << endl;
    cout << "\nn: ";
    cin  >> n;

    h = (xf-x0)/n;

    xv = x0;
    yv = y0;

    for (int i = 0; i < n; i++)
    {
        yn = yv + h*f(xv,yv);
        xn = xv + h;
        
        archivo << xn << "\t" << yn << endl;

        xv = xn;
        yv = yn;
    }
}

void heun(){
    double x0, xf, y0, h, yt, xn, xv, yn, yv, e;
    int n;

    string nombre = "heun.txt";
    ofstream archivo;
    archivo.open(nombre.c_str(), fstream::out);
    archivo << "xi\tyi" << endl;

    cout << "Ingrese x0, xf. y0" << endl;
    cout << "\nx0: ";
    cin  >> x0;
    cout << "\nxf: ";
    cin  >> xf;
    cout << "\ny0: ";
    cin  >> y0;

    cout << "\nIngrese la cantidad de intervalos" << endl;
    cout << "\nn: ";
    cin  >> n;

    xv = x0;
    yv = y0;

    h = (xf-x0)/n;

    for (int i = 0; i < n; i++)
    {
        xn = xv + h;
        yt = yv + h*f(xv, yv);
        yn = yv + h*((f(xv,yv)+f(xn,yt))/2);
        e = fabs(fp(xn,yn)*pow(h,2)/2);
        
        archivo << xn << "\t" << yn << "\t" << e << endl;

        xv = xn;
        yv = yn;
    }
}

void puntoMedio(){
    double x0, xf, y0, h, e, ym, xv, yv, yn, xm;
    int n;

    string nombre = "puntoMedio.txt";
    ofstream archivo;
    archivo.open(nombre.c_str(), fstream::out);
    archivo << "xi\tyi" << endl;

    cout << "Ingrese x0, xf. y0" << endl;
    cout << "\nx0: ";
    cin  >> x0;
    cout << "\nxf: ";
    cin  >> xf;
    cout << "\ny0: ";
    cin  >> y0;
    cout << "\nIngrese la cantidad de intervalos" << endl;
    cout << "\nn: ";
    cin  >> n;

    h = (xf-x0)/n;

    xv = x0;
    yv = y0;

    for (int i = 0; i < n; i++)
    {
        ym = yv + (h/2)*f(xv,yv);
        xm = xv + h/2;
        yn = yv + h*f(xm,ym);
        xv = xv + h;

        
        archivo << xv << "\t" << yn << endl;

        yv = yn;
    }
}