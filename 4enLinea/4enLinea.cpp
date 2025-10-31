#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;
char tabla[6][7] = { {' ', ' ', ' ',' ', ' ', ' ', ' '},
                     {' ', ' ', ' ',' ', ' ', ' ', ' '},
                     {' ', ' ', ' ',' ', ' ', ' ', ' '},
                     {' ', ' ', ' ',' ', ' ', ' ', ' '},
                     {' ', ' ', ' ',' ', ' ', ' ', ' '},
                     {' ', ' ', ' ',' ', ' ', ' ', ' '} };

void imprimirTabla() {
    cout << "   0   1   2   3   4   5   6\n";
    for (int fila = 0; fila < 6; ++fila) {
        cout << fila << " ";
        for (int col = 0; col < 7; ++col) {
            cout << " " << tabla[fila][col];
            if (col < 6) cout << " |";
        }
        cout << "\n";
        if (fila < 7) cout << "  ---+---+---+---+---+---+---\n";
    }

}

void limpiarTabla() {
    //Es basciamente un barrido donde en cada dato de la matriz se colo un " " para que quede vacia
    for (int fila = 0; fila < 6; ++fila) {
        for (int col = 0; col < 7; ++col) {
            tabla[fila][col] = ' ';
        }
    }
}

bool casillasDisponibles() {
    for (int fila = 0; fila < 6; ++fila) {
        for (int col = 0; col < 7; ++col) {
            if (tabla[fila][col] == ' ')
                return true;
        }
    }
    return false;
}

bool checaGanador(char c) {
    // Horizontal
    //Utilizare ciclos for para verificar si se cumplen los 4 caracteres en linea
    //Con las comprobaciones que realice si jala bien los resultados, tocara esperar a ver cuando
    //cree las funciones para ingresar los datos manualmente...
    for (int fila = 0; fila < 6; fila++) {
        for (int col = 0; col <= 3; col++) {
            if (tabla[fila][col] == c &&
                tabla[fila][col + 1] == c &&
                tabla[fila][col + 2] == c &&
                tabla[fila][col + 3] == c)
                return true;
        }
    }

    // Vertical
    for (int col = 0; col < 7; col++) {
        for (int fila = 0; fila <= 3; fila++) {
            if (tabla[fila][col] == c &&
                tabla[fila + 1][col] == c &&
                tabla[fila + 2][col] == c &&
                tabla[fila + 3][col] == c)
                return true;
        }
    }

    // Diagonal descendente 
    for (int fila = 0; fila <= 2; fila++) {
        for (int col = 0; col <= 3; col++) {
            if (tabla[fila][col] == c &&
                tabla[fila + 1][col + 1] == c &&
                tabla[fila + 2][col + 2] == c &&
                tabla[fila + 3][col + 3] == c)
                return true;
        }
    }

    // Diagonal ascendente 
    for (int fila = 3; fila < 6; fila++) {
        for (int col = 0; col <= 3; col++) {
            if (tabla[fila][col] == c &&
                tabla[fila - 1][col + 1] == c &&
                tabla[fila - 2][col + 2] == c &&
                tabla[fila - 3][col + 3] == c)
                return true;
        }
    }

    return false;
}

//Quiero hacer una funcion donde se vea "caer" la ficha que se coloque hasta el lugar más bajo disponible
//Creo que con ciclos for parecidos a cuando imprimo la tabla puede funcionar
void CaidaDeFicha() {

}

int main()
{
    imprimirTabla();
    if (checaGanador('X'))
        cout << "Ya tenemos un ganador";
}
