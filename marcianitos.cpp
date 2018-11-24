#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

typedef int mapa[120][30];

void gotoxy(int x, int y);
void iniciar(mapa jugador,mapa marcianos,mapa misil_humano,mapa misil_ovni);
void dibujar(mapa matriz);
void vaciar(mapa matriz);
void mover(int &x,int y,mapa jugador);
void disparar(mapa misil_humano,int x,int y);
void animacion_misil(mapa misil_humano);
void fin_misil(mapa misil_humano);
void romper_ufo(mapa misil_humano,mapa marcianos);
void disparar_ufo(mapa marcianos,mapa misil_ovni,int random);
void animacion_misil_ufo(mapa misil_ovni);
int contar_marcianos(mapa marcianos);
void fin_misil_ovni(mapa misil_ovni);
void eliminar_jugador(mapa jugador,mapa misil_ovni,int x);
using namespace std;
int main(){
	mapa marcianos,misil_humano,misil_ovni,jugador;
	iniciar(jugador,marcianos,misil_humano,misil_ovni);
	int x=59;
	int y=28;
	int random;
	int contador;
	int tiempo=0;
	srand(time(NULL));
	system("color 72");
	while(true){
	
		dibujar(marcianos);
		
		dibujar(misil_humano);
		
		dibujar(misil_ovni);
		
		dibujar(jugador);
		fin_misil(misil_humano);
		fin_misil_ovni(misil_ovni);
		animacion_misil(misil_humano);
		animacion_misil_ufo(misil_ovni);
		mover(x,y,jugador);
		if((tiempo%5)==0){
			contador=contar_marcianos(marcianos);
			random=rand()%contador+1;
			disparar_ufo(marcianos,misil_ovni,random);
		}
		if(contador==0){
			system("cls");
			cout<<"HAS GANADO ENRAO"<<endl;
			system("pause");
			exit(1); 
		}
		eliminar_jugador(jugador,misil_ovni, x);
		disparar(misil_humano,x,y);
		romper_ufo(misil_humano,marcianos);
	    
	    
		
		Sleep(30);
		tiempo++;
		system("cls");
		
		
		
	}
}
void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}
void dibujar(mapa matriz){
	int x=0;
	int y=0;
	while(y<30){
		while(x<120){
			if(matriz[x][y]==1){
				gotoxy(x,y);
			
				cout<<"O";
			}
			if(matriz[x][y]==2){
			
				gotoxy(x,y);
				cout<<"X";
			}
			if(matriz[x][y]==3){
				gotoxy(x,y);
			
				cout<<"|";
			}
			if(matriz[x][y]==4){
				gotoxy(x,y);
				
				cout<<"!";
			}
			x++;
		}
		x=0;
		y++;
	}
}
void iniciar(mapa jugador,mapa marcianos,mapa misil_humano,mapa misil_ovni){
	vaciar(jugador);
	vaciar(marcianos);
	vaciar(misil_humano);
	vaciar(misil_ovni);
	int y=5;
	int cont=1;
	int x=30;
	jugador[59][28]=2;
	
	while(cont<60){
		marcianos[x][y]=1;
		y=cont%2+5;
		x++;
		cont++;
	}
	
}
void vaciar(mapa matriz){
	int x=0;
	int y=0;
	while(y<30){
		while(x<120){
			matriz[x][y]=0;
			x++;
		}
		x=0;
		y++;
	}
}
void mover(int &x,int y,mapa jugador){
	jugador[x][y]=0;
	if(GetAsyncKeyState(65)==-32767){
		x--;
	}
	else if(GetAsyncKeyState(68)==-32767){
		x++;
	}
	jugador[x][y]=2;
}
void disparar(mapa misil_humano,int x,int y){
	if(GetAsyncKeyState(VK_SPACE)==-32767){
		misil_humano[x][y-1]=3;
	}
}
void animacion_misil(mapa misil_humano){
	int x=0,y=0;
	while(y<30){
		while(x<120){
			if(misil_humano[x][y]==3){
				misil_humano[x][y]=0;
				misil_humano[x][y-1]=3;
			}
			x++;
		}
		x=0;
		y++;
	}
}
void fin_misil(mapa misil_humano){
	int x=0,y=0;
	
		while(x<120){
			if(misil_humano[x][y]==3){
				misil_humano[x][y]=0;
			}
			x++;	
		}
		
	

}
void romper_ufo(mapa misil_humano,mapa marcianos){
	int x=0,y=0;
	while(y<30){
		while(x<120){
			if(marcianos[x][y]==1){
				if(misil_humano[x][y]==3){
					marcianos[x][y]=0;
					misil_humano[x][y]=0;
					
				}
			}
			x++;
		}
		x=0;
		y++;
	}
}

void disparar_ufo(mapa marcianos,mapa misil_ovni,int random){
	
	int x=0,y=0,contador=1;
	while(y<30){
		while(x<120){
			if(marcianos[x][y]==1){
				if(random==contador){
					misil_ovni[x][y+1]=4;
				}
				contador++;
			}
			x++;
		}
		x=0;
		y++;
	}
}
void animacion_misil_ufo(mapa misil_ovni){
	int x=0,y=29;
	while(y>=0){
		while(x<120){
			if(misil_ovni[x][y]==4){
				misil_ovni[x][y]=0;
				misil_ovni[x][y+1]=4;
			}
			x++;
		}
		x=0;
		y--;
	}
}

int contar_marcianos(mapa marcianos){
	int x=0;
	int y=0;
	int contador=0;
	while(y<30){
		while(x<120){
			if(marcianos[x][y]==1){
				contador++;
			}
			x++;
		}
		x=0;
		y++;
	}
	return contador;
}
void fin_misil_ovni(mapa misil_ovni){
	int x=0;
	int y=29;
	while(x<120){
		if(misil_ovni[x][y]==4){
			misil_ovni[x][y]=0;
		}
		x++;
	}
}	
void eliminar_jugador(mapa jugador,mapa misil_ovni,int x){
     
     if(misil_ovni[x][28]==4){
     	system("cls");
     	cout<<"HAS PERDIDO";
     	exit(1);
	 }
	
}
