#include "../UNIR-2D/UNIR-2D.h"
#include "ActorEntrada.h"
#include "JuegoBuscaminas.h"
#include "ActorTablero.h"


ActorEntrada::ActorEntrada(JuegoBuscaminas* juego) : m_juego(juego) {
}

void ActorEntrada::inicia() {
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
// En este método se actualiza el estado de la partida y se transforman los pixles columnas y fuilas//
//////////////////////////////////////////////////////////////////////////////////////////////////////
void ActorEntrada::actualiza(double /*tiempo_seg*/) {
    if (m_juego->estadoPartida() != EstadoPartida::jugando) return;

    unir2d::Vector posMouse = unir2d::Raton::posicion();

    // Transformación de pixeles a columnas y filas
    int col = (int)((posMouse.x() - TABLERO_X) / TAMANO_CELDA);
    int fila = (int)((posMouse.y() - TABLERO_Y) / TAMANO_CELDA);

    //Validación de filas y columnas
    if (!coordenadasValidas(m_juego->tablero(), fila, col)) return;

    // Monitoreo y procesamiento del clic del Raton izquierdo y derecho
    if (unir2d::Raton::pulsando(unir2d::BotonRaton::izquierda)) {
        unir2d::Raton::consumePulsado(unir2d::BotonRaton::izquierda);
        procesarClic(fila, col);
    }

    if (unir2d::Raton::pulsando(unir2d::BotonRaton::derecha)) {
        unir2d::Raton::consumePulsado(unir2d::BotonRaton::derecha);
        procesarBandera(fila, col);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Porcesamiento de los clic del jugador en el tablero creando un puntero que apunta al tablero creado, ////////
// además se crea un referencia constante para evitar que se copio la estructura y se midifieque por accidente./
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ActorEntrada::procesarClic(int fila, int col) 
{
    Tablero* tablero = m_juego->tablero();
    const Celda& cel = tablero->celda(fila, col);

    //Verificar si es posibel pulsar la celda
    if (cel.revelada || cel.tieneBandera) return;

    //Comprobar si hay una mina en la celda seleccionada y si es así retrna el estado del juego a "perdido"
    if (cel.tieneMina) {
        tablero->revelar(fila, col);
        m_juego->setEstadoPartida(EstadoPartida::perdido);
        return;
    }

    // Método para:
    // Descubrir la celda 
    // En caso que no tenga mina esa celda descubre celdas vecinas
    //Repite el proceso recursivamente.
    revelarRecursivo(tablero, fila, col);

    // Compbrueba la victoria del jugador y si todas las celdas están decubiertas
    if (comprobarVictoria(tablero)) {
        m_juego->setEstadoPartida(EstadoPartida::ganado);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
// solo se ejecuta cuando el jugador hace clic derecho, para indicar en el tablero una posible mina//
//////////////////////////////////////////////////////////////////////////////////////////////////////
void ActorEntrada::procesarBandera(int fila, int col) {
    Tablero* tablero = m_juego->tablero();

    //Verifica que la celta no esté descubirta
    if (!tablero->celda(fila, col).revelada) {
        tablero->alternarBandera(fila, col);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Desarrollo del método Recursivo resive un puntero del Tablero, fila y colimna a descubrir automáticamete///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ActorEntrada::revelarRecursivo(Tablero* tablero, int fila, int col) {
   
    //Veridficacuón que las coordenadas existan dentro del tablero
    if (!coordenadasValidas(tablero, fila, col)) return;
    
    // Obptención de la celda actual como referencia
    const Celda& cel = tablero->celda(fila, col);

    //Casos por los cuales no debe revelarse la celda: Ya esta revelada, tiene una bandera o está marcada como una mina
    if (cel.revelada || cel.tieneBandera || cel.tieneMina) return;

    // llamado al método revelar de la clase Tablero
    tablero->revelar(fila, col);

    //VErificación de minas cercanas, recorre y descubrir vecinos cercanos en 8 direcciones posibles

    if (cel.minasCercanas == 0) {
        int desplazamientos[8][2] = {
            {-1,-1}, {-1,0}, {-1,1},
            { 0,-1},          { 0,1},
            { 1,-1}, { 1,0}, { 1,1}
        };

        //Recorrer el desplazamiento  y calcula la posición vecina
        for (auto& d : desplazamientos) {

            //LLamada al recursivo
            revelarRecursivo(tablero, fila + d[0], col + d[1]);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Método para comprobar la victoria del Jugador
/// Compruba la cantidad de filas y columnas y el total de minas
/// Llamar al méttodo celdasReveladas de la clase Tablero comparando la celdas revelada con las celas sin minas
/////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ActorEntrada::comprobarVictoria(Tablero* tablero) const {
    int celdasSinMina = tablero->filas() * tablero->columnas() - tablero->totalMinas();
    return tablero->celdasReveladas() >= celdasSinMina;
}


/// Compruba las psociones validas dentro del tablero con condiciones que se deben cumplir para que retorne un true
bool ActorEntrada::coordenadasValidas(Tablero* tablero, int fila, int col) const {
    return 
        fila >= 0 && 
        fila < tablero->filas() &&
        col >= 0 && 
        col < tablero->columnas();
}
