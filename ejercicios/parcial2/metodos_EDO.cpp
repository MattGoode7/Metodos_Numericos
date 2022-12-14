#include <math.h>
#include <iostream>
#include <fstream>
#define MAXROW 100

using namespace std;

double f(double x, double y);
double fp(double x, double y);
void euler();
void heun();
void puntoMedio();
void rk4();
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
        case 4:
            rk4();
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
    cout << "4. Metodo clasico de Runge-Kutta" << endl;
    cout << "\n0. Salir" << endl;
    cout << "\nOpcion: ";
    cin >> op;
    return op;
}

double f(double x, double y){
    return 3*sqrt(y);
}

double fp(double x, double y){
    return -2*y;
}

void euler(){
    int n;
    double xf, h, xp, yp, aux;
    double x[MAXROW], y[MAXROW];

    string nombre = "euler.txt";
    ofstream archivo;
    archivo.open(nombre.c_str(), fstream::out);
    archivo << "xi\tyi" << endl;

    cout << "Ingrese x0, xf. y0" << endl;
    cout << "\nx0: ";
    cin  >> x[0];
    cout << "\nxf: ";
    cin  >> xf;
    cout << "\ny0: ";
    cin  >> y[0];

    cout << "\nIngrese la cantidad de intervalos" << endl;
    cout << "\nn: ";
    cin  >> n;

    h = (xf-x[0])/n;

    //Calculo del y1
    // for (int i = 0; i < n; i++)
    // {
    //     y[i+1] = y[i] + h*f(x[i],y[i]);
    //     x[i+1] = x[i] + h;
    //     archivo << x[i+1] << "\t" << y[i+1] << endl;
    // }

    //Modificacion Recuperatorio

    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            y[i + 1] = y[i] + h * f(x[i], y[i]);
            x[i + 1] = x[i] + h;
            archivo << x[i + 1] << "\t" << y[i + 1] << "\t" << endl;
        } else {
            x[i + 1] = x[i] + h;
            y[i + 1] = y[i] + h * (2 * f(x[i], y[i]) - f(x[i - 1], y[i - 1]));
            archivo << x[i + 1] << "\t" << y[i + 1] << "\t" << endl;
        }
    }
    

    archivo.close();
}

void heun(){
    int n;
    double xf, h;
    double x[MAXROW], y[MAXROW], yt; 

    string nombre = "heun.txt";
    ofstream archivo;
    archivo.open(nombre.c_str(), fstream::out);
    archivo << "xi\tyi" << endl;

    cout << "Ingrese x0, xf. y0" << endl;
    cout << "\nx0: ";
    cin  >> x[0];
    cout << "\nxf: ";
    cin  >> xf;
    cout << "\ny0: ";
    cin  >> y[0];

    cout << "\nIngrese la cantidad de intervalos" << endl;
    cout << "\nn: ";
    cin  >> n;

    h = (xf-x[0])/n;

    for (int i = 0; i < n; i++)
    {
        x[i+1] = x[i] + h;
        yt = y[i] + h*f(x[i],y[i]);
        y[i+1] = y[i] + h*((f(x[i],y[i])+f(x[i+1],yt))/2);
        
        archivo << x[i+1] << "\t" << y[i+1] << endl;
    }
    archivo.close();
}

void puntoMedio(){
    int n;
    double xf, h;
    double x[MAXROW], y[MAXROW], ym, xm; 

    string nombre = "puntoMedio.txt";
    ofstream archivo;
    archivo.open(nombre.c_str(), fstream::out);
    archivo << "xi\tyi" << endl;

    cout << "Ingrese x0, xf. y0" << endl;
    cout << "\nx0: ";
    cin  >> x[0];
    cout << "\nxf: ";
    cin  >> xf;
    cout << "\ny0: ";
    cin  >> y[0];

    cout << "\nIngrese la cantidad de intervalos" << endl;
    cout << "\nn: ";
    cin  >> n;

    h = (xf-x[0])/n;

    for (int i = 0; i < n; i++)
    {
        xm = x[i] + h/2;
        ym = y[i] + h/2*f(x[i],y[i]);
        y[i+1] = y[i] + h*f(xm,ym);
        x[i+1] = x[i] + h;
        archivo << x[i+1] << "\t" << y[i+1] << endl;
    }
    archivo.close(); 
}

void rk4(){
    int n;
    double xf, h;
    double x[MAXROW], y[MAXROW], k[5]; 

    string nombre = "rungeKutta.txt";
    ofstream archivo;
    archivo.open(nombre.c_str(), fstream::out);
    archivo << "xi\tyi" << endl;

    cout << "Ingrese x0, xf. y0" << endl;
    cout << "\nx0: ";
    cin  >> x[0];
    cout << "\nxf: ";
    cin  >> xf;
    cout << "\ny0: ";
    cin  >> y[0];

    cout << "\nIngrese la cantidad de intervalos" << endl;
    cout << "\nn: ";
    cin  >> n;

    h = (double)(xf-x[0])/n;

    for (int i = 0; i < n; i++)
    {
        k[1] = f(x[i],y[i]);
        k[2] = f(x[i] + h, y[i] + k[1] * h/2);
        k[3] = f(x[i] + h/2, y[i] + k[2] * h/2);
        k[4] = f(x[i] + h, y[i] + k[3]*h);

        y[i+1] = y[i] + h*(k[1]+2*k[2]+2*k[3]+k[4])/6;
        x[i+1] = x[i] + h;
    
        archivo << x[i+1] << "\t" << y[i+1] << endl;
    }
    archivo.close(); 
}