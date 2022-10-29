/* Metodos Cerrados y Abiertos para localizacion de raices */

/*
    NOTAS:
    - Verificar que las funciones esten bien definidas
    - Verificar los valores iniciales que usen xv
    - Verificar que los limites esten bien definidos
    - Recordar despejar x en el metodo punto fijo (g(x))
    - Comprobar la tolerencia (si es necesario)
*/



#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

int menu();
void biseccion();
void regulaFalsi();
void puntoFijo();
void newRaph();
void secante();

double f(double);
double fp(double);
double g(double);
double gp(double);

int main(){

    int op;

    do{
        op = menu();
        switch (op)
        {
            case 0:
                cout << "Cierre del programa" << endl;
                break;
            case 1:
                biseccion();
                break;
            case 2:
                regulaFalsi();
                break;
            case 3:
                puntoFijo();
                break;
            case 4:
                newRaph();
                break;
            case 5:
                secante();
                break;
            default:
                cout << "Se ha ingresado una opcion invalida. Intentelo nuevamente" << endl;
                break;
        }
    }while(op != 0);
}

int menu(){

    int op;

    cout << "\nIngrese una opcion a realizar" << endl;
    cout << "\n1. Metodo de la biseccion" << endl;
    cout << "2. Metodo de falsa posicion (regula falsi)" << endl;
    cout << "3. Metodo del punto fijo" << endl;
    cout << "4. Metodo Newton-Raphson" << endl;
    cout << "5. Metodo de la Secante" << endl;

    cout << "\n0. Salir" << endl;

    cout << "\nOpcion: ";
    cin >> op;

    return op;
}

////////////////// FUNCIONES //////////////////////////////

double f(double x){
    double res;

    //Definir funcion
    res = 3*x + sin(x) - exp(x);

    return res;
}

double fp(double xv){
    //double fp = (f(xv + 0.01) - f(xv))/0.01;
    double fp = (f(xv + 0.01) - f(xv))/(0.01);

    return fp;
}

double g(double x){
    //x = x;
    //x = pow(x,5)-3*pow(x,3)-2*pow(x,2)+2;
    //x = cos(sin(x));

    //x = pow(x,x-cos(x));

    x = (-sin(x) + exp(x))/3;

    return x;
}

double gp(double x){
    //double gp = (g(x + 0.01) - g(x))/0.01;

    double gp = (g(x + 0.01) - g(x - 0.01))/(0.01);
    return gp;
}

////////////////// METODOS //////////////////////////////

void biseccion(){
    int i = 0;
    double a, b, c, cv;
    double tol, eprox, epor = 0;

    cout << "Ingrese el intervalo [a,b]" << endl;
    cout << "\na: ";
    cin >> a;
    cout << "b: ";
    cin >> b;

    cv = a;

    cout << "\nIngrese la tolerancia en decimales" << endl;
    cout << "Tolerancia: ";
    cin >> tol;

    do
    {
        //c = (a+b)/2;

        if (i == 0){
            c = (a + b) / 2;
            cv = a;
            eprox = fabs(c - cv);
            epor = ((fabs(c - cv)/c)*100);
        }

        if(((f(a)*f(c)) > 0)){
            a = c;
            cv = c;
            c = (a + b) / 2;
            eprox = fabs(c - cv);
            epor = ((fabs(c - cv)/c)*100);
        }
        else if (f(b)*f(c) > 0){
            b = c;
            cv = c;
            c = (a + b) / 2;
            eprox = fabs(c - cv);
            epor = ((fabs(c - cv)/c)*100);
        }
        else{
            break;
        } 
        i++;
    } while (eprox > tol);

    cout << "Numero de iteraciones: " << i << endl;
    cout << "Raiz: " << c << endl;
    cout << "Error aproximado: " << eprox << endl;
    cout << "Error porcentual: " << epor << endl;
}

void regulaFalsi(){
    int i = 0;
    double a, b, c, cv;
    double tol, eprox, epor;

    cout << "Ingrese el intervalo [a,b]" << endl;
    cout << "\na: ";
    cin >> a;
    cout << "b: ";
    cin >> b;

    cv = a;

    cout << "\nIngrese la tolerancia en decimales" << endl;
    cout << "Tolerancia: ";
    cin >> tol;

    do
    {
        c = (f(b)*a-f(a)*b)/(f(b) - f(a));

        if(f(a)*f(c) > 0){
            a = c;
        }
        if(f(b)*f(c) > 0){
            b = c;
        }

        if(((f(a)*f(c)) == 0) || ((f(b)*f(c)) == 0)){
            eprox = fabs(c - cv);
            epor = ((fabs(c - cv)/c)*100);
            i++;
            continue;
        }
        
        eprox = fabs(c - cv);
        epor = ((fabs(c - cv)/c)*100);
        cv = c;
        i++;

    } while (eprox > tol);

    cout << "Numero de iteraciones: " << i << endl;
    cout << "Raiz: " << c << endl;
    cout << "Error aproximado: " << eprox << endl;
    cout << "Error porcentual: " << epor << endl;
}

void puntoFijo(){
    double xn, xv = 0;
    double tol, eprox, epor;
    int i = 0;

    tol = pow(10, -8);

    cout << "Tolerancia: " << tol << endl;

    cout << "\nIngrese el valor inicial (Por defecto 0)" << endl;
    cout << "\nxv: ";
    cin >> xv;

    do
    {
        //La funcion diverge si su derivada en xv es mayor o igual a uno
        if(fabs(gp(xv)) >= 1 || i == 1000){
            cout << "\nAtencion: el resultado diverge\n" << endl;
            exit(EXIT_FAILURE);
        }

        xn = g(xv);

        eprox = fabs(xn - xv);
        epor = ((fabs(xn - xv)/xn)*100);

        xv = xn;
        i++;

    } while(eprox > tol);

    cout << "Numero de iteraciones: " << i << endl;
    cout << "Raiz: " << xn << endl;
    cout << "Error aproximado: " << eprox << endl;
    cout << "Error porcentual: " << epor << endl;
}

void newRaph(){
    double xn, xv = 0;
    double tol, eprox, epor;
    int i = 0;

    tol = pow(10,-8);

    cout << "Tolerancia: " << tol << endl;

    cout << "\nIngrese el valor de inicio" << endl;
    cout << "xv: ";
    cin  >> xv;

    do
    {
        if(fabs(fp(xv)) < 0.001){
            cout << "Atencion: f'(xv) es muy cercano a cero" << endl;
        }
        else{
            xn = xv - ((f(xv)/fp(xv)));

            eprox = fabs(xn - xv);
            epor = ((fabs(xn - xv)/xn)*100);

            xv = xn;
            i++;
        }
    } while (eprox > tol && i < 1000);

    if(i >=1000){
        cout << "\nSe ha excedido el numero maximo de iteraciones" << endl;
        exit(EXIT_FAILURE);
    }
    else{
        cout << "Numero de iteraciones: " << i << endl;
        cout << "Raiz: " << xn << endl;
        cout << "Error aproximado: " << eprox << endl;
        cout << "Error porcentual: " << epor << endl;
    }
    
}

void secante(){
    double xn, xv, xvv = 0;
    double tol, eprox, epor;
    int i = 0;

    tol = 0.0001;

    cout << "Tolerancia: " << tol << endl;

    cout << "\nIngrese valor para xv" << endl;
    cin  >> xv;

    cout << "\nIngrese el valor para xi - 1 (xvv)" << endl;
    cin  >> xvv;

    do
    {
        double aprox = (f(xvv) - f(xv)) / (xvv - xv);

        xn = xv - (f(xv)/aprox);

        eprox = fabs(xn - xv);
        epor = ((fabs(xn - xv)/xn)*100);

        xvv = xv;
        xv = xn;
        i++;

    } while (eprox > tol && i < 1000);

    if(i >=1000){
        cout << "\nSe ha excedido el numero maximo de iteraciones" << endl;
        exit(EXIT_FAILURE);
    }
    else{
        cout << "Numero de iteraciones: " << i << endl;
        cout << "Raiz: " << xn << endl;
        cout << "Error aproximado: " << eprox << endl;
        cout << "Error porcentual: " << epor << endl;
    }
    
}