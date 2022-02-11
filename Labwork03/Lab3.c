#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mpi.h"

int main(int argc, char* argv[]){
    int rank,size,cout=1,dest=1,tag=1;
    char *file_name="send.txt";
    char *file_name_recv="recv.txt";
    FILE *file;
    MPI_Init(NULL,NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if(rank==0){
	file=fopen(file_name,"rb");
        MPI_Send(&file_name,cout,MPI_BYTE,dest,tag,MPI_COMM_WORLD);
        close(file);
    }
    else{
        MPI_Recv(&file_name_recv,cout,MPI_BYTE,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf ("Rank %d received",rank);
        file=fopen(file_name_recv,"wb");
        write(file);
        close(file);
    }
    MPI_Finalize();
    return 0;

}
