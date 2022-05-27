#include <mpi.h>
int main(int argc, char *argv[])
{
    int i;
    int myRank, size;
    int send[4], recv[32];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_myRank(MPI_COMM_WORLD, &myRank);

    for (i = 0; i < size; i++)
    {
        send[i] = myRank + 1; //每个进程内的数据
    }

    //向其他进程发送数据
    for (i = 0; i < size; i++)
    {
        MPI_Send(&send, 1, MPI_INT, i, myRank, MPI_COMM_WORLD);
    }

    //接收来自其他进程的数据，并放在recv+4*i的位置上
    for (i = 0; i < size; i++)
    {
        MPI_Recv(recv + i * 4, 1, MPI_INT, i, i, MPI_COMM_WORLD, &status);
    }

    MPI_Finalize();
}