//使用MPI_Type_indexed来构造新类型
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
    //题目中没有告诉我A矩阵的总行数和总列数是多少
    //假设将A平均分成nxn个小的mxm矩阵
    int m = 5;
    int n = 2;

    MPI_Datatype submat;

    int count = 2*m;    //一共有2*m个数据块
    int *lenarr[2*m];   //每个数据块的长度
    int *indexarr[2*m]; //每个元素的起始位置在原始数据中的index

    for(int i = 0; i < 2*m; i++){
        lenarr[i] = m;      //每个数据块的长度均是m
    }

    for(int i = 0; i < m; i++){
        indexarr[i] = i * n*m;  //A00子矩阵每行的偏移，n*m表示的是总列数
    }
    for(int i = m; i < 2*m; i++){
        indexarr[i] = 2*m*n*m + i * n*m;  //2*m*n*m表示的是A20的第0行第0列相对于起始位置的偏移
    }

    MPI_Type_indexed(count, lenarr, indexarr, MPI_INT, &submat);   //将A0定义为新类型
    MPI_Type_commit(&submat);


    MPI_Finalize();
    return 0;
}
