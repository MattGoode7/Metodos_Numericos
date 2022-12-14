/* Si hay errores al calcular, verificar por sobre todo el MAXROW */

//////////////// ESTE ES EL METODO PARA LA INTEGRAL QUE MEZCLABA VELOCIDAD  Y PUNTOS EN X

#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#define MAXROW 10000

using namespace std;

double f(double x);
double f(double x, double v);
double integral(double [MAXROW], double [MAXROW], double, double, int);
double integral(double [MAXROW], double [MAXROW], double, double, int, double);
void trapecio();
void simpson();
void glegendre();
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
            trapecio();
            break;
        case 2:
            simpson();
            break;
        case 3:
            glegendre();
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
    cout << "\n1. Metodo del trapecio" << endl;
    cout << "2. Metodo de Simpson" << endl;
    cout << "3. Cuadratura de Gauss-Legendre" << endl;
    cout << "\n0. Salir" << endl;
    cout << "\nOpcion: ";
    cin >> op;
    return op;
}

////////////////////////////                                //////////////////////////////
///////////////////////////     FUNCIONES MATEMATICAS      ///////////////////////////////
///////////////////////////                                ///////////////////////////////

double f(double x, double v){
    return 10 * exp(0.05 * v * pow(x,0.02));
}

double integral(double c[MAXROW], double x[MAXROW], double a, double b, int puntos){
    double integ = 0;

    for (int i = 0; i < puntos; i++)
    {
        integ += (c[i]*f(((b-a)*x[i]+(b+a))/2));
    }
    integ *= ((b-a)/2);
    return integ;    
}

double integral(double c[MAXROW], double x[MAXROW], double a, double b, int puntos, double v){
    double integ = 0;

    for (int i = 0; i < puntos; i++)
    {
        integ += (c[i]*f(((b-a)*x[i]+(b+a))/2),v);
    }
    integ *= ((b-a)/2);
    return integ;    
}
//////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////                                //////////////////////////////
///////////////////////////     METODOS DE INTEGRACION     ///////////////////////////////
///////////////////////////                                ///////////////////////////////

void trapecio(){
    int n;
    double a, b;
    double suma, h = 0, suma2 = 0;
    double x[MAXROW] = {0};

    cout << "\nIngrese los limites de integracion" <<endl;
    cout << "a: ";
    cin  >> a;
    cout << "\nb: ";
    cin  >> b;
    cout << "\nIngrese el numero de subintervalos" << endl;
    cout << "n: ";
    cin  >> n;

    suma = f(a)+f(b);

    h = (double)(b-a)/n;

    for (int i = 1; i < n; i++)
    {
        suma += 2*f(a+i*h);
    }
    suma *= h/2;
    cout << "\n(Trapecio) Valor de la integral: " <<  fixed << setprecision(7) << suma;
}

void simpson(){
    int n;
    double a, b;
    double suma, h, x = 0;

    cout << "\nIngrese los limites de integracion" <<endl;
    cout << "a: ";
    cin  >> a;
    cout << "\nb: ";
    cin  >> b;
    do
    {
        cout << "\nIngrese el numero de subintervalos (debe ser par)" << endl;
        cout << "n: ";
        cin  >> n;
        if(n%2 != 0) cout << "\nEl numero de subintervalos debe ser par!" << endl;
    } while (n%2 != 0);

    h = (b-a)/n;
    suma = f(a)+f(b);

    for (int i = 1; i < (n/2); i++)
    {
        x = a + 2*i*h;
        suma = suma + 2*f(x) + 4*f(x-h);
    }
    suma = (suma + 4*f(b-h))*(h/3);
    cout << "\n(Simpson) Valor de la integral: " <<  fixed << setprecision(40) << suma << endl;
}

void glegendre(){
    double a,b;
    double c[6];
    double x[6];
    double integ;
    double v = 0;
    double c2[2] = {1,1};
    double x2[2] = {-0.577350269, 0.577350269};
    double c3[3] = {0.5555556, 0.8888889, 0.5555556};
    double x3[3] = {-0.774596669, 0.0, 0.774596669};
    double c4[4] = {0.3478548, 0.6521452, 0.6521452, 0.3478548};
    double x4[4] = {-0.861136312, -0.339981044, 0.339981044, 0.861136312};
    double c5[5] = {0.2369269, 0.4786287, 0.5688889, 0.4786287, 0.2369269};
    double x5[5] = {-0.906179846, -0.538469310, 0.0, 0.538469310, 0.906179846};
    double c6[6] = {0.1713245, 0.3607616, 0.4679139, 0.4679139, 0.3607616, 0.1713245};
    double x6[6] = {-0.932469514, -0.661209386,-0.238619186, 0.238619186, 0.661209386, 0.932469514};
    int puntos;

    cout << "Ingrese a y b" << endl;
    cout << "\na:";
    cin  >> a;
    cout <<"b:";
    cin  >> b;

    cout << "\nIngrese la cantidad de puntos (entre 2 y 6)" << endl;
    cout << "\nPuntos: ";
    cin  >> puntos;
    
    switch (puntos)
    {
    case 0:
        cout << "\nFin del programa" << endl;
        break;
    case 2:
        integ = integral(c2,x2,a,b,puntos);
        cout << "\n(Gauss-Legendre) Valor de la integral: " << fixed << setprecision(10) << integ << endl;
        break;
    case 3:

    while (v != 50)
        {
        integ = integral(c3,x3,a,b,puntos,v);
        cout << "\n(Gauss-Legendre) Valor de la integral: " << fixed << setprecision(10) << integ << endl;
        v+= 2.5;
        }
        break;
    case 4:
        integ = integral(c4,x4,a,b,puntos);
        cout << "\n(Gauss-Legendre) Valor de la integral: " << fixed << setprecision(10) << integ << endl;
        break;
    case 5: 
        integ = integral(c5,x5,a,b,puntos);
        cout << "\n(Gauss-Legendre) Valor de la integral: " << fixed << setprecision(10) << integ << endl;
        break;
    case 6:
        integ = integral(c6,x6,a,b,puntos);
        cout << "\n(Gauss-Legendre) Valor de la integral: " << fixed << setprecision(10) << integ << endl;
        break;
    default:
        cout << "\n(Gauss-Legendre) Valor de la integral: " << fixed << setprecision(10) << integ << endl;
        break;
    
    }

}