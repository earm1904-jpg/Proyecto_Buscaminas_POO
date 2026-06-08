#pragma once

#include "../UNIR-2D/UNIR-2D.h"


class JuegoBuscaminas;

class ActorInicio : public unir2d::ActorBase {


    // En la parte public de la clase ActorInicio se declara el constructor que recibe un puntero al juego y el método jugadorListoPara() que devuelve un booleano indicando si el jugador ha hecho clic en el botón para comenzar a jugar.
public:
    ActorInicio(JuegoBuscaminas* juego);

    bool jugadorListoPara() const;


    // Para la parte protected de la clase ActorInicio se declaran los métodos inicia(), termina() y actualiza() que se sobreescriben para crear los elementos gráficos de la pantalla de inicio, detectar el clic del ratón en el botón y actualizar el estado listo para iniciar el juego.1
protected:
    void inicia()                     override;
    void termina()                    override;
    void actualiza(double tiempo_seg) override;

    // En la parte privada de la clase ActorInicio se declaran los atributos necesarios para almacenar el puntero al juego, el estado listo para iniciar el juego y los elementos gráficos de la pantalla de inicio, como el fondo, el título, las instrucciones y el botón para jugar.

private:
    JuegoBuscaminas*    m_juego;
    bool                m_listo = false;

    unir2d::Rectangulo* m_fondo       = nullptr;
    unir2d::Texto*      m_txtTitulo   = nullptr;
    unir2d::Texto*      m_txtInstruc1 = nullptr;
    unir2d::Texto*      m_txtInstruc2 = nullptr;
    unir2d::Texto*      m_txtInstruc3 = nullptr;
    unir2d::Rectangulo* m_boton       = nullptr;
    unir2d::Imagen* m_imagen1 = nullptr;
    unir2d::Imagen* m_imagen2 = nullptr;
    unir2d::Textura* m_textura1 = nullptr;
    unir2d::Textura* m_textura2 = nullptr;
    unir2d::Texto*      m_txtBoton    = nullptr;
};
