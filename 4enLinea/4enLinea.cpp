#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace std;
//Declare la tabla global para que no sea necesario que la tenga que estar enviando a todas las funciones que la utilicen
char tabla[6][7] = { {' ', ' ', ' ',' ', ' ', ' ', ' '},
                     {' ', ' ', ' ',' ', ' ', ' ', ' '},
                     {' ', ' ', ' ',' ', ' ', ' ', ' '},
                     {' ', ' ', ' ',' ', ' ', ' ', ' '},
                     {' ', ' ', ' ',' ', ' ', ' ', ' '},
                     {' ', ' ', ' ',' ', ' ', ' ', ' '} };

//Creamos un menu sencillo para el juego
int menu() {
    int opc;
    while (true) {
        cout << "=========================================\n";
        cout << "         BIENVENIDO A CONECTA 4          \n";
        cout << "=========================================\n";
        cout << " Un juego de estrategia para dos jugadores\n";
        cout << " Gana quien conecte 4 fichas iguales      \n";
        cout << " en linea horizontal, vertical o diagonal \n";
        cout << "-----------------------------------------\n";
        cout << " 1. Iniciar nuevo juego                   \n";
        cout << " 2. Salir                                 \n";
        cout << "=========================================\n";
        cout << " Selecciona una opcion: ";
        cin >> opc;
        if ((opc < 1) || (opc > 3))
            cout << "Opcion incorrecta, vuelve a seleccionar.\n";
        else
            return opc;
    };
}

//Funcion para estar imprimiendo la tabla en pantalla
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

//Funcion para cuando se requiera jugar de nuevo y se tenga que limpiar la tabla
void limpiarTabla() {
    //Es basciamente un barrido donde en cada dato de la matriz se colo un " " para que quede vacia
    for (int fila = 0; fila < 6; ++fila) {
        for (int col = 0; col < 7; ++col) {
            tabla[fila][col] = ' ';
        }
    }
}

//Misma que en el gato solo ampliamos el rango de la matriz
//Verificamos que aun haya espacios disponibles en la tabla
bool casillasDisponibles() {
    for (int fila = 0; fila < 6; ++fila) {
        for (int col = 0; col < 7; ++col) {
            if (tabla[fila][col] == ' ')
                return true;
        }
    }
    return false;
}

//Utilice ciclos for para poder hacer las comprobaciones en cuando a si ya alguien cumplio con las 4 en linea, tnato horizontales como verticales y diagonales
//Es bool ya que si no se cumple ninguno regresa un false que significa que no hay un ganador aun
bool checaGanador(char c) {
    // Horizontal
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

bool checaEmpate() {
    //Bool para comprobar si fue o no empate, si ya hay ganador pues entonces no hay empate por eso primero
    // lo verifico
    if (checaGanador('X') == true)
        return false;
    if (checaGanador('O') == true)
        return false;
    //Verificamos si aun hay casillas para hacer o no empate
    if (casillasDisponibles() == true)
        return false;
    return true;
}

//Esta funcion lo que hace es basicamente dibujar o hacer la animacion que cuando se selecciona una columna se vea como va cayendo la ficha hasta la posiciones que debe de ir
void CaidaDeFicha(char c, int row, int columna) {
    system("cls");
    for (int i = 0; i <= row; i++) {
        tabla[i][columna] = c; //Le damos el valor a la casilla
        imprimirTabla();       //Imprimimos la tabla para que se vea
        tabla[i][columna] = ' ';//Luego quitamos el valor de la casilla para que de el efecto de caida
        Sleep(250);             //Esta linea hace que el juego espere 250 milisegundos para pasar a la siguiente linea y eso hace que se cree la "animacion" de caer
        system("cls");
    }
}

//Funcion donde se jugara
char jugar() {
    int opc;
    bool fichacolocada;
    while (true) { //Ciclo para que se siga jugando mientras el jugador no seleccione salir
        fichacolocada = false; //Esta variable la usaremos para poder salir del ciclo siguiente ya que si no se quedaba ciclado por la posiciones de los break
        while (true) { //Ciclo para que no se seleccione una casilla ya utilizada
            while (true) {//Ciclo para no colocar un dato invalido
                cout << "Jugador 1 elija la columna donde quiere jugar\n";
                cin >> opc;
                if ((opc < 0 || opc>6))
                    cout << "Valores invalidos, vuelva a seleccionar\n";
                else
                    break;
            }
            for (int fila = 5; fila >= 0; --fila) {
                if (tabla[fila][opc] == ' ') {
                    CaidaDeFicha('X', fila, opc); //Una vez que se selecciona la columna primero hacemos el efecto de caida de la ficha
                    tabla[fila][opc] = 'X'; //Despues ya colocamos la ficha en la ultima opcion disponible
                    system("cls");
                    imprimirTabla();
                    fichacolocada = true;
                    break;
                }
            }
            if (fichacolocada) //Si ya se coloco una ficha entonces salimos del ciclo para irnos al turno del jugador 2
                break;
            system("cls");
            imprimirTabla();
            cout << "La columna esta llena, seleccione de nuevo\n";
        }
        //Verificamos si hay empate o si ya tenemos un ganador
        if (checaEmpate())
            return 'E';
        if (checaGanador('X'))
            return 'X';
        //Esto es basicamente el codigo de arriba pero oritentado al jugador 2 'O'
        fichacolocada = false;
            while (true) { //Ciclo para que no se seleccione una casilla ya utilizada
                while (true) {//Ciclo para no colocar un dato invalido
                    cout << "Jugador 2 elija la columna donde quiere jugar\n";
                    cin >> opc;
                    if ((opc < 0 || opc>6))
                        cout << "Valores invalidos, vuelva a seleccionar\n";
                    else
                        break;
                }
                for (int fila = 5; fila >= 0; --fila) {
                    if (tabla[fila][opc] == ' ') {
                        CaidaDeFicha('O', fila, opc);
                        tabla[fila][opc] = 'O';
                        system("cls");
                        imprimirTabla();
                        fichacolocada = true;
                        break;
                    }
                }
                if (fichacolocada)
                    break;
                system("cls");
                imprimirTabla();
                cout << "La columna esta llena, seleccione de nuevo\n";
        }
     if (checaEmpate())
        return 'E';
     if (checaGanador('O'))
        return 'O';
    }
}

//Funcion para felicitar al ganador
void felicitarGanador(char jugador) {
    cout << "\n==============================\n";
    cout << "   ¡Felicidades Jugador " << (jugador == 'X' ? "1" : "2") << "! \n";
    cout << "   ¡Has logrado conectar 4!\n";
    cout << "==============================\n\n";
}
//Mensaje de empate
void mensajeEmpate() {
    cout << "===============================" << endl;
    cout << "|                             |" << endl;
    cout << "|         ¡EMPATE!            |" << endl;
    cout << "|                             |" << endl;
    cout << "|   El tablero esta lleno     |" << endl;
    cout << "|   y nadie logro ganar.      |" << endl;
    cout << "|                             |" << endl;
    cout << "|   ¡Gran juego de ambos!     |" << endl;
    cout << "|                             |" << endl;
    cout << "===============================" << endl;

}

//Funcion main donde se mandara a llamar a los demas funciones para que se pueda realizar el juego, trate de que fuese lo más compacto disponible modularizando todas las funciones
//que pude, para asi poder utilizarlas despues como lo hice con el proyecto anterior, que tome funciones y las adapte a este nuevo proyecto
int main()
{
    int modo,opc,resultado;
    while (true) { //While para que se siga repitiendo mientras el jugador pida volver a jugar
        opc = menu();
        system("cls");
        imprimirTabla();
        if (opc == 1) {
            resultado = jugar();
            if (resultado == 'X') {
                system("cls");
                imprimirTabla();
                felicitarGanador('X');
            }
            else if (resultado == 'O') {
                system("cls");
                imprimirTabla();
                felicitarGanador('O');
            }
            else if (resultado == 'E') {
                system("cls");
                imprimirTabla();
                mensajeEmpate();
            }
        }
        else
            return 0;
        cout << "Quieres volver a jugar (1-si 2-no) ?\n";
        cin >> modo;
        if (modo == 2)
            break;
        else
            system("cls");
        limpiarTabla();
    }
}
