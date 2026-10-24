#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "DatosMemCompartida.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc,char* argv[])
{
	int i;
	DatosMemCompartida* dat;
	//char *direccion;
	int fd;
	
	fd=open(argv[1], O_RDWR);
	if (fd == -1)
	{
		perror("Error al abrir el archivo"); 
		return 1;
	}
	
	dat=(DatosMemCompartida*)mmap(NULL, sizeof(DatosMemCompartida), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (dat == (DatosMemCompartida*) MAP_FAILED)
	{
		perror("Error en la proyeccion mmap"); 
		close(fd);
		return 1;
	}
	close(fd);
	

	while(1)
	{
		usleep(25000);
		//PRUEBA: Para evitar el rebote en el movimiento de la raqueta del jugador 1 usando el bot
		//float diferencia = dat->esfera.centro.y - dat->jugador.y1; //Para ver cual esta más arriba o abajo y a que distancia estan
		//float umbral = 3.0f; //Es como un margen de tolerancia para que la raqueta no se mueva más cuando la esfera entra en ese umbral
		
		/*if (diferencia>umbral){
			dat->accion=1; //Mover arriba
		}
		else if (diferencia<umbral){
			dat->accion=-1; //Mover abajo
		}
		else {
			dat->accion=0; //Ya esta todo alineado
		}*/
		if (dat->esfera.centro.y > dat->jugador1.y1) {
			dat->accion=1; //Mover arriba
		}
		else if(dat->esfera.centro.y < dat->jugador1.y1){
			dat->accion=-1; //Mover abajo
		}
		else{
			dat->accion=0; //No se mueve
		}
		
	}
	return 0;
}
