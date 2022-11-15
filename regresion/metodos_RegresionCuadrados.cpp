#include <iostream>
#include <math.h>

#define MAXCOL 2
#define MAXCOLM 10
#define MAXROW 10

void read(double[MAXROW][MAXCOL], int *);
void printNodes(double[MAXROW][MAXCOL], int);
void build(double [MAXROW][MAXCOL], double [MAXROW][MAXCOLM], double [MAXROW], int, int);
void error (double [MAXROW], double [MAXROW][MAXCOL], int, int);
void triangulation(double [MAXROW][MAXCOLM], double [MAXROW], int, int);
void retrosustitucion(double [MAXROW][MAXCOLM], double [MAXROW], double [MAXROW], int, int);
void polynomial (double [MAXROW], int);
void print(double [MAXROW][MAXCOLM], double [MAXROW], int, int);

using namespace std;

int main(int argc, char *argv[]) {
    int rows, p;
    double nodes[MAXROW][MAXCOL];
    double m[MAXROW][MAXCOLM];
    double b[MAXROW];
    double x[MAXROW];

    cout << "Ingrese el grado del polinomio" << endl;
    cout << "\nGrado: ";
    cin  >> p;

    p = p+1; //Correccion por no consideracion del termino a0

    read(nodes, &rows);
    printNodes(nodes, rows);
    build(nodes, m, b, rows, p);

    cout << "\nMatriz ampliada" << endl;
    print(m, b, p, p);

    cout << "\nMatriz triangulada" << endl;
    triangulation(m, b, p, p);
    retrosustitucion(m, b, x, p, p);

    error(x, nodes, p, rows);
    polynomial(x, p);
}

void read(double m[MAXROW][MAXCOL], int *rows) {
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

    /* Reinicia el puntero */
    fclose(fp);
    fp = fopen("data.txt","r");

    /* Carga los datos en la matriz m y b */
    for(int i = 0; i < *rows; i++) {
		for (int j = 0; j < MAXCOL; j++){
            fscanf(fp,"%f",&k);
            m[i][j] = k;
        }
	}
    fclose(fp);
}

void printNodes(double m[MAXROW][MAXCOL], int rows) {
    
    cout << "\nNodos" << endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < MAXCOL; j++) {
            cout << m[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void print(double m[MAXROW][MAXCOLM], double b[MAXROW], int rows, int columns) {
    /* Impresion de la matriz ampliada en pantalla */

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << m[i][j] << "\t";
        }
        cout << b[i] << endl;
    }
}

void build(double n[MAXROW][MAXCOL], double m[MAXROW][MAXCOLM], double b[MAXROW], int rows, int p) {

    double sum;
    double sumx;

    for (int i = 0; i < p; ++i) {
        sum = 0;
        for (int j = 0; j < rows; ++j) {
            sum = sum + pow(n[j][0], i) * n[j][1];
        }
        b[i] = sum;
        for (int j = 0; j < p; ++j) {
            sumx = 0;
            for (int k = 0; k < rows; ++k) {
                sumx = sumx + pow(n[k][0], i + j);
            }
            m[i][j] = sumx;
        }
    }

}

void error (double a[MAXROW], double n[MAXROW][MAXCOL], int p, int rows){
    double yb = 0;
    double e = 0;
    double ecm;
    double st = 0;
    double r;

    for (int i = 0; i < rows; ++i) {
        double sum = 0;
        for (int j = 0; j < p; ++j) {
            sum = sum + a[j]*pow(n[i][0], j);
        }
        e = e + pow(n[i][1]-sum, 2);
        yb = yb + n[i][1];
    }
    yb = yb/(rows+1);
    for (int i = 0; i < rows; ++i) {
        st = st + pow(n[i][1]-yb, 2);
    }
    r = sqrt(fabs(e-st)/st);
    ecm = sqrt(e/rows);
    printf("El error es de: %lf\n", e);
    printf("El error cuadratico medio es de: %lf\n", ecm);
    printf("El coeficiente de correlacion es: %lf\n", r);
}

void triangulation(double m[MAXROW][MAXCOLM], double b[MAXROW], int rows, int columns) {
    double factor, swap = 0;
    double tol = pow(10, -3);

    /* Pivoteo parcial */
    for (int i = 0; i < rows-1; i++) {
        if(abs(m[i][i]) < tol){
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

void retrosustitucion(double m[MAXROW][MAXCOLM], double b[MAXROW], double x[MAXROW], int rows, int columns) {
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

void polynomial (double x[MAXROW], int p){
    cout << "\nPolinomio: " << endl;
    int pow = 0;
    for (int i = 0; i <= p - 1; i++) {
        if (pow == 0)
            printf("%lf", x[i]);
        else {
            if (x[i] >= 0)
                printf(" + %E.x^%d ", x[i], pow);
            else
                printf(" %E.x^%d", x[i], pow);
        }
        pow++;
    }
}