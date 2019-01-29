#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int myid, numprocs, source, msg_tag = 0;
    char msg[100];

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numprocs); //共启动几个进程
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);  //当前进程的编号（0～n-1）

    printf("I'm %d of %d\n", myid, numprocs);
    if (myid != 0)
    {
        int len = sprintf(msg, "hello from %d", myid);
        MPI_Send(msg, len, MPI_CHAR, 0, msg_tag, MPI_COMM_WORLD); //向id=0的进程发送信息
        printf("I'm %d, sending msg to proc 0\n",myid);

    }
    else
    {
        for (source = 1; source < numprocs; source++)
        {
            //从id=source的进程接受消息
            MPI_Recv(msg, 100, MPI_CHAR, source, msg_tag, MPI_COMM_WORLD, &status);
            printf("I'm proc %d, get msg from %d: %s\n", myid, source, msg);
        }
    }

    MPI_Finalize();
    return 0;
}