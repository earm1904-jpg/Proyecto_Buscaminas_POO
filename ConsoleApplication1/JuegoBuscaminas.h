#pragma once

#include "../UNIR-2D/UNIR-2D.h"
#include  "Tablero.h"

class ActorTablero;
class ActorHUD;
class ActorInicio;
class ActorFin;
class ActorEntrada;



// Definimos el estado de la partida
class JuegoBuscaminas : public unir2d::JuegoBase {
public:
    JuegoBuscaminas();

    EstadoPartida estadoPartida() const;
    void setEstadoPartida(EstadoPartida estado);

    Tablero* tablero();

protected:
    const wstring tituloVentana() const override;
    void regionVentana(unir2d::Vector& posicion, unir2d::Vector& tamano) const override;

    void inicia()                    override;
    void termina()                   override;
    void preactualiza(double tiempo) override;

private:
    EstadoPartida  m_estado = EstadoPartida::jugando;
    Tablero*       m_tablero   = nullptr;

    ActorInicio*   m_actorInicio  = nullptr;
    ActorTablero*  m_actorTablero = nullptr;
    ActorHUD*      m_actorHUD     = nullptr;
    ActorEntrada*  m_actorEntrada = nullptr;
    ActorFin*      m_actorFin     = nullptr;

    bool m_esperandoInicio = true;

    void mostrarPantallaJuego();
    void mostrarPantallaFin();
};
