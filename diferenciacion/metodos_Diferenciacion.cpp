#include <math.h>
#include <iostream>
#include <fstream>
#define MAXROW 10000

using namespace std;

void firstOrder(double, double, double, int);
void secondOrder(double, double, double, int);
void thirdOrder(double, double, double, int);
void fourthOrder(double, double, double, int);
int menu();


double f(double x){
    return 3*pow(x,3) + 1;
}

int main(){
    double xc, xf, h;
    int n;
    int op;

    cout << "Ingrese x0 y xf" << endl;
    cout << "\nx0: ";
    cin  >> xc;
    cout << "\nxf: ";
    cin  >> xf;

    cout << "\nIngrese la cantidad de intervalos" << endl;
    cout << "\nn: ";
    cin  >> n;

    h = (xf-xc)/n;

    do
    {
        op = menu();

        switch (op)
        {
        case 0:
            cout << "Fin del programa" << endl;
            break;
        case 1:
            firstOrder(xc, xf, h, n);
            break;
        case 2:
            secondOrder(xc, xf, h, n);
            break;
        case 3:
            thirdOrder(xc, xf, h, n);
            break;
        case 4:
            fourthOrder(xc, xf, h, n);
            break;
        default:
            cout << "Se ha ingresado una opcion invalida" << endl;
            break;
        }
    } while (op != 0);
    
    return 0;
}

int menu(){
    int op;

    cout << "Ingrese el orden de derivada" << endl;

    cout << "\n1. Primer orden" << endl;
    cout << "2. Segundo orden" << endl;
    cout << "3. Tercer orden" << endl;
    cout << "4. Cuarto orden" << endl;
    cout << "\n0. Salir" << endl;

    cout << "\nOpcion: ";
    cin  >> op;

    return op;
}

void firstOrder(double xc, double xf, double h, int n){
    double x, fp;
    string nombre = "primerOrden.txt";
    ofstream archivo;
    archivo.open(nombre.c_str(), fstream::out);

    archivo << "xi\tyi" << endl;

    //Adelante
    for (int i = 0; i < 2; i++)
    {
        x = xc + i*h;
        fp = (-f(x+2*h)+4*f(x+h)-3*f(x))/(2*h);

        archivo << x << "\t" << fp << endl;
    }

    //Centro
    for (int i = 2; i < n-1; i++)
    {
        x = xc + i*h;
        fp = ((-f(x+2*h)+8*f(x+h)-8*f(x-h)+f(x-2*h)))/(12*h);
        archivo << x << "\t" << fp << endl;
    }
    
    //Atras
    for (int i = n-1; i < n+1; i++)
    {
        x = xc + i*h;
        fp = ((3*f(x)-4*f(x-h)+f(x-2*h)))/(2*h);
        archivo << x << "\t" << fp << endl;
    }
    cout << "\nArchivo generado" << endl;
    archivo.close();
} 

void secondOrder(double xc, double xf, double h, int n){
    double x, fp;
    string nombre = "segundoOrden.txt";
    ofstream archivo;
    archivo.open(nombre.c_str(), fstream::out);

    //Adelante
    for (int i = 0; i < 3; i++)
    {
        x = xc + i*h;
        fp = (-f(x+3*h)+4*f(x+2*h)-5*f(x+h)+f(x))/(pow(h,2));

        archivo << x << "\t" << fp << endl;
    }

    //Centro
    for (int i = 2; i < n-1; i++)
    {
        x = xc + i*h;
        fp = (-f(x+2*h)+16*f(x+h)-30*f(x)+16*f(x-h)-f(x-2*h))/(12*pow(h,2));
        archivo << x << "\t" << fp << endl;
    }
    
    //Atras
    for (int i = n-1; i < n+1; i++)
    {
        x = xc + i*h;
        fp = (2*f(x)-5*f(x-h)+4*f(x-2*h)-f(x-3*h))/(pow(h,2));
        archivo << x << "\t" << fp << endl;
    }
    cout << "\nArchivo generado" << endl;
    archivo.close();
}

void thirdOrder(double xc, double xf, double h, int n){
    double x, fp;
    string nombre = "thirdOrden.txt";
    ofstream archivo;
    archivo.open(nombre.c_str(), fstream::out);

    //Adelante
    for (int i = 0; i < 3; i++)
    {
        x = xc + i*h;
        fp = (-3*f(x+4*h)+14*f(x+3*h)-24*f(x+2*h)+18*f(x+h)-5*f(x))/(2*pow(h,3));

        archivo << x << "\t" << fp << endl;
    }

    //Centro
    for (int i = 3; i < n-2; i++)
    {
        x = xc + i*h;
        fp = (-f(x+3*h)+8*f(x+2*h)-13*f(x+h)+13*f(x-h)-8*f(x-2*h)+f(x-3*h))/(8*pow(h,3));
        archivo << x << "\t" << fp << endl;
    }
    
    //Atras
    for (int i = n-2; i < n+1; i++)
    {
        x = xc + i*h;
        fp = (5*f(x)-18*f(x-h)+24*f(x-2*h)-14*f(x-3*h)+3*f(x-4*h))/(2*pow(h,3));
        archivo << x << "\t" << fp << endl;
    }
    cout << "\nArchivo generado" << endl;
    archivo.close();
}

void fourthOrder(double xc, double xf, double h, int n){
    double x, fp;
    string nombre = "fourthOrden.txt";
    ofstream archivo;
    archivo.open(nombre.c_str(), fstream::out);

    //Adelante
    for (int i = 0; i < 3; i++)
    {
        x = xc + i*h;
        fp = (-2*f(x+5*h)+11*f(x+4*h)-24*f(x+3*h)+26*f(x+2*h)-14*f(x+h)+3*f(x))/(pow(h,4));

        archivo << x << "\t" << fp << endl;
    }
    
    //Centro
    for (int i = 3; i < n-2; i++)
    {
        x = xc + i*h;
        fp = (-f(x+3*h)+12*f(x+2*h)-39*f(x+h)+56*f(x)-39*f(x-h)+12*f(x-2*h)-f(x-3*h))/(6*pow(h,4));
        archivo << x << "\t" << fp << endl;
    }

    //Atras
    for (int i = n-2; i < n+1; i++)
    {
        x = xc + i*h;
        fp = (3*f(x)-14*f(x-h)+26*f(x-2*h)-24*f(x-3*h)+11*f(x-4*h)-2*f(x-5*h))/(pow(h,4));
        archivo << x << "\t" << fp << endl;
    }
    cout << "\nArchivo generado" << endl;
    archivo.close();
}
