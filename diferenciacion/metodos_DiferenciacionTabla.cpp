#include <math.h>
#include <iostream>
#include <fstream>
#define MAXROW 10000

using namespace std;

void firstOrderTabla();
int menu();

double f(double x){
    return 3*pow(x,3) + 1;
}

int main(){
    cout << "Derivada primera (Tabla)" << endl;
    firstOrderTabla();
    return 0;
}

void firstOrderTabla(){
    string nombre = "firstOrderTable.txt";
    ofstream archivo;
    archivo.open(nombre.c_str(), fstream::out);

    double xc, xf, h;
    int n, rows, fil;
    double a, b;
    double suma;
    FILE *readPtr;
    float k;
    double fp;

    readPtr = fopen("dataDif.txt", "r");
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

    cout << "\nIngrese x0 y xf" << endl;
    cout << "\nx0: ";
    cin  >> xc;
    cout << "\nxf: ";
    cin  >> xf;

    n = rows - 1;

    h = (xf-xc)/n;

    for (int i = 0; i < 2; ++i) {
        fp = (-y[i + 2] + 4 * y[i + 1] - 3 * y[i]) / (2 * h);
        archivo << fp << endl;
    }

    for (int i = 2; i < n - 1; ++i) {
        fp = (-y[i + 2] + 8 * y[i + 1] - 8 * y[i - 1] + y[i - 2]) / (12 * h);
        archivo << fp << endl;
    }

    for (int i = n - 1; i < n + 1; ++i) {
        fp = (3 * y[i] - 4 * y[i - 1] + y[i - 2]) / (2 * h);
        archivo << fp << endl;
    }
}