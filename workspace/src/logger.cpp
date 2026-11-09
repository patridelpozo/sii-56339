#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char **argv) {
    int fd;
    char buffer[1024];


   //En vez de crear una fifo nueva, el logger se conecta a la que ya esta creada en el servidor
    if ((fd = open("pipe_coor", O_RDONLY))<0) {
        perror("No puede abrirse el pipe_coor");
        return(1);
    }
    //Lee y se muestra por pantalla lo que emite el servidor
    while (read(fd, buffer, sizeof(buffer))>0) {
	printf("%s", buffer);
    }
    close(fd);
   
    return(0);
}
