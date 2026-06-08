  #pragma once

#include "../UNIR-2D/UNIR-2D.h"
#include  "Tablero.h"

// ActorFin se encarga de mostrar la pantalla de fin del juego, con el resultado de la partida (ganado o perdido) y un botón para reiniciar el juego. 
// El jugador debe hacer clic en el botón "REINICIAR" para indicar que desea comenzar una nueva partida. El método actualiza() detecta el clic del ratón en el botón y establece el estado reiniciar para iniciar una nueva partida.

class ActorFin : public unir2d::ActorBase {
public:
    ActorFin(EstadoPartida resultado);

    bool reiniciar() const;

protected:
    void inicia()                     override;
    void termina()                    override;
    void actualiza(double tiempo_seg) override;

private:
    EstadoPartida       m_resultado;
    bool                m_reiniciar = false;

    unir2d::Rectangulo* m_fondo      = nullptr;
    unir2d::Texto*      m_txtResultado = nullptr;
    unir2d::Texto*      m_txtMensaje   = nullptr;
    unir2d::Rectangulo* m_boton        = nullptr;
    unir2d::Texto*      m_txtBoton     = nullptr;
    unir2d::Imagen* m_imagen1 = nullptr;
    unir2d::Imagen* m_imagen2 = nullptr;
    unir2d::Textura* m_textura1 = nullptr;
    unir2d::Textura* m_textura2 = nullptr;
};
