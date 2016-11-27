#include <iostream>
#include <windows.h>
#include "miniwin.h"

using namespace miniwin;
int main(){
    vredimensiona(250,500);
}
/*char mapa[10][20] = {
"###################",
"#                 #",
"#                 #",
"#                 #",
"#                 #",
"#                 #",
"#                 #",
"#                 #",
"#                 #",
"###################"
};
char mapa2[10][20] = {
"###################",
"#                 #",
"#                 #",
"#                 #",
"#                 #",
"#                 #",
"#                 #",
"#                 #",
"#                 #",
"###################"
};
char pieza = '@';
bool ejecucion = true;
int x = 9;
int y = 1;
void reiniciar(){
    x = 9;
    y = 1;
}
int filallena = 0;
int main()
{

    while(ejecucion==true)
    {
        if (filallena==16){
            int i = 8;
            for (i;i>1;i--){
                mapa[i][x]=mapa[i-1][x];}
        }
        system("cls");
        for(int visualizar=0; visualizar<10;visualizar++){
            cout << mapa[visualizar] << endl;}
        mapa[y][x]=pieza;
        system("pause>nul");
        if(GetAsyncKeyState(VK_DOWN)){
            int y2 = y+1;
            if(mapa[y2][x] != '#'){
                if(mapa[y2][x]=='@'){
                    mapa[y][x]=='@';
                    reiniciar();
                }
                if(y2==8){
                    mapa[y][x] = ' ';
                    y++;
                    mapa[y][x] = '@';
                    reiniciar();
                    filallena++;
                }
                else
                    mapa[y][x] = ' ';
                    y++;
                    mapa[y][x] = pieza;
            }
        }
        if(GetAsyncKeyState(VK_RIGHT)){
            int x2 = x+1;
            if(mapa[y][x2] != '#'){
                mapa[y][x] = ' ';
                x++;
                mapa[y][x] = pieza;
            }
        }
        if(GetAsyncKeyState(VK_LEFT)){
            int x2 = x-1;
            if(mapa[y][x2] != '#'){
                mapa[y][x] = ' ';
                x--;
                mapa[y][x] = pieza;
            }
        }
        if(GetAsyncKeyState(VK_ESCAPE)){
            ejecucion=false;
        }
    }

    system("cls");
    cout << "GAME OVER";
    return 0;
}*/

