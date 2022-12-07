/* Metodo de eliminacion Gaussiana */

    /*
        Primero se leen los datos del .txt
        Se imprimen por pantalla
        Se triangula inferior la matriz y luego se utiliza la retrosustitucion para dar el conjunto solucion

        NOTA:
        - Definir primeramente la matriz en el data.txt, con un salto mas
        - Existe la posibilidad de que el programa se rompa cuando escanea las filas
    */

#include <math.h>
#include <iostream>

/* Valores constantes para filas y columnas */

#define MAXCOL 15
#define MAXROW 15

using namespace std;

/* Funciones */

void read(double [MAXROW][MAXCOL], double [MAXROW], int *, int *);
void print(double [MAXROW][MAXCOL], double [MAXROW], int, int);
void triangulacion(double [MAXROW][MAXCOL], double [MAXROW], int, int);
void retrosustitucion (double [MAXROW][MAXCOL], double [MAXROW], double [MAXROW], int, int);
void banda(double [MAXROW][MAXCOL], double, int, int);
void save(double [MAXCOL][MAXROW], double [MAXROW]);

int main(){

    /* Variables */

    double m[MAXROW][MAXCOL];
    double b[MAXROW];
    double x[MAXROW];
    int rows = 0;
    int columns = 0;

    read(m, b, &rows, &columns);

    cout << "\nMatriz ampliada" << endl;
    print(m, b, rows, columns);
    triangulacion(m, b, rows, columns);
    retrosustitucion(m, b, x, rows, columns);

}

void read(double m[MAXROW][MAXCOL], double b[MAXROW], int *rows, int *columns){
    
    /* Variables */

    FILE *fp;
    char c;
    float k;

    /* Abre el archivo y comprueba que no este vacio */
    fp = fopen("data.txt","r");

    if ( fp == NULL ){
        puts ( "No se puede abrir el archivo");
        EXIT_FAILURE;
    }

    /* Cuenta el numero de filas */

    while((c = fgetc(fp)) != EOF){
        if(c == '\n') *rows+= 1; 
    }
    *columns = *rows;

    /* Reinicia el puntero */
    fclose(fp);
    fp = fopen("data.txt","r");

    /* Carga los datos en la matriz m y b */
    for(int i = 0; i < *rows; i++) {
		for (int j = 0; j < *columns; j++){
            fscanf(fp,"%f",&k);
            m[i][j] = k;
        }
            fscanf(fp,"%f",&k);
            b[i] = k;
	}
    fclose(fp);
}

void print(double m[MAXROW][MAXCOL], double b[MAXROW], int rows, int columns){
    
    /* Impresion de la matriz ampliada en pantalla */

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << m[i][j] << "\t";
        }
        cout << b[i] << endl;
    }
}

void triangulacion(double m[MAXROW][MAXCOL], double b[MAXROW], int rows, int columns){
    double factor, swap = 0;
    double tol = pow(10, -3);
    bool isPivot = false;

    /* Pivoteo parcial */
    for (int i = 0; i < rows-1; i++) {
        if(abs(m[i][i]) < tol){
            isPivot = true;
            for (int l = i + 1; l < rows; l++){
                if(abs(m[l][i]) > abs(m[i][l])){
                    for (int n = 0; n < columns; n++){
                        swap = m[i][n];
                        m[i][n] = m[l][n];
                        m[l][n] = swap;
                    }
                    swap = b[i];
                    b[i] = b[l];
                    b[l] = swap;
                }
            }  
        }

        if(isPivot){
            cout << "\nSe realizo un pivoteo parcial" << endl;
        }

        for (int j = i+1; j < rows; j++) {
            factor = -m[j][i]/m[i][i];
                for (int k = 0; k < columns; k++) {
                m[j][k] = m[i][k] * factor + m[j][k];
            }
                b[j] = b[i] * factor + b[j];
        }
    }
    cout << "\nMatriz ampliada triangulada" << endl;
    print(m, b, rows, columns);
}

void retrosustitucion (double m[MAXROW][MAXCOL], double b[MAXROW], double x[MAXROW], int rows, int columns){
    double value = 0;

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

    cout << "\nSoluciones" << endl;

    for (int i = 0; i < rows; ++i) {
        cout << "x" << (i + 1) << " = " << x[i] << endl;
    }
}
