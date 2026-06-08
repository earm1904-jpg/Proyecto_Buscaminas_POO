#pragma once

#include "../UNIR-2D/UNIR-2D.h"
#include  "Tablero.h"
#include <vector>


// Declaración adelantada de la clase JuegoBuscaminas para reducir dependencias
class JuegoBuscaminas;


class ActorEntrada : public unir2d::ActorBase {
public:
    //Constructor que oermite crear un actor en el juego
    ActorEntrada(JuegoBuscaminas* juego);

protected:
    void inicia()                     override;
    void actualiza(double tiempo_seg) override;

private:
    // Se crear un punto de la clase JuegoBucaminas para no incluir todo el archivo .h
    JuegoBuscaminas* m_juego;

    // Método para gestionar el clic izquierdo
    void procesarClic(int fila, int col);


    //Gestinonar clic derecho
    void procesarBandera(int fila, int col);

    // Imnplementación de automatiación para revelar celdas vecinas
    void revelarRecursivo(Tablero* tablero, int fila, int col);


    // Comprobar si todas las celdas sin minas se han revelado
    bool comprobarVictoria(Tablero* tablero) const;

    // Verificación de las posiciones validas dentro del tablero
    bool coordenadasValidas(Tablero* tablero, int fila, int col) const;
};


