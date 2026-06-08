#include "../UNIR-2D/UNIR-2D.h"
#include "ActorInicio.h"
#include "JuegoBuscaminas.h"

// ActorInicio sirve para mostrar la pantalla de inicio del juego, con el título, instrucciones y un botón para comenzar a jugar. 
// El jugador debe hacer clic en el botón "JUGAR" para indicar que está listo para comenzar la partida. 
// El método actualiza() detecta el clic del ratón y establece el estado listo para iniciar el juego.

// Declaracion de Boton jugar en el centro inferior
static const float BTN_X = 170.0f;
static const float BTN_Y = 480.0f;
static const float BTN_W = 160.0f;
static const float BTN_H =  45.0f;

ActorInicio::ActorInicio(JuegoBuscaminas* juego) : m_juego(juego) {
}

bool ActorInicio::jugadorListoPara() const {
    return m_listo;
}


//inicia () crea los elementos gráficos de la pantalla de inicio, como el fondo, el título, las instrucciones y el botón para jugar.
void ActorInicio::inicia() {
    ponPosicion(unir2d::Vector(0, 0));

    m_fondo = new unir2d::Rectangulo(500, 560);
    m_fondo->ponColor(unir2d::Color(39, 71, 84));
    m_fondo->ponPosicion(unir2d::Vector(0, 0));
    agregaDibujo(m_fondo);

    m_txtTitulo = new unir2d::Texto("Sixtyfour-Regular");
    m_txtTitulo->ponTamano(40);
    m_txtTitulo->ponColor(unir2d::Color(42, 157, 144));
    m_txtTitulo->ponPosicion(unir2d::Vector(70, 80));
    m_txtTitulo->ponCadena("BUSCAMINAS");
    agregaDibujo(m_txtTitulo);

    m_txtInstruc1 = new unir2d::Texto("BitcountSingle-Variable");
    m_txtInstruc1->ponTamano(20);
    m_txtInstruc1->ponColor(unir2d::Color(249, 197, 78));
    m_txtInstruc1->ponPosicion(unir2d::Vector(150, 200));
    m_txtInstruc1->ponCadena("Revelar celda");
    agregaDibujo(m_txtInstruc1);
    
    m_imagen1 = new unir2d::Imagen();
    m_textura1 = new unir2d::Textura{};
    std::filesystem::path archivo = std::filesystem::current_path();
    archivo = archivo / "imagenes" / "clic_izquierdo.png";
    m_textura1->carga(archivo);
    m_imagen1->asigna(m_textura1);
    m_imagen1->ponPosicion(unir2d::Vector(80, 150));
    agregaDibujo(m_imagen1);


    m_txtInstruc2 = new unir2d::Texto("BitcountSingle-Variable");
    m_txtInstruc2->ponTamano(20);
    m_txtInstruc2->ponColor(unir2d::Color(249, 197, 78));
    m_txtInstruc2->ponPosicion(unir2d::Vector(100, 280));
    m_txtInstruc2->ponCadena("Colocar bandera (P)");
    agregaDibujo(m_txtInstruc2);

    m_imagen2 = new unir2d::Imagen();
    m_textura2 = new unir2d::Textura{};
    std::filesystem::path archivo_1 = std::filesystem::current_path();
    archivo_1 = archivo_1 / "imagenes" / "clic_derecho.png";
    m_textura2->carga(archivo_1);
    m_imagen2->asigna(m_textura2);
    m_imagen2->ponPosicion(unir2d::Vector(300, 250));
    agregaDibujo(m_imagen2);

    m_txtInstruc3 = new unir2d::Texto("BitcountSingle-Variable");
    m_txtInstruc3->ponTamano(21);
    m_txtInstruc3->ponColor(unir2d::Color(249, 197, 78));
    m_txtInstruc3->ponPosicion(unir2d::Vector(88, 380));
    m_txtInstruc3->ponCadena("OBJETIVO:\ndescubrir todas las\nceldas sin minas.");
    agregaDibujo(m_txtInstruc3);

    m_boton = new unir2d::Rectangulo(BTN_W, BTN_H);
    m_boton->ponColor(unir2d::Color(231, 110, 80));
    m_boton->ponPosicion(unir2d::Vector(BTN_X, BTN_Y));
    agregaDibujo(m_boton);

    m_txtBoton = new unir2d::Texto("BitcountSingle-Variable");
    m_txtBoton->ponTamano(25);
    m_txtBoton->ponColor(unir2d::Color(255, 255, 255));
    m_txtBoton->ponPosicion(unir2d::Vector(BTN_X + 38, BTN_Y + 8));
    m_txtBoton->ponCadena("JUGAR");
    agregaDibujo(m_txtBoton);
}

// termina elimina los elementos gráficos de la pantalla de inicio, liberando la memoria y extrayéndolos de la lista de dibujos del actor.
void ActorInicio::termina() {
    if (m_fondo)       { extraeDibujo(m_fondo);       delete m_fondo;       m_fondo       = nullptr; }
    if (m_txtTitulo)   { extraeDibujo(m_txtTitulo);   delete m_txtTitulo;   m_txtTitulo   = nullptr; }
    if (m_txtInstruc1) { extraeDibujo(m_txtInstruc1); delete m_txtInstruc1; m_txtInstruc1 = nullptr; }
    if (m_txtInstruc2) { extraeDibujo(m_txtInstruc2); delete m_txtInstruc2; m_txtInstruc2 = nullptr; }
    if (m_txtInstruc3) { extraeDibujo(m_txtInstruc3); delete m_txtInstruc3; m_txtInstruc3 = nullptr; }
    if (m_boton)       { extraeDibujo(m_boton);       delete m_boton;       m_boton       = nullptr; }
    if (m_txtBoton)    { extraeDibujo(m_txtBoton);    delete m_txtBoton;    m_txtBoton    = nullptr; }
}


// actualiza detecta si el jugador ha hecho clic en el botón "JUGAR". Si se detecta un clic dentro de las coordenadas del botón, se marca el estado listo para iniciar el juego.
void ActorInicio::actualiza(double /*tiempo_seg*/) {
    if (unir2d::Raton::pulsando(unir2d::BotonRaton::izquierda)) {
        unir2d::Vector pos = unir2d::Raton::posicion();
        if (pos.x() >= BTN_X && pos.x() <= BTN_X + BTN_W &&
            pos.y() >= BTN_Y && pos.y() <= BTN_Y + BTN_H) {
            unir2d::Raton::consumePulsado(unir2d::BotonRaton::izquierda);
            m_listo = true;
        }
    }
}
