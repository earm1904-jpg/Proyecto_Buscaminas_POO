#include "../UNIR-2D/UNIR-2D.h"
#include "JuegoBuscaminas.h"
#include "ActorTablero.h"
#include "ActorHUD.h"
#include "ActorInicio.h"
#include "ActorFin.h"
#include "ActorEntrada.h"

// 9x9 con 10 minas
static const int FILAS   = 9;
static const int COLUMNAS = 9;
static const int MINAS    = 10;



// Constructor del tablero de juego. Si quisieramos modificarlo solo habría que cambiar los valores de las constantes anteriores.
JuegoBuscaminas::JuegoBuscaminas() {
    m_tablero = new Tablero(FILAS, COLUMNAS, MINAS);
}

// Devuelve el estado de la partida.
EstadoPartida JuegoBuscaminas::estadoPartida() const {
    return m_estado;
}

// Establecemos el estado de la partida.
void JuegoBuscaminas::setEstadoPartida(EstadoPartida estado) {
    m_estado = estado;
}

// Devuelve el tablero de juego.
Tablero* JuegoBuscaminas::tablero() {
    return m_tablero;
}

const wstring JuegoBuscaminas::tituloVentana() const {
    return L"Buscaminas";
}


// Establecemos la posicion y el tamaño de la ventana de juego.
void JuegoBuscaminas::regionVentana(unir2d::Vector& posicion, unir2d::Vector& tamano) const {
    posicion = unir2d::Vector(100, 100);
    tamano   = unir2d::Vector(500, 560);
}

// Iniciamos el juego.
void JuegoBuscaminas::inicia() {
    m_esperandoInicio = true;
    m_estado = EstadoPartida::jugando;
    m_actorInicio = new ActorInicio(this);
    agregaActor(m_actorInicio);
}

// Destruimos el juego, liberando memoria.
void JuegoBuscaminas::termina() {
    delete m_tablero;
    m_tablero = nullptr;
}


// Gestionamos las transiciones entre los diferentes estados de la partida.
void JuegoBuscaminas::preactualiza(double /*tiempo*/) {
    if (m_esperandoInicio) {
        if (m_actorInicio->jugadorListoPara()) {
            extraeActores();
            delete m_actorInicio;
            m_actorInicio = nullptr;
            m_esperandoInicio = false;
            mostrarPantallaJuego();
        }
        return;
    }

    if (m_estado == EstadoPartida::ganado || m_estado == EstadoPartida::perdido) {
        if (m_actorFin == nullptr) {
            extraeActores();
            delete m_actorTablero; m_actorTablero = nullptr;
            delete m_actorHUD;     m_actorHUD     = nullptr;
            delete m_actorEntrada; m_actorEntrada = nullptr;
            mostrarPantallaFin();
        } else if (m_actorFin->reiniciar()) {
            extraeActores();
            delete m_actorFin; m_actorFin = nullptr;
            m_estado = EstadoPartida::jugando;
            m_tablero->inicializa();
            mostrarPantallaJuego();
        }
    }
}

// Mostramos la pantalla de la partida, inicializando el tablero y creando los actores necesarios.
void JuegoBuscaminas::mostrarPantallaJuego() {
    m_tablero->inicializa();
    m_estado = EstadoPartida::jugando;

    m_actorTablero = new ActorTablero(m_tablero);
    m_actorHUD     = new ActorHUD(m_tablero);
    m_actorEntrada = new ActorEntrada(this);
    m_actorFin     = nullptr;

    agregaActor(m_actorTablero);
    agregaActor(m_actorHUD);
    agregaActor(m_actorEntrada);
}

// Mostramos la pantalla de final de partida.
void JuegoBuscaminas::mostrarPantallaFin() {
    m_actorFin = new ActorFin(m_estado);
    agregaActor(m_actorFin);
}
