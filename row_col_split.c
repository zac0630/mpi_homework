//首先是按照列划分通讯子，然后是按照行划分通讯子
//p行q列
#include <mpi.h>
int main(int argc, char** argv) {
	int p = 10;
    int q = 10;

	MPI_Comm colComm, rowComm;
	int myRank, size;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	int colorCol = myRank % q;
	int keyRow = myRank / q;
	MPI_Comm_split(MPI_COMM_WORLD, colorCol, keyRow, &colComm);

	int colorRow = myRank / q;
	int keyCol = myRank % q;
	MPI_Comm_split(MPI_COMM_WORLD, colorRow, keyCol, &rowComm);

	MPI_Finalize();

	return 0;
}
