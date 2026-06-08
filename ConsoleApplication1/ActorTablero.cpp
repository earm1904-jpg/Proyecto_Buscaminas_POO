#include "../UNIR-2D/UNIR-2D.h"
#include "ActorTablero.h"
#include "Tablero.h"
#include <string>



ActorTablero::ActorTablero(Tablero* tablero) : m_tablero(tablero) {
}

void ActorTablero::inicia() {
    ponPosicion(unir2d::Vector(TABLERO_X, TABLERO_Y));

    int total = m_tablero->filas() * m_tablero->columnas();

    m_sombraCeldas.reserve(total);
    m_rectCeldas.reserve(total);
    m_txtCeldas.reserve(total);

    for (int i = 0; i < total; i++) {
        int fila = i / m_tablero->columnas();
        int col = i % m_tablero->columnas();

        float x = col * TAMANO_CELDA;
        float y = fila * TAMANO_CELDA;

        auto* sombra = new unir2d::Rectangulo(TAMANO_CELDA - 6.0f, TAMANO_CELDA - 6.0f);
        sombra->ponPosicion(unir2d::Vector(x + 4.0f, y + 6.0f));
        sombra->ponColor(unir2d::Color(105, 130, 135));
        agregaDibujo(sombra);
        m_sombraCeldas.push_back(sombra);

        auto* rect = new unir2d::Rectangulo(TAMANO_CELDA - 6.0f, TAMANO_CELDA - 6.0f);
        rect->ponPosicion(unir2d::Vector(x, y));
        rect->ponColor(unir2d::Color(160, 190, 195));
        agregaDibujo(rect);
        m_rectCeldas.push_back(rect);

        auto* txt = new unir2d::Texto("BitcountSingle-Variable");
        txt->ponTamano(22);
        txt->ponPosicion(unir2d::Vector(x + TAMANO_CELDA * 0.30f, y + TAMANO_CELDA * 0.12f));
        txt->ponCadena("");
        txt->ponColor(unir2d::Color(255, 255, 255));
        agregaDibujo(txt);
        m_txtCeldas.push_back(txt);
    }
}

void ActorTablero::termina() {
    for (auto* s : m_sombraCeldas) { extraeDibujo(s); delete s; }
    for (auto* r : m_rectCeldas) { extraeDibujo(r); delete r; }
    for (auto* t : m_txtCeldas) { extraeDibujo(t); delete t; }
    m_sombraCeldas.clear();
    m_rectCeldas.clear();
    m_txtCeldas.clear();
}

void ActorTablero::actualiza(double /*tiempo_seg*/) {
    // mina revelada = partida perdida, hay que mostrar el resto
    bool juegoAcabado = false;
    for (int f = 0; f < m_tablero->filas(); f++) {
        for (int c = 0; c < m_tablero->columnas(); c++) {
            const Celda& cel = m_tablero->celda(f, c);
            if (cel.tieneMina && cel.revelada) {
                juegoAcabado = true;
            }
        }
    }

    for (int f = 0; f < m_tablero->filas(); f++) {
        for (int c = 0; c < m_tablero->columnas(); c++) {
            actualizarCelda(f, c, juegoAcabado);
        }
    }
}

void ActorTablero::actualizarCelda(int fila, int col, bool mostrarMinas) {
    int idx = fila * m_tablero->columnas() + col;
    const Celda& cel = m_tablero->celda(fila, col);

    unir2d::Rectangulo* sombra = m_sombraCeldas[idx];
    unir2d::Rectangulo* rect = m_rectCeldas[idx];
    unir2d::Texto* txt = m_txtCeldas[idx];
    txt->ponCadena("");

    if (cel.revelada) {
        sombra->ponVisible(false);
        if (cel.tieneMina) {
            rect->ponColor(colorFondoNumero(cel.minasCercanas));
            txt->ponCadena("*");
            txt->ponColor(unir2d::Color(255, 255, 255));
        }
        else if (cel.minasCercanas > 0) {
            sombra->ponVisible(true);
            sombra->ponColor(unir2d::Color(80, 105, 110));
            rect->ponColor(colorFondoNumero(cel.minasCercanas));
            txt->ponCadena(std::to_string(cel.minasCercanas));
            txt->ponColor(colorNumero(cel.minasCercanas));
        }
        else {
            rect->ponColor(unir2d::Color(245, 250, 248));
            txt->ponCadena("");
        }
    }
    else if (cel.tieneBandera) {
        sombra->ponVisible(true);
        sombra->ponColor(unir2d::Color(190, 125, 25));
        rect->ponColor(unir2d::Color(245, 190, 65));
        txt->ponCadena("P");
        txt->ponColor(unir2d::Color(220, 0, 0));
    }
    else if (mostrarMinas && cel.tieneMina) {
        sombra->ponVisible(false);
        rect->ponColor(unir2d::Color(240, 60, 110));
        txt->ponCadena("*");
        txt->ponColor(unir2d::Color(255, 255, 255));
    }
    else {
        sombra->ponVisible(true);
        sombra->ponColor(unir2d::Color(80, 105, 110));
        rect->ponColor(unir2d::Color(160, 190, 195));
        txt->ponCadena("");
    }
}

unir2d::Color ActorTablero::colorNumero(int numero) const {
    return unir2d::Color(255,255,255);
}

unir2d::Color ActorTablero::colorFondoNumero(int numero) const {
    switch (numero) {
    case 1: return unir2d::Color(0, 120, 220);
    case 2: return unir2d::Color(0, 150, 70);
    case 3: return unir2d::Color(220, 40, 40);
    case 4: return unir2d::Color(40, 70, 170);
    case 5: return unir2d::Color(150, 50, 40);
    case 6: return unir2d::Color(0, 150, 150);
    case 7: return unir2d::Color(50, 50, 50);
    case 8: return unir2d::Color(120, 120, 120);
    default: return unir2d::Color(180, 180, 180);
    }
}


