#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
    int rank, size;

    MPI_Init(&argc, &argv);
    // printf("Hello world!\n");
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("I am %d of %d\n", rank + 1, size);

    MPI_Finalize();
    return 0;
}
