
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>
#include <math.h>

void ONE_TO_ALL_BROADCAST(int d, int my_ID, int &X)
{
        MPI_Status status;
        int mask = pow(2, d) - 1;
        int i;
        for(i = d-1; i>=0; i--)
        {
                int twotoi=pow(2,i);
                mask = mask ^ twotoi;

                if((my_ID & mask)==0)
                {
                        if((my_ID & twotoi)==0)
                        {
                                int dest = my_ID ^ twotoi;
                                 printf("Process %d is sending the message %d to process %d.\n", my_ID,X, dest);
                                MPI_Send(&X, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
                                printf("Process %d sent the message %d to process %d.\n", my_ID,X, dest);
                        }
                        else
                        {
                                int source = my_ID ^ twotoi;
                                  printf("Process %d will receive message from process %d.\n", my_ID, source, &status);
                                MPI_Recv(&X, 1, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
                                printf("Process %d received the message %d from process %d.\n", my_ID,X, source, &status);
                        }
                }


        }
}

int howManyDimensions(int p)
{
        return log2(p);

}
int main(int argc, char **argv)
{
        int myrank;
        int comm_size;
        int message;
        int number;
        //MPI_Status status;
        MPI_Init(&argc, &argv);
        sleep(5);
        MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
        MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

        if(myrank==0)
        {
                message = 153;
                printf("comm_size: %d.\n", comm_size);
                printf("Process %d broadcasting integer %d...\n", myrank, message);
        }
        ONE_TO_ALL_BROADCAST(howManyDimensions(comm_size), myrank, message);
        printf("Process %d finished with message %d.\n", myrank, message);

        MPI_Finalize();
        return 0;
}
