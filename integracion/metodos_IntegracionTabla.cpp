/* Si hay errores al calcular, verificar por sobre todo el MAXROW */

#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#define MAXROW 10000

using namespace std;

double f(double x);
void trapecioTabla();
void simpsonTabla();
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
            trapecioTabla();
            break;
        case 2:
            simpsonTabla();
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
    cout << "1. Trapecio (tabla)" << endl;
    cout << "2. Simpson (tabla)" << endl;
    cout << "\n0. Salir" << endl;
    cout << "\nOpcion: ";
    cin >> op;
    return op;
}

void trapecioTabla(){
    int n, rows, fil;
    double a, b;
    double suma, h;
    FILE *readPtr;
    float k;

    readPtr = fopen("dataInt.txt", "r");
    fscanf(readPtr, "%d", &fil);
    rows = fil;

    /////////////////////////////////////////////////
    /////////////Carga de valores aca////////////////
    /////////////////////////////////////////////////
    double y[MAXROW];

    for (int i = 0; i < rows; i++) {
        fscanf(readPtr, "%f", &k);
        y[i] = k;
    }
    fclose(readPtr);
    ///////////////////////////////////////////////////

    cout << "\nIngrese los limites de integracion" <<endl;
    cout << "a: ";
    cin  >> a;
    cout << "\nb: ";
    cin  >> b;

    n = rows - 1;
    h = (double)(b-a)/n;

    suma = y[0] + y[rows-1];

    for(int i=1; i <= n-1; i++){
		suma += 2*y[i];
	}
	suma *= (h/2);
    cout << "\n(TrapecioTabla) Valor de la integral: " <<  fixed << setprecision(7) << suma;
}


void simpsonTabla(){
    int n, rows, fil;
    double a, b;
    double suma, h;
    FILE *readPtr;
    float k;

    readPtr = fopen("dataInt.txt", "r");
    fscanf(readPtr, "%d", &fil);
    rows = fil;

    /////////////////////////////////////////////////
    /////////////Carga de valores aca////////////////
    /////////////////////////////////////////////////
    double y[MAXROW];

    for (int i = 0; i < rows; i++) {
        fscanf(readPtr, "%f", &k);
        y[i] = k;
    }
    fclose(readPtr);
    /////////////////////////////////////////////////

    cout << "\nIngrese los limites de integracion" <<endl;
    cout << "a: ";
    cin  >> a;
    cout << "\nb: ";
    cin  >> b;
    
    n = rows - 1;

    if(n%2 != 0){
        cout << "ADVERTENCIA: el numero de subintervalos no es par" << endl;
        return;
    }

    h = (b-a)/n;
    suma = y[0] + y[n];

    for (int i = 1; i < n / 2; i++) {
        suma += 2 * y[2 * i] + 4 * y[2 * i - 1];
    }

    suma = (h/3) * (suma + 4 * y[n - 1]);
    cout << "\n(SimpsonTabla) Valor de la integral: " <<  fixed << setprecision(10) << suma << endl;
}