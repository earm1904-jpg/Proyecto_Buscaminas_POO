#pragma once

#include "../UNIR-2D/UNIR-2D.h"
#include "Tablero.h"
#include <vector>

// Tamano de cada celda en pixeles y posicion del tablero en pantalla
static const float TAMANO_CELDA = 44.0f;
static const float TABLERO_X    = 52.0f;
static const float TABLERO_Y    = 110.0f;

class ActorTablero : public unir2d::ActorBase {
public:
    ActorTablero(Tablero* tablero);

protected:
    void inicia()                     override;
    void termina()                    override;
    void actualiza(double tiempo_seg) override;

private:
    Tablero* m_tablero;
    // Sombra de cada celda
    std::vector<unir2d::Rectangulo*> m_sombraCeldas;
    // Un rectangulo por celda para el fondo
    std::vector<unir2d::Rectangulo*> m_rectCeldas;
    // Un texto por celda para el numero o simbolo
    std::vector<unir2d::Texto*>      m_txtCeldas;

    void actualizarCelda(int fila, int col, bool mostrarMinas);
    unir2d::Color colorNumero(int numero) const;
    unir2d::Color colorFondoNumero(int numero) const;
};
