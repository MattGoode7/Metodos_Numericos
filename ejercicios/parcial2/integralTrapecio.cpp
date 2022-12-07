/* Si hay errores al calcular, verificar por sobre todo el MAXROW */

#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#define MAXROW 100

using namespace std;

double F(double);
void parcialTrapecio();
double trapecio(double);

int main(){
    parcialTrapecio();
    return 0;
}

double F(double x){
    return 6*pow(x,2) + 1;
}

void parcialTrapecio(){
    int n, rows, fil;
    double a, b;
    double suma, h;
    FILE *readPtr;
    float k;

    readPtr = fopen("dataInt.txt", "r");
    fscanf(readPtr, "%d", &fil);
    rows = fil;

    double Fyi[MAXROW] = {0};
    double y[MAXROW] = {0};

    cout << "\nIngrese los limites de integracion" <<endl;
    cout << "a: ";
    cin  >> a;
    cout << "\nb: ";
    cin  >> b;

    n = 5;
    h = (double)(b-a)/n;

    y[0] = a;

    //Definimos un lazo nuevo para calcular los Fyi

    for (int i = 0; i <= n; i++)
    {
        Fyi[i] = trapecio(y[i]); //Llamamos al trapecio para calcular Fyi
        y[i + 1] = y[i] + h; //Aumentamos el intervalo
    }
    
    suma = Fyi[0] + Fyi[n]; //Suma de los elementos extremos

    for(int i=1; i < n; i++){
		suma += 2*Fyi[i];
	}
	suma *= (h/2);
    cout << "\n(TrapecioParcial) Valor de la integral: " <<  fixed << setprecision(7) << suma;
}

double trapecio(double b){
    int n;
    double a;
    double suma, h = 0;

    n = 5;
    a = 0;

    if(b == 0){
        return 0;
    }

    h = (double)(b-a)/n;
    suma = F(a)+F(b);

    for (int i = 1; i < n; i++)
    {
        suma += 2*F(a+i*h);
    }
    suma *= h/2;

    return suma;
}