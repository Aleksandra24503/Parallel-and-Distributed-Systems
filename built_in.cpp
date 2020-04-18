#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>
#include <math.h>


int main(int argc, char **argv)
{
        int myrank;
        int comm_size;
        int message;
        MPI_Status status;
        MPI_Init(&argc, &argv);

        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

        if(myrank==0)
        {
                message = 6;
                printf("comm_size: %d.\n", comm_size);
                printf("Process %d broadcasting integer %d using built in function.\n", myrank, message);
        }

        MPI_Bcast(&message, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if(myrank!=0)
        {
                printf("Process %d received the message %d.\n", myrank, message );
        }

        MPI_Finalize();
        return 0;
}