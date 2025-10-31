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

//Misma que en el gato solo ampliamos el rango de la matriz
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
//Esta mal todo, me fui con la idea de hacerlo como en el gato pero no es igual ya que aqui solo se seleccionara
//la columna, no fila y columna y pues la idea que tenia en mente ya no funciona asi que hay que descartarlo
//y volver a pensar en como hacerlo de nuevo
void CaidaDeFicha(char c, int row, int columna) {
    system("cls");
    cout << "   0   1   2   3   4   5   6\n";
    for (int fila = 0; fila < 6; ++fila) {
        cout << fila << " ";
        for (int col = 0; col < 7; ++col) {
            if (fila == row)
                cout << " " << tabla[row][columna];;
            cout << " " << tabla[fila][col];
            if (fila == row)
                tabla[fila][col] = ' ';
            if (col < 6) cout << " |";
        }
        cout << "\n";
        if (fila < 7) cout << "  ---+---+---+---+---+---+---\n";
    }
}

char jugar() {
    int fila, columna, opc;
        while (true) { //Ciclo para que no se seleccione una casilla ya utilizada
            while (true) {//Ciclo para no colocar un dato invalido
                imprimirTabla();
                //Cree una opcion para que en cualquier momento pueden colocar un 9 para que 
                //se reinicie el juego y te mande al menu de salida
                cout << "Ingrese un 9 en cualquier momento para reiniciar la partida...\n";
                cout << "Jugador 1 elija su casilla, primero elija fila y despues columna (ejemplo 1 0)\n";
                cin >> opc;
                //Aqui comprobamos que si es 9 ya sea fila o columna se reinicie
                if (opc == 9)
                    return 'R';
                if ((opc < 0 || opc>6))
                    cout << "Valores invalidos, vuelva a seleccionar\n";
                else
                    break;
            }
            //Comprobamos si la casilla seleccionada esta vacia entonces se coloca X
            if (tabla[fila][columna] == ' ') {
                CaidaDeFicha('X', fila, columna);
                tabla[fila][columna] = 'X';
                break;
            } // Si no esta vacia entonces se muestra el error y volvemos a seleccionar
            else {
                cout << "Casilla tomada, vuelva a seleccionar\n";
            }
        }
}

int main()
{
    int resultado;
    //imprimirTabla();
    resultado = jugar();

    if (checaGanador('X'))
        cout << "Ya tenemos un ganador";
}
