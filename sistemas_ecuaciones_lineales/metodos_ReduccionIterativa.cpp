/* Metodos iterativos para solucion de sistemas de ecuaciones */
/*
    Se incluyen los metodos de Jacobi, Gauss-Seidel y Gauss-Seidel con coef. de relajacion

    NOTAS:
    - Cargar previamente la matriz en el data.txt
    - Comprobar las tolerancias
    - Se incluye un metodo llamado "gsChetado", una version mas de Gauss-Seidel, por si la original no anda
*/


#include <math.h>
#include <iostream>

#define MAXC 15
#define MAXR 15

using namespace std;

void read(double[MAXR][MAXC], double[MAXR], int *, int *);
void print(double[MAXR][MAXC], double[MAXR], int, int);
void jacobi(double [MAXR][MAXC], double [MAXR], int, int);
void gs(double[MAXR][MAXC], double[MAXR], int, int);
void gsChetado(double[MAXR][MAXC], double[MAXR], int, int);
void relax(double[MAXR][MAXC], double[MAXR], int, int);

int main(){

    //Variables
    double m[MAXR][MAXC];
    double b[MAXR];
    int rows = 0;
    int columns = 0;

    /* Carga y lectura de las matrices */
    read(m, b, &rows, &columns);
    print(m, b, rows, columns);


    /* Metodos iterativos */
    cout << "\nJacobi" << endl;
    jacobi(m, b, rows, columns);
    
    cout << "\nGauss-Seidel" << endl;
    gs(m, b, rows, columns);

    cout << "\nGauss-Seidel Chetado" << endl;
    gsChetado(m, b, rows, columns);

    cout << "\nRelajacion" << endl;
    relax(m, b, rows, columns);
}

void read(double m[MAXR][MAXC], double b[MAXR], int *rows, int *columns){
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

    //Carga los datos en la matriz m y b
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

void print(double m[MAXR][MAXC], double b[MAXR], int rows, int columns){
    
    /* Impresion de la matriz ampliada en pantalla */

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << m[i][j] << "\t";
        }
        cout << b[i] << endl;
    }
}

void jacobi(double m[MAXR][MAXC], double b[MAXR], int rows, int columns){
    double xv[MAXR] = {0};
    double xn[MAXR] = {0};
    double suma;
    double aux = 0;
    double error = 0;
    double tol = pow(10, -4);
    int iter = 0;

    /* Diagonalmente dominante */
    for (int i = 0; i < rows; i++)
    {
        aux = 0;
        for (int j = 0; j < columns; j++)
        {
            if(i != j){
                aux = aux + fabs(m[i][j]);
            }
        }
        if(fabs(m[i][i]) <= aux){
            cout << "\nADVERTENCIA: la matriz no es diagonalmente dominante" << endl;
            break;
        }
    }

    do
    {
        iter++;
        error = 0;

        for (int i = 0; i < rows; i++)
        {
            suma = 0;
            for (int j = 0; j < columns; j++)
            {
                if(i != j){
                    suma = suma + m[i][j]*xv[j];
                }
            }
            xn[i] = (b[i] - suma)/m[i][i];
            error = error + pow((xn[i] - xv[i]), 2);
            xv[i] = xn[i];
        }
        
        error = sqrt(error);

    } while (tol < error && iter < 10000);
    
    if(iter == 9999){
        cout << "\nNumero de iteraciones maximo alcanzado" << endl;
    }

    cout << "\nConjunto solucion" << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << "x" << i + 1 << " = " << xn[i] << endl;
    }
    
    cout << "\nError: " << error << endl;
    cout << "Iteraciones: " << iter << endl;
}

void gs(double m[MAXR][MAXC], double b[MAXR], int rows, int columns){
    
    //Variables
    double xv[MAXR] = {0};
    double xn[MAXR] = {0};
    double suma;
    double aux = 0;
    double error = 0;
    double tol = pow(10, -8);
    int iter = 0;

    //Diagonalmente dominante
    for (int i = 0; i < rows; i++)
    {
        aux = 0;
        for (int j = 0; j < columns; j++)
        {
            if(i != j){
                aux = aux + fabs(m[i][j]);
            }
        }
        if(fabs(m[i][i]) <= aux){
            cout << "\nADVERTENCIA: la matriz no es diagonalmente dominante" << endl;
            break;
        }
    }
    do
    {
        error = 0;
        iter++;
        
        for (int i = 0; i < rows; i++)
        {
            if(i == 0)
            {
                suma = 0;
                for (int j = 1; j < rows; j++)
                {
                    suma += m[i][j] * xv[j];
                }
                xn[i] = (b[i] - suma)/m[i][i];
            }
            else{
                suma = 0;
                for (int j = 0; j < i; j++)
                {
                    suma += m[i][j] * xn[j];
                }
                for (int j = i + 1; j < rows; j++)
                {
                    suma += m[i][j] * xv[j];
                }
                xn[i] = (b[i] - suma)/m[i][i];
            }
        }

        for (int i = 0; i < rows; i++)
        {
            error += pow((xn[i] - xv[i]), 2);
        }

        error = sqrt(error);

        for (int i = 0; i < rows; i++)
        {
            xv[i] = xn[i];
        }
        
        
    } while (tol < error && iter < 10000);

    if(iter == 9999){
        cout << "\nNumero de iteraciones maximo alcanzado" << endl;
    }

    cout << "\nConjunto solucion" << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << "x" << i + 1 << " = " << xn[i] << endl;
    }
    
    cout << "\nError: " << error << endl;
    cout << "Iteraciones: " << iter << endl;   
}

void relax(double m[MAXR][MAXC], double b[MAXR], int rows, int columns){
    //Variables
    double xv[MAXR] = {0};
    double xn[MAXR] = {0};
    double suma;
    double aux = 0;
    double error = 0;
    double tol = pow(10, -3);
    double cte = 0;

    cout << "\nIngrese el coeficiente de relajacion" << endl;
    cout << "Coef.:";
    cin  >> cte;

    int iter = 0;

    //Diagonalmente dominante
    for (int i = 0; i < rows; i++)
    {
        aux = 0;
        for (int j = 0; j < columns; j++)
        {
            if(i != j){
                aux = aux + fabs(m[i][j]);
            }
        }
        if(fabs(m[i][i]) <= aux){
            cout << "\nADVERTENCIA: la matriz no es diagonalmente dominante" << endl;
            break;
        }
    }
    do
    {
        error = 0;
        iter++;
        
        for (int i = 0; i < rows; i++)
        {
            suma = 0;
            for (int j = 0; j < columns; j++)
            {
                if(i != j){
                    suma = suma + m[i][j] * xv[j];
                }
            }
            xn[i] = (b[i] - suma) / m[i][i];
            error = error + pow((xn[i] - xv[i]), 2);
            xn[i] = cte * xn[i] + (1 - cte) * xv[i];
            xv[i] = xn[i];
        }
        

        error = sqrt(error);
        
    } while (tol < error && iter < 10000);

    if(iter == 9999){
        cout << "\nNumero de iteraciones maximo alcanzado" << endl;
    }

    cout << "\nConjunto solucion" << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << "x" << i + 1 << " = " << xn[i] << endl;
    }
    
    cout << "\nError: " << error << endl;
    cout << "Iteraciones: " << iter << endl;   
}

void gsChetado(double m[MAXR][MAXC], double b[MAXR], int rows, int columns){

    double xv[MAXR] = {0};
    double xn[MAXR] = {0};
    double s;
    double aux = 0;
    double error = 0;
    double tol = pow(10, -5);

    int iter = 0;

    do{
        for (int i = 0; i < rows; i++){
            s = 0;
            for (int j = 0; j < i; j++)
                s += m[i][j] * xn[j];
      
            for (int j = i + 1; j < rows; j++)
                s += m[i][j] * xv[j];

            xn[i] = (b[i] - s)/m[i][i];    
      
            double e1 = 0, e2 = 0;
        
            for(int i = 0; i < rows; i++){
                e1 += pow(xn[i]-xv[i],2);
                e2 += pow(xn[i],2);
            }
            error = sqrt(e1/e2);

            for(int i = 0; i < rows; i++){
                xv[i] = xn[i];
            }
    }

    iter++;
  } while(tol < error && iter < 10000);

  if(iter == 9999){
        cout << "\nNumero de iteraciones maximo alcanzado" << endl;
    }

    cout << "\nConjunto solucion" << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << "x" << i + 1 << " = " << xn[i] << endl;
    }
    
    cout << "\nError: " << error << endl;
    cout << "Iteraciones: " << iter << endl;  
}