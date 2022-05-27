#include <mpi.h>
int main(int argc, char** argv) {
	int p = 10;
    int q = 10;
    int data = 0;   //广播给所有进程的数据
	MPI_Comm colComm, rowComm;
	int myRank, size;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
    if(myRank == 0)
        data = 100;

	int colorCol = myRank % q;
	int keyRow = myRank / q;
	MPI_Comm_split(MPI_COMM_WORLD, colorCol, keyRow, &colComm);

    //首先在第0列进行广播
    MPI_Bcast(&data, 1, MPI_INT, 0, colComm);
    MPI_Barrier(MPI_COMM_WORLD);

	int colorRow = myRank / q;
	int keyCol = myRank % q;
	MPI_Comm_split(MPI_COMM_WORLD, colorRow, keyCol, &rowComm);

    //再在每列的行方向上进行广播
    MPI_Bcast(&data, 1, MPI_INT, 0, rowComm);
    MPI_Barrier(MPI_COMM_WORLD);
    
	MPI_Finalize();

	return 0;
}
