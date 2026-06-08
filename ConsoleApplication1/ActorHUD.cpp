#include "../UNIR-2D/UNIR-2D.h"
#include "ActorHUD.h"

ActorHUD::ActorHUD(Tablero* tablero) : m_tablero(tablero) {
}


// inicia () crea los elementos gráficos del HUD, como el fondo, el texto para mostrar las minas restantes y el tiempo transcurrido. 
// El método actualiza() se encarga de actualizar el texto del HUD con la información actual del tablero y el tiempo transcurrido desde el inicio del juego.

void ActorHUD::inicia() {
    ponPosicion(unir2d::Vector(0, 0));

    m_fondoHUD = new unir2d::Rectangulo(500, 55);
    m_fondoHUD->ponColor(unir2d::Color(30, 70, 84));
    m_fondoHUD->ponPosicion(unir2d::Vector(0, 0));
    agregaDibujo(m_fondoHUD);

    m_txtMinas = new unir2d::Texto("BitcountSingle-Variable");
    m_txtMinas->ponTamano(20);
    m_txtMinas->ponColor(unir2d::Color(255, 80, 80));
    m_txtMinas->ponPosicion(unir2d::Vector(15, 14));
    agregaDibujo(m_txtMinas);

    m_txtTiempo = new unir2d::Texto("BitcountSingle-Variable");
    m_txtTiempo->ponTamano(20);
    m_txtTiempo->ponColor(unir2d::Color(80, 200, 80));
    m_txtTiempo->ponPosicion(unir2d::Vector(280, 14));
    agregaDibujo(m_txtTiempo);
}

// termina () elimina los elementos gráficos del HUD de la pantalla y libera la memoria asignada a ellos.
void ActorHUD::termina() {
    if (m_fondoHUD)  { extraeDibujo(m_fondoHUD);  delete m_fondoHUD;  m_fondoHUD  = nullptr; }
    if (m_txtMinas)  { extraeDibujo(m_txtMinas);  delete m_txtMinas;  m_txtMinas  = nullptr; }
    if (m_txtTiempo) { extraeDibujo(m_txtTiempo); delete m_txtTiempo; m_txtTiempo = nullptr; }
}


// actualiza () se encarga de actualizar el texto del HUD con la información actual del tablero y el tiempo transcurrido desde el inicio del juego. 
// Si es la primera vez que se llama a actualiza(), se establece el tiempo de inicio con el valor de tiempo_seg. 
// Luego, se calcula el número de minas restantes restando las banderas colocadas al total de minas y se actualiza el texto correspondiente. 
// Finalmente, se calcula el tiempo transcurrido en segundos y se actualiza el texto del tiempo.
void ActorHUD::actualiza(double tiempo_seg) {
    if (m_tiempoInicio < 0.0) {
        m_tiempoInicio = tiempo_seg;
    }

    int minasRestantes = m_tablero->totalMinas() - m_tablero->banderasColocadas();
    m_txtMinas->ponCadena("Minas: " + std::to_string(minasRestantes));

    int segundos = (int)(tiempo_seg - m_tiempoInicio);
    m_txtTiempo->ponCadena("Tiempo: " + std::to_string(segundos) + "s");
}
