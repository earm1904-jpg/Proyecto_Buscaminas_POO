#pragma once

#include "../UNIR-2D/UNIR-2D.h"
#include "Tablero.h"


// Cabecera de actorHUD, que se encarga de mostrar el número de minas restantes y el tiempo transcurrido desde el inicio del juego. 
// El actor HUD se actualiza en cada ciclo del juego para reflejar los cambios en el tablero y el tiempo transcurrido.
class ActorHUD : public unir2d::ActorBase {
public:
    ActorHUD(Tablero* tablero);

protected:
    void inicia()                     override;
    void termina()                    override;
    void actualiza(double tiempo_seg) override;

private:
    Tablero*           m_tablero;
    unir2d::Texto*     m_txtMinas    = nullptr;
    unir2d::Texto*     m_txtTiempo   = nullptr;
    unir2d::Rectangulo* m_fondoHUD   = nullptr;

    double m_tiempoInicio = -1.0;
};
