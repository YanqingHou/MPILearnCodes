#include <stdio.h>
#include <mpi.h>

int is_lp(long long x)
{
    long long t = x * x, i = 10;
    while (i < t)
    {
        long long l = t / i, r = t % i;
        if (l + r == x)
            return 1;
        i *= 10;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int myid, numprocs, source;
    const int N = 100000000;

    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

    printf("I'm %d of %d\n", myid, numprocs);
    int start = myid * (N / numprocs), stop = (myid + 1) * (N / numprocs);
    if (myid == numprocs - 1)
        stop = N;
    printf("start from %d to %d\n", start, stop);
    int ans = 0, i;
    for (i = start; i < stop; i++)
        if (is_lp(i))
            ans += 1;
    printf("%d finished calculation with %d numbers\n", myid, ans);

    if (myid != 0)
    {
        MPI_Send(&ans, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        int tmp;
        for (source = 1; source < numprocs; source++)
        {
            MPI_Recv(&tmp, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status);
            printf("from %d: %d\n", source, tmp);
            ans += tmp;
        }
        printf("final ans: %d\n", ans);
    }

    MPI_Finalize();
    return 0;
}