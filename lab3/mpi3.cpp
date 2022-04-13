#include <stdio.h>
#include <mpi.h>
#include <vector>

const int M = 4;

int main(int argc, char* argv[])
{
    int ProcNum, ProcRank, Recv = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    int* Send = new int[ProcNum];
    for ( int i=0; i < M; i++ )
    {   
        if (ProcRank == 0){
        Recv += 1;
        printf("\n Round %3d", Recv);
        }
        
        for (int j = 0; j<ProcNum; j++){
            Send[j] = Recv;
        }

        for(int j=0;j<ProcNum;j++){
            MPI_Scatter(Send, 1, MPI_INT, &Recv, 1, MPI_INT, j, MPI_COMM_WORLD);
            printf("\n%d -> %d: %d", ProcRank, (ProcRank + 1)%ProcNum, Recv);
            for (int j = 0; j<ProcNum; j++){
                Send[j] = Recv;
            }
        }
    }
    delete[] Send;
    MPI_Finalize();
    return 0;
}