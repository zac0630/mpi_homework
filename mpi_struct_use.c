//使用MPI_Type_struct
#include <mpi.h>
int main(int argc, char *argv[])
{
    int myrank, size;
    MPI_Comm comm; //通讯子
    MPI_Init(&argc, &argv);
    MPI_Comm_dup(MPI_COMM_WORLD, &comm); //复制产生一个新通信器，确保库函数中的通信不会与程序的其他通信相互干扰
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &myrank);

    int tag = 1;
    //定义结构体，由3个int,2个float,5个char组成。
    struct my_data_type
    {
        int i[3];
        float f[2];
        char c[5];
    };
    struct my_data_type mydata;

    //构造结构体新类型
    MPI_Datatype submat;
    int blocklens_array[3] = {3, 2, 5};
    MPI_Aint displs_array[3];
    MPI_Datatype old_type_array[3] = {MPI_INT, MPI_FLOAT, MPI_CHAR};

    //使用地址函数计算偏移
    MPI_Address(&mydata.f[0], &displs_array[1]); //第一个double型相对于MPI_BOTTOM的偏移
    MPI_Address(&mydata.c[0], &displs_array[2]); //第一个char型相对于MPI_BOTTOM的偏移
    MPI_Address(&mydata.i[0], &displs_array[0]);
    displs_array[2] = displs_array[2] - displs_array[0]; //数据块与首地址的偏移量
    displs_array[1] = displs_array[1] - displs_array[0];
    displs_array[0] = 0;

    MPI_Type_struct(3,blocklens_array,displs_array,old_type_array, &submat); //将结构体定义为新类型
    MPI_Type_commit(&submat);

    struct my_data_type x[10];
    struct my_data_type y[10];
    //0号进程发送5个x的元素
    if(myrank == 0)
        MPI_Send(x, 5, submat, 1, tag, comm);

    //1号进程接收5个x的元素
    if(myrank = 1)
        MPI_Recv(y, 5, submat, 0, tag, comm, MPI_STATUS_IGNORE);

    MPI_Finalize();
    return 0;
}
