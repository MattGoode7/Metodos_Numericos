#include <iostream>
#include <math.h>

#define MAXROW 12
#define MAXCOL 2
#define MAXCOL2 12

using namespace std;

void readTxtI(double[MAXROW][MAXCOL], int *);
void printMatrixI(double[MAXROW][MAXCOL], int);
void buildMatrix(double [MAXROW][MAXCOL], double [MAXROW][MAXCOL2], double [MAXROW], int);
void interpolation(double [MAXROW][MAXCOL], double [MAXROW], int);
void printMatrix(double [MAXROW][MAXCOL2], double [MAXROW], int, int);
void triangulation(double [MAXROW][MAXCOL2], double [MAXROW], int, int);
void retrosustitucion(double [MAXROW][MAXCOL2], double [MAXROW], double [MAXROW], int, int);
void pivot(double [MAXROW][MAXCOL2], double [MAXROW], int, int, int);

int main(int argc, char *argv[]) {

    double nodes[MAXROW][MAXCOL];
    double matrix[MAXROW][MAXCOL2];
    double b[MAXROW];
    double z[MAXROW];
    int rows;

    readTxtI(nodes, &rows);
    printMatrixI(nodes, rows);
    // intervals = nodes - 1
    buildMatrix(nodes, matrix, b, rows - 1);

    cout << "\nMatriz antes de reducir" << endl;

    printMatrix(matrix, b, 4 * (rows - 1), 4 * (rows - 1));

    cout << "\nMatriz despues de reducir" << endl;

    triangulation(matrix, b, 4 * (rows - 1), 4 * (rows - 1));
    retrosustitucion(matrix, b, z, 4 * (rows - 1), 4 * (rows - 1));
    interpolation(nodes, z, rows);

    return 0;
}

void readTxtI(double m[MAXROW][MAXCOL], int *rows) {
    FILE *readPtr;
    int j, i, n;
    float k;
    readPtr = fopen("data.txt", "r");
    fscanf(readPtr, "%d", &n);
    *rows = n;

    for (i = 0; i < *rows; i++) {
        for (j = 0; j < MAXCOL; j++) {
            fscanf(readPtr, "%f", &k);
            m[i][j] = k;
        }
    }
    fclose(readPtr);
}

void printMatrixI(double m[MAXROW][MAXCOL], int rows) {
    cout << "------ NODOS ------" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < MAXCOL; j++) {
            cout << m[i][j];
        }
        cout << endl;
    }
    cout << "-------------------\n" << endl;
}

void printMatrix(double m[MAXROW][MAXCOL2], double b[MAXROW], int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << m[i][j];
        }
        cout << b[i];
        cout << endl;

    }
}

void buildMatrix(double nodes[MAXROW][MAXCOL], double matrix[MAXROW][MAXCOL2], double b[MAXROW], int intervals) {

    ///construccion de las primeras 2n ecuaciones(imagen de la funcion)
    for (int i = 0; i < intervals; ++i) {
        for (int j = 0; j <= 3; ++j) {
            matrix[2 * i][4 * i + j] = pow(nodes[i][0], 3 - j);
            matrix[2 * i + 1][4 * i + j] = pow(nodes[i + 1][0], 3 - j);
        }
        b[2 * i] = nodes[i][1];
        b[2 * i + 1] = nodes[i + 1][1];
    }

    ///construccion de las primeras n-1 ecuaciones(derivadas primeras)
    for (int i = 2 * intervals; i <= (3 * intervals - 2); ++i) {
        for (int j = 0; j <= intervals - 2; ++j) {
            for (int k = 0; k <= 2; ++k) {
                matrix[i][4 * j + k] = (3 - k) * pow(nodes[j + 1][0], 2 - k);
                matrix[i][4 * (j + 1) + k] = -(3 - k) * pow(nodes[j + 1][0], 2 - k);
            }
        }
        b[i] = 0;
    }

    ///derivadas segundas
    for (int i = 3 * intervals - 1; i <= (4 * intervals - 3); ++i) {
        for (int j = 0; j <= intervals - 2; ++j) {
            matrix[i][4 * j] = 6 * nodes[j + 1][0];
            matrix[i][4 * j + 1] = 2;
            matrix[i][4 * j + 4] = (-6 * nodes[j + 1][0]);
            matrix[i][4 * j + 5] = (-2);
        }
        b[i] = 0;
    }

    matrix[4 * intervals - 2][0] = 6 * nodes[0][0];
    matrix[4 * intervals - 2][1] = 2;
    b[4 * intervals - 2] = 0;

    matrix[4 * intervals - 1][4 * intervals - 4] = 6 * nodes[intervals][0];
    matrix[4 * intervals - 1][4 * intervals - 3] = 2;
    b[4 * intervals - 1] = 0;

}

void interpolation (double nodes[MAXROW][MAXCOL], double z[MAXROW], int rows) {
    double value;
    double result = 0;
    cout << "\nIngrese el valor a interpolar" << endl;
    cin  >> value;

    if (value >= nodes[0][0] && value <= nodes[rows - 1][0]) {
        for (int i = 0; i < rows; ++i) {
            if(value <= nodes[i+1][0]){
                result = z[4*i]*pow(value,3) + z[4*i+1]*pow(value,2) + z[4*i+2]*value + z[4*i+3];
                break;
            }
        }
        cout << "El valor interpolado para " << value << "es: " << result;
    }
    else{
        cout << "\nEl valor a interpolar no se encuentra en el rango de datos\n" << endl;
    }
}

void triangulation(double m[MAXROW][MAXCOL2], double b[MAXROW], int rows, int columns) {
    for (int i = 0; i < rows - 1; ++i) {
        pivot(m, b, rows, columns, i);
        for (int j = i + 1; j < rows; ++j) {
            double factor = -m[j][i] / m[i][i];
            for (int k = 0; k < columns; ++k) {
                m[j][k] = m[i][k] * factor + m[j][k];
            }
            b[j] = b[i] * factor + b[j];
        }
    }
    printMatrix(m, b, rows, columns);
}

void pivot(double m[MAXROW][MAXCOL2], double b[MAXROW], int rows, int columns, int i) {
    double tolerance = pow(10, -3);
    if (fabs(m[i][i]) < tolerance) {
        for (int j = i + 1; j < rows; ++j) {
            if (fabs(m[j][i]) > fabs(m[i][i])) {
                for (int k = i; k < columns; ++k) {
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

void retrosustitucion(double m[MAXROW][MAXCOL2], double b[MAXROW], double x[MAXROW], int rows, int columns) {
    double value = 0;
    value = b[rows - 1] / m[rows - 1][columns - 1];
    x[rows - 1] = value;
    for (int i = rows - 2; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < columns; ++j) {
            sum = sum + m[i][j] * x[j];
        }
        value = (b[i] - sum) / m[i][i];
        x[i] = value;
    }
    cout << "\nConjunto solucion" << endl;
    for (int i = 0; i < rows; ++i) {
        cout << "x" << i << " = " << x[i];
    }
}
