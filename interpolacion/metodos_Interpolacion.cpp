#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <iostream>

#define MAXC 2
#define MAXC2 10
#define MAXR 10

using namespace std;

void nodos(double[MAXR][MAXC], int*);
void lagrange(double[MAXR][MAXC], int);
void polynomial (double[MAXR][MAXC], int);
void printNodes(double[MAXR][MAXC], int);

void print(double [MAXR][MAXC2], double [MAXR], int, int);
void triangulacion(double [MAXR][MAXC2], double [MAXR], int, int);
void retrosustitucion (double [MAXR][MAXC2], double [MAXR], double [MAXR], int, int);
void pivote (double [MAXR][MAXC2], double [MAXR], int, int, int);

double f(double x);

int main(){

    int rows;
    double n[MAXR][MAXC];

    nodos(n, &rows);
    printNodes(n, rows);

    lagrange(n, rows);
    polynomial(n, rows);
}

///////////////////////////Funciones//////////////////////////////

double f(double x){
    return -26.961 + 35.4439 * x;
}

/////////////////////////Funciones para matrices//////////////////////////

void print(double m[MAXR][MAXC2], double b[MAXR], int rows, int columns){
    double diagonal = 1;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            printf("%.1lf ",m[i][j]);
        }
        printf("%.1lf",b[i]);
        diagonal = diagonal * m[i][i];
        printf("\n");
    }
    printf("\nDiagonal: %.1lf\n", diagonal);
}

//////////////////////////Interpolaciones///////////////////////////////////

void printNodes(double n[MAXR][MAXC], int rows){
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0 ; j < 2; j++)
        {
            printf("%.1lf ",n[i][j]);
        }
        printf("\n");
    }
}

void nodos(double n[MAXR][MAXC], int *rows){

    /*
    Metodo para calcular los valores y de los nodos a mano

        cout << "Ingrese los valores de x" << endl;

        for (int i = 0; i < rows; i++)
        {
            cout << "X" << i << ":";
            cin >> n[i][0];
            n[i][1] = f(n[i][0]);
        }

    */

    FILE *readPtr;
    float k;
    char c;

    readPtr = fopen("nodes.txt", "r");
    while((c = fgetc(readPtr)) != EOF)
    {
        if(c == '\n'){
            *rows += 1; //cuenta el numero de filas
		}
    }

    fclose(readPtr); //reinicia el puntero
    readPtr = fopen("nodes.txt","r");

    //Carga de los datos en la matriz m y b
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < 2; j++) {
            fscanf(readPtr, "%f", &k);
            n[i][j] = k;
        }
    }
    fclose(readPtr);
}

void lagrange(double n[MAXR][MAXC], int rows){
    double producto;
    double suma = 0;
    double error = 0;
    double x;

    cout << "\nIngrese el valor a interpolar" << endl;
    cout << "x: ";
    cin  >> x;

    //Polinomio de Lagrange
    for (int i = 0; i < rows; i++)
    {
        producto = 1;
        for (int k = 0; k < rows; k++)
        {
            if(i!=k){
                producto = producto * ((x - n[i][0])/(n[k][0] - n[i][0]));
            }
        }
        suma = suma + (n[i][1]*producto);
    }

    error = fabs(f(x)-suma);
    
    cout << "Valor del polinomio: " << suma << endl;
    cout << "Error: " << error << endl;
}

void polynomial (double m[MAXR][MAXC], int rows){
    double A[MAXR][MAXC2];
    double B[MAXR];
    double x[MAXR];

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < rows;j++){
            A[i][j] = pow(m[i][0], j);
            cout << "Elemento " << i << j << " = " << A[i][j] << endl;
        }
        B[i] = m[i][1];
    }
    cout << "\nMatriz antes de triangular" << endl;
    print(A, B, rows, rows);

    cout << "\nMatriz despues de triangular" << endl;
    triangulacion(A, B, rows, rows);
    retrosustitucion(A, B, x, rows, rows);

}

void triangulacion(double m[MAXR][MAXC2], double b[MAXR], int rows, int columns){
    
    for (int i = 0; i < rows-1; ++i) {
        pivote(m, b, rows, columns, i);
        for (int j = i+1; j < rows; ++j) {
            double factor = -m[j][i]/m[i][i];
            for (int k = 0; k < columns; ++k) {
                m[j][k] = m[i][k] * factor + m[j][k];
            }
            b[j] = b[i] * factor + b[j];
        }
    }
    print(m, b, rows, columns);
}

void pivote(double m[MAXR][MAXC2], double b[MAXR], int rows, int columns, int i){
    
    double tol = pow(10, -3);

    if(fabs(m[i][i]) < tol){
        for (int j = i+1; j < rows; ++j) 
        {
            if(fabs(m[j][i])>fabs(m[i][i]))
            {
                for (int k = i; k < columns; ++k) 
                {
                    double swap = m[i][k];
                    m[i][k] = m[j][k];
                    m[j][k] = swap;
                }
                double swap = b[i];
                b[i] = b[j];
                b[j] = swap;
            }
        }
    }
}

void retrosustitucion (double m[MAXR][MAXC2], double b[MAXR], double x[MAXR], int rows, int columns){
    double value;

    value = b[rows-1]/m[rows-1][columns-1];
    x[rows-1] = value;

    for (int i = rows-2; i >= 0; --i) {
        double sum = 0;
        for (int j = i+1; j < columns; ++j) {
            sum = sum + m[i][j] * x[j];
        }
        value = (b[i] - sum) / m[i][i];
        x[i] = value;
    }
    
    cout << "\nPolinomio interpolador" << endl;

    for (int i = 0; i < rows; ++i) {
        if(i == 0){
            cout << x[i] << " + ";
        }
        else{
            (i != rows - 1) ? (cout << x[i] << ".x^" << i << " + ") : (cout << x[i] << ".x^" << i);
        }
    }
}