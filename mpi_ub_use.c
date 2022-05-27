#include <mpi.h>
int main(int argc, char *argv[])
{
    int myrank, size;
    MPI_Comm comm; //通讯子
    MPI_Init(&argc, &argv);
    MPI_Comm_dup(MPI_COMM_WORLD, &comm); //复制产生一个新通信器，确保库函数中的通信不会与程序的其他通信相互干扰
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &myrank);

    //定义矩阵mxm
    //假设将A平均分成nxn个小的mxm矩阵
    int m = 5;
    int n = 2;
    MPI_Datatype submat;

    MPI_Type_vector(m, m, n*m, MPI_INT, &submat);   //将A0定义为新类型
    MPI_Type_commit(&submat);

    //用MPI_UB和submat构造submat1
    MPI_Datatype submat1;

    int oldtype_nums = 2;
    int blocklens_array[2] = {1, 1};
    MPI_Datatype old_type_array[2] = {submat, MPI_UB};

    MPI_Aint displs_array[2];
    displs_array[1] = 4*(2*m*n*m);  //2*m是行数，n*m是总列数，一共有这么多个int型的数
    displs_array[0] = 0;

    MPI_Type_create_struct(2, blocklens_array, displs_array, old_type_array, &submat1);
    MPI_Type_commit(&submat1);

    MPI_Finalize();
    return 0;
}
