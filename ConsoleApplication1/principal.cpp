#include "../UNIR-2D/UNIR-2D.h"
#include "JuegoBuscaminas.h"

int main() {
    JuegoBuscaminas* juego = new JuegoBuscaminas{};
    unir2d::Motor*   motor = new unir2d::Motor{};

    // Ejecutamos el juego.
    motor->ejecuta(juego);


    // Una vez finalizado, destruimos motor y juego para liberar memoria
    delete motor;
    delete juego;

    return 0;
}
