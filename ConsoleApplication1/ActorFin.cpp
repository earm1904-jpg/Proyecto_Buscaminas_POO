#include "../UNIR-2D/UNIR-2D.h"
#include "ActorFin.h"

static const float FIN_BTN_X = 130.0f;
static const float FIN_BTN_Y = 420.0f;
static const float FIN_BTN_W = 240.0f;
static const float FIN_BTN_H =  45.0f;

ActorFin::ActorFin(EstadoPartida resultado) : m_resultado(resultado) {
}

bool ActorFin::reiniciar() const {
    return m_reiniciar;
}

void ActorFin::inicia() {
    ponPosicion(unir2d::Vector(0, 0));

    unir2d::Color colorFondo = (m_resultado == EstadoPartida::ganado)
        ? unir2d::Color(39, 71, 84)
        : unir2d::Color(206, 93, 64);

    m_fondo = new unir2d::Rectangulo(500, 560);
    m_fondo->ponColor(colorFondo);
    m_fondo->ponPosicion(unir2d::Vector(0, 0));
    agregaDibujo(m_fondo);

    m_txtResultado = new unir2d::Texto("Sixtyfour-Regular");
    m_txtResultado->ponTamano(38);
    m_txtResultado->ponPosicion(unir2d::Vector(40, 120));

    if (m_resultado == EstadoPartida::ganado) {
        m_txtResultado->ponColor(unir2d::Color(231, 110, 80));
        m_txtResultado->ponCadena("HAS GANADO!");
        m_imagen1 = new unir2d::Imagen();
        m_textura1 = new unir2d::Textura{};
        std::filesystem::path archivo = std::filesystem::current_path();
        archivo = archivo / "imagenes" / "Ganar.png";
        m_textura1->carga(archivo);
        m_imagen1->asigna(m_textura1);
        m_imagen1->ponPosicion(unir2d::Vector(80, 180));
        agregaDibujo(m_imagen1);
    } else {
        m_txtResultado->ponColor(unir2d::Color(39, 71, 84));
        m_txtResultado->ponCadena("HAS PERDIDO!");
        m_imagen2 = new unir2d::Imagen();
        m_textura2 = new unir2d::Textura{};
        std::filesystem::path archivo_1 = std::filesystem::current_path();
        archivo_1 = archivo_1 / "imagenes" / "Perder.png";
        m_textura2->carga(archivo_1);
        m_imagen2->asigna(m_textura2);
        m_imagen2->ponPosicion(unir2d::Vector(80, 180));
        agregaDibujo(m_imagen2);
    }
    agregaDibujo(m_txtResultado);

    m_txtMensaje = new unir2d::Texto("BitcountSingle-Variable");
    m_txtMensaje->ponTamano(20);
    m_txtMensaje->ponColor(unir2d::Color(30, 70, 84));
    m_txtMensaje->ponPosicion(unir2d::Vector(250, 250));
    if (m_resultado == EstadoPartida::ganado) {
        m_txtMensaje->ponCadena("Todas las celdas\ndescubiertas!!");
    } else {
        m_txtMensaje->ponCadena("Pisaste una mina!!");
    }
    agregaDibujo(m_txtMensaje);

    m_boton = new unir2d::Rectangulo(FIN_BTN_W, FIN_BTN_H);
    m_boton->ponColor(unir2d::Color(30, 70, 84));
    m_boton->ponPosicion(unir2d::Vector(FIN_BTN_X, FIN_BTN_Y));
    agregaDibujo(m_boton);

    m_txtBoton = new unir2d::Texto("BitcountSingle-Variable");
    m_txtBoton->ponTamano(25);
    m_txtBoton->ponColor(unir2d::Color(255, 255, 255));
    m_txtBoton->ponCadena("JUGAR DE NUEVO");
    float txtX = FIN_BTN_X + (FIN_BTN_W - m_txtBoton->anchura()) / 2.0f;
    m_txtBoton->ponPosicion(unir2d::Vector(txtX, FIN_BTN_Y + 12));
    agregaDibujo(m_txtBoton);
}

void ActorFin::termina() {
    if (m_fondo)         { extraeDibujo(m_fondo);         delete m_fondo;         m_fondo         = nullptr; }
    if (m_txtResultado)  { extraeDibujo(m_txtResultado);  delete m_txtResultado;  m_txtResultado  = nullptr; }
    if (m_txtMensaje)    { extraeDibujo(m_txtMensaje);    delete m_txtMensaje;    m_txtMensaje    = nullptr; }
    if (m_boton)         { extraeDibujo(m_boton);         delete m_boton;         m_boton         = nullptr; }
    if (m_txtBoton)      { extraeDibujo(m_txtBoton);      delete m_txtBoton;      m_txtBoton      = nullptr; }
}

void ActorFin::actualiza(double /*tiempo_seg*/) {
    if (unir2d::Raton::pulsando(unir2d::BotonRaton::izquierda)) {
        unir2d::Vector pos = unir2d::Raton::posicion();
        if (pos.x() >= FIN_BTN_X && pos.x() <= FIN_BTN_X + FIN_BTN_W &&
            pos.y() >= FIN_BTN_Y && pos.y() <= FIN_BTN_Y + FIN_BTN_H) {
            unir2d::Raton::consumePulsado(unir2d::BotonRaton::izquierda);
            m_reiniciar = true;
        }
    }
}
