#include "../UNIR-2D/UNIR-2D.h"
#include "Tablero.h"
#include <cstdlib>
#include <ctime>

Tablero::Tablero(int filas, int columnas, int totalMinas)
    : m_filas(filas), m_columnas(columnas), m_totalMinas(totalMinas) {
}

void Tablero::inicializa() {
    m_banderasColocadas = 0;
    m_celdasReveladas   = 0;

    m_celdas.assign(m_filas, std::vector<Celda>(m_columnas));

    colocarMinas();
    calcularNumeros();
}

int Tablero::filas()      const { return m_filas; }
int Tablero::columnas()   const { return m_columnas; }
int Tablero::totalMinas() const { return m_totalMinas; }
int Tablero::banderasColocadas() const { return m_banderasColocadas; }
int Tablero::celdasReveladas()   const { return m_celdasReveladas; }

const Celda& Tablero::celda(int fila, int col) const {
    return m_celdas[fila][col];
}

void Tablero::revelar(int fila, int col) {
    if (!m_celdas[fila][col].revelada) {
        m_celdas[fila][col].revelada = true;
        m_celdasReveladas++;
    }
}

void Tablero::alternarBandera(int fila, int col) {
    if (m_celdas[fila][col].revelada) return;

    if (m_celdas[fila][col].tieneBandera) {
        m_celdas[fila][col].tieneBandera = false;
        m_banderasColocadas--;
    } else {
        m_celdas[fila][col].tieneBandera = true;
        m_banderasColocadas++;
    }
}

bool Tablero::dentroDelTablero(int fila, int col) const {
    return fila >= 0 && fila < m_filas && col >= 0 && col < m_columnas;
}

void Tablero::colocarMinas() {
    srand((unsigned int)time(nullptr));

    int minasColocadas = 0;
    while (minasColocadas < m_totalMinas) {
        int f = rand() % m_filas;
        int c = rand() % m_columnas;
        if (!m_celdas[f][c].tieneMina) {
            m_celdas[f][c].tieneMina = true;
            minasColocadas++;
        }
    }
}

void Tablero::calcularNumeros() {
    int desplazamientos[8][2] = {
        {-1,-1}, {-1,0}, {-1,1},
        { 0,-1},          { 0,1},
        { 1,-1}, { 1,0}, { 1,1}
    };

    for (int f = 0; f < m_filas; f++) {
        for (int c = 0; c < m_columnas; c++) {
            if (m_celdas[f][c].tieneMina) continue;

            int cuenta = 0;
            for (auto& d : desplazamientos) {
                int vf = f + d[0];
                int vc = c + d[1];
                if (dentroDelTablero(vf, vc) && m_celdas[vf][vc].tieneMina) {
                    cuenta++;
                }
            }
            m_celdas[f][c].minasCercanas = cuenta;
        }
    }
}
