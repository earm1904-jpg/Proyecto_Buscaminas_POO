#pragma once

#include "../UNIR-2D/UNIR-2D.h"
#include <vector>

// Estados posibles de la partida
enum class EstadoPartida {
    jugando,
    ganado,
    perdido
};

// Datos de una celda del tablero
struct Celda {
    bool tieneMina    = false;
    bool revelada     = false;
    bool tieneBandera = false;
    int  minasCercanas = 0;
};

class Tablero {
public:
    Tablero(int filas, int columnas, int totalMinas);

    void inicializa();

    int filas()      const;
    int columnas()   const;
    int totalMinas() const;
    int banderasColocadas() const;
    int celdasReveladas()   const;

    const Celda& celda(int fila, int col) const;

    void revelar(int fila, int col);
    void alternarBandera(int fila, int col);

private:
    int m_filas;
    int m_columnas;
    int m_totalMinas;
    int m_banderasColocadas = 0;
    int m_celdasReveladas   = 0;

    std::vector<std::vector<Celda>> m_celdas;

    void colocarMinas();
    void calcularNumeros();
    bool dentroDelTablero(int fila, int col) const;
};
