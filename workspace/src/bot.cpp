#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "DatosMemCompartida.h" // Tus estructuras base de la P3
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>

int main(int argc, char* argv[])
{
    int fd_teclas, fd_coor;
    
    // Abrir la tubería de teclas (pipe_teclas) en modo escritura
    fd_teclas = open("pipe_teclas", O_WRONLY);
    if (fd_teclas == -1) {
        perror("Error al abrir pipe_teclas en el bot"); 
        return 1;
    }

    // Abrir la tubería de coordenadas (pipe_coor) para leer dónde está la pelota
    fd_coor = open("pipe_coor", O_RDONLY);
    if (fd_coor == -1) {
        perror("Error al abrir pipe_coor en el bot"); 
        close(fd_teclas);
        return 1;
    }
    
    printf("Bot conectado correctamente.\n");

    DatosMemCompartida dat;
    char buffer[1024];

    while(1)
    {
        usleep(25000); // Pausa para sincronizar con el bucle del servidor

        // Leemos las coordenadas que emite el servidor por pipe_coor
        int n = read(fd_coor, buffer, sizeof(buffer) - 1);
        if (n > 0) {
            buffer[n] = '\0';
            
            if (strstr(buffer, "marca") != NULL) {
                continue; // Si el servidor manda el texto de gol, lo ignoramos
            }
            
            float j2_x1_dummy, j2_y1_dummy, j2_x2_dummy, j2_y2_dummy;
            int p1_dummy, p2_dummy; // Variables temporales para los puntos
            
            sscanf(buffer, "%f %f %f %f %f %f %f %f %f %f %d %d", 
                   &dat.esfera.centro.x, &dat.esfera.centro.y, 
                   &dat.jugador1.x1, &dat.jugador1.y1, &dat.jugador1.x2, &dat.jugador1.y2, 
                   &j2_x1_dummy, &j2_y1_dummy, &j2_x2_dummy, &j2_y2_dummy, 
                   &p1_dummy, &p2_dummy); // <--- Usamos variables temporales en lugar de dat.puntos1/2
        }

        // LÓGICA DE LA PRÁCTICA 3
        if (dat.esfera.centro.y > dat.jugador1.y1) {
            dat.accion = 1; // Arriba
        }
        else if (dat.esfera.centro.y < dat.jugador1.y1) {
            dat.accion = -1; // Abajo
        }
        else {
            dat.accion = 0;
        }
        
        // ENVÍO DE LA TECLA POR EL FIFO
        char cadena_tecla[10];
        if (dat.accion == 1) {
            sprintf(cadena_tecla, "o");
            write(fd_teclas, cadena_tecla, strlen(cadena_tecla) + 1);
        }
        else if (dat.accion == -1) {
            sprintf(cadena_tecla, "l");
            write(fd_teclas, cadena_tecla, strlen(cadena_tecla) + 1);
        }
    }
    
    close(fd_teclas);
    close(fd_coor);
    return 0;
}
