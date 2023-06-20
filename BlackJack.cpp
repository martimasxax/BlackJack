#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int generarNumeroAleatorio(int min, int max) {
    return min + rand() % (max - min + 1);
}


int obtenerValorCarta(string carta) {
    if (carta == "J" || carta == "Q" || carta == "K") {
        return 10;
    }
    else if (carta == "A") {
        return 0;  // El valor del As se determinará más adelante
    }
    else {
        return carta;
    }
}

int calcularValorMano(string mano[], int numCartas) {
    int valor = 0;
    int numAses = 0;

    for (int i = 0; i < numCartas; i++) {
        int cartaValor = obtenerValorCarta(mano[i]);
        if (cartaValor == 0) {
            numAses++;
        }
        else {
            valor += cartaValor;
        }
    }

    // Calcular el valor del As
    for (int i = 0; i < numAses; i++) {
        if (valor + 11 <= 21) {
            valor += 11;
        }
        else {
            valor += 1;
        }
    }

    return valor;
}


void mostrarCartas(string mano[], int numCartas) {
    cout << "Cartas: ";
    for (int i = 0; i < numCartas; i++) {
        cout << mano[i] << " ";
    }
    cout << endl;
}
void finalJuego(int valorJugador, int valorCroupier) {
    if (valorJugador > 21) {
        cout << "Te has pasado. ¡El croupier gana!" << endl;
    }
    else if (valorJugador == 21 && valorCroupier == 21) {
        cout << "Empate." << endl;
    }
    else if (valorJugador == 21 && valorCroupier != 21) {
        cout << "¡Blackjack! ¡Ganas!" << endl;
    }
    else if (valorCroupier > 21) {
        cout << "El croupier se ha pasado. ¡Ganas!" << endl;
    }
    else if (valorJugador < valorCroupier) {
        cout << "El croupier tiene una puntuación mayor. ¡El croupier gana!" << endl;
    }
    else if (valorJugador > valorCroupier) {
        cout << "Tienes una puntuación mayor. ¡Ganas!" << endl;
    }
    else {
        cout << "Empate." << endl;
    }
}

int main() {
    srand(time(0)); 

    string baraja[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
    string manoJugador[9];
    string manoCroupier[9];

    int numCartasJugador = 0;
    int numCartasCroupier = 0;

    // Repartir dos cartas al jugador
    manoJugador[numCartasJugador++] = baraja[generarNumeroAleatorio(0, 12)];
    manoJugador[numCartasJugador++] = baraja[generarNumeroAleatorio(0, 12)];

    // Repartir una carta al croupier
    manoCroupier[numCartasCroupier++] = baraja[generarNumeroAleatorio(0, 12)];

    cout << "Bienvenido a la mesa de Blackjack!" << endl;

    // Mostrar las cartas del jugador
    cout << "Tus cartas son :" << endl;
    mostrarCartas(manoJugador, numCartasJugador);
    cout << "Total: " << calcularValorMano(manoJugador, numCartasJugador) << endl;

    // Turno del jugador
    while (calcularValorMano(manoJugador, numCartasJugador) < 21) {
        string accion;
        cout << "¿Quieres pedir otra carta? (s/n): ";
        cin >> accion;

        if (accion == "s") {
            manoJugador[numCartasJugador++] = baraja[generarNumeroAleatorio(0, 12)];

            cout << "Tus cartas:" << endl;
            mostrarCartas(manoJugador, numCartasJugador);
            cout << "Total: " << calcularValorMano(manoJugador, numCartasJugador) << endl;
        }
        else if (accion == "n") {
            break;
        }
        else {
            cout << "Acción inválida. Intenta de nuevo." << endl;
        }
    }

    // Turno del croupier
    cout << "Turno del croupier..." << endl;
    cout << "Cartas del croupier:" << endl;
    mostrarCartas(manoCroupier, numCartasCroupier);
    cout << "Total: " << calcularValorMano(manoCroupier, numCartasCroupier) << endl;

    while (calcularValorMano(manoCroupier, numCartasCroupier) < 17) {
        manoCroupier[numCartasCroupier++] = baraja[generarNumeroAleatorio(0, 12)];

        cout << "Cartas del croupier:" << endl;
        mostrarCartas(manoCroupier, numCartasCroupier);
        cout << "Total: " << calcularValorMano(manoCroupier, numCartasCroupier) << endl;
    }

    // Calcular los resultados
    int valorJugador = calcularValorMano(manoJugador, numCartasJugador);
    int valorCroupier = calcularValorMano(manoCroupier, numCartasCroupier);

    cout << "Resultados de la partida:" << endl;
    cout << "Tus cartas: ";
    mostrarCartas(manoJugador, numCartasJugador);
    cout << "Total: " << valorJugador << endl;

    cout << "Cartas del croupier: ";
    mostrarCartas(manoCroupier, numCartasCroupier);
    cout << "Total: " << valorCroupier << endl;
    finalJuego(valorJugador, valorCroupier);
    

    return 0;
}
