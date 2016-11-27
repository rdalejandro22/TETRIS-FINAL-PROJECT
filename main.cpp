#include "miniwin.h"
#include <cstdlib>
#include <vector>
#include <time.h>
#include <sstream>
using namespace std;
using namespace miniwin;
const int TAM = 25;
const int FILAS = 20;
const int COLUMNAS = 10;
typedef int Tablero[COLUMNAS][FILAS];
void cuadrado(int x, int y){
    rectangulo_lleno(20+1 + x * TAM,
                     20+1 + y * TAM,
                     20+x * TAM + TAM,
                     20+y * TAM + TAM);
}
class Coordenadas
{
    int x, y;
public:
    Coordenadas(){
        x=0;
        y=0;
    }
    Coordenadas(int a, int b){
        x=a;
        y=b;
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
    void setX(int a)
    {
        x = a;
    }
    void setY(int b)
    {
        y = b;
    }
    void aumentarY(int n){
        y += n;
    }
    void aumentarX(int n){
        x += n;
    }
};
Coordenadas extremos[7][3] = {
    {{1,0}  , {0,1}  , {1,1}  },
    {{1,0}  , {-1,1} , {0,1}  },
    {{0,1}  , {1,1}  , {-1,0} },
    {{0,1}  , {0,-1} , {1,1}  },
    {{0,1}  , {0,-1} , {-1,1} },
    {{0,1}  , {0,-1} , {0,2}  },
    {{-1,0} , {1,0}  , {0,1}  }
};
class Pieza
{
    int abc;
    Coordenadas pivote;
    Coordenadas perifs[3];
public:
    Pieza(){}
    Pieza(std::vector <Coordenadas> extremos)
    {
        pivote.setX(13);
        pivote.setY(2);
        abc = 1 + rand()%6;
        for(int i = 0; i < 3; i++){
            perifs[i] = extremos[i];
        }
    }
    Coordenadas return_pivote()
    {
        return pivote;
    }
    Coordenadas posicion(int n) {
        Coordenadas temp(pivote.getX(), pivote.getY());
        if(n != 0){
            temp.aumentarX(perifs[n-1].getX());
            temp.aumentarY(perifs[n-1].getY());
        }
        return temp;
    }
    void pieza_inicio(std::vector <Coordenadas> extremos)
    {
        pivote.setX(13);
        pivote.setY(2);
        abc = 1 + rand()%6;
        for(int i = 0; i < 3; i++){
            perifs[i] = extremos[i];
        }
    }
    void set_pivote(int a,int b){
        pivote.setX(a);
        pivote.setY(b);
    }
    int getColor()
    {
        return abc;
    }
    void mover_abajo(){
        pivote.aumentarY(1);
    }
    void mover_derecha(){
        pivote.aumentarX(1);
    }
    void mover_izquierda(){
        pivote.aumentarX(-1);
    }
    void rotar_derecha(){
        for(int i = 0; i < 3; i++){
            int n = perifs[i].getX();
            int m = perifs[i].getY();
            perifs[i].setX(-m);
            perifs[i].setY(n);
        }
    }

};
void pintar(Pieza &P)
{
        color(P.getColor());
        for(int i = 0; i < 4; i++){
            Coordenadas c = P.posicion(i);
            cuadrado(c.getX(), c.getY());
    }
}
std::vector <Coordenadas> pieza_aleatoria(){
    std::vector <Coordenadas> temp;
    int aleatorio = rand() % 7;
    for(int i = 0; i < 3; i++){
        temp.push_back(extremos[aleatorio][i]);
    }
    return temp;
}
void tablero_vacio(Tablero &T){
    for(int i=0; i < COLUMNAS; i++){
        for(int j=0; j < FILAS; j++){
            T[i][j] = NEGRO; //Casilla vacia
        }
    }
}
void tablero_lleno(const Tablero &T){
    for(int i=0; i < COLUMNAS; i++){
        for(int j=0; j < FILAS; j++){
            color(T[i][j]); //Casilla vacia
            cuadrado(i, j);
        }
    }
}
void tablero_fijar(Tablero &T, Pieza &P){
    for(int i = 0; i < 4; i++){
        Coordenadas c = P.posicion(i);
        T[c.getX()][c.getY()] = P.getColor();
    }
}
bool tablero_conflicto(const Tablero &T, Pieza &P){
    for(int i = 0; i < 4; i++){
        Coordenadas c = P.posicion(i);
        if(c.getX() < 0 || c.getX() >= COLUMNAS){
            return true;}
        if(c.getY() < 0 || c.getY() >= FILAS){
            return true;}
        if(T[c.getX()][c.getY()] != NEGRO){
            return true;}
    }
    return false;
}
bool tablero_filallena(Tablero &T, int fila){
        for(int i = 0; i < COLUMNAS; i++){
            if(T[i][fila] == NEGRO)
                return false;
        }
}
void tablero_colapsa(Tablero &T, int fila){
    for(int j = fila; j > 0; j--){
        for(int i = 0; i < COLUMNAS; i++){
            T[i][j] = T[i][j-1];
        }
    }
    for(int i = 0; i < COLUMNAS; i++){
        T[i][0] = NEGRO;
    }
}
int tablero_cuentalineas(Tablero &T){
    int fila = FILAS-1;
    int cont = 0;
    while(fila>=0){
        if(tablero_filallena(T, fila)){
            tablero_colapsa(T, fila);
            cont++;
        }
        else
            fila--;
    }
    return cont;
}
string convertir(int a)
{
    stringstream sout;
    sout << a;
    return sout.str();
}
void repinta(const Tablero &T, Pieza &P, Pieza &sig, int puntos, int nivel)
{
    const int ancho = TAM*COLUMNAS;
    const int alto = TAM*FILAS;
    borra();
    tablero_lleno(T);
    color(BLANCO);
    linea(20, 20, 20, 20 + TAM * FILAS);
    linea(20, 20 + alto, 20 + ancho, 20 + alto);
    linea(20 + ancho, 20 + alto, 20 + ancho, 20);
    texto(60 + ancho, 20, "Pieza Siguiente");
    texto(60 + ancho, 170, "Nivel");
    texto(60 + ancho, 320, "Puntaje");
    texto(60 + ancho, 370, convertir(puntos));
    texto(60 + ancho, 220, convertir(nivel+1));
    pintar(P);
    pintar(sig);
    refresca();
}
void gameover(){
    color(BLANCO);
    texto(140,240,"GAME OVER");
    refresca();
    espera(3000);
    vcierra();
}
const int puntos_nivel[10] = {10,20,30,40,50,60,70,80,90,100};
const int rapidez[10] =      {30,27,25,23,20,17,15,10,7,5};
int main()
{
    srand(time(NULL));
    vredimensiona(TAM * COLUMNAS + 200, TAM * FILAS + 100);

    int ticks = 0;
    int puntos = 0;
    int nivel = 0;

    int n = 1 + rand() % 6;
    Tablero T;
    tablero_vacio(T);
    Pieza sig(pieza_aleatoria());
    Pieza z(pieza_aleatoria());
    z.set_pivote(5,2);
    pintar(z);
    repinta(T,z,sig,puntos,nivel);

    int t = tecla();
    while(t != ESCAPE){
        Pieza copia = z;
        if(t == NINGUNA && ticks > rapidez[nivel]){
            ticks=0;
            t = ABAJO;}
        if(t == ABAJO){
            z.mover_abajo();
        }
        if(t == ARRIBA){
            z.rotar_derecha();
        }
        if(t == IZQUIERDA){
            z.mover_izquierda();
        }
        if(t == DERECHA){
            z.mover_derecha();
        }
        if(t == ESPACIO)
        {
            while(tablero_conflicto(T,z)){
                z.mover_abajo();
            }

        }
        if(t == 'N')
            nivel++;
        if(tablero_conflicto(T,z)){
            z = copia;
            if(t == ABAJO){
                tablero_fijar(T, z);
                int cont = tablero_cuentalineas(T);
                puntos += cont;
                if(puntos > puntos_nivel[nivel])
                    nivel++;
                z = sig;
                sig.pieza_inicio(pieza_aleatoria());
                z.set_pivote(5,2);
                if(tablero_conflicto(T,z))
                {
                    gameover();
                }
            }
        }
        if(t != NINGUNA){
            repinta(T,z,sig,puntos,nivel);
        }
        espera(30);
        ticks++;
        t = tecla();
    }
    vcierra();
    return 0;
}
