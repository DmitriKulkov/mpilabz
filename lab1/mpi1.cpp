#include <stdio.h>
#include <mpi.h>

const int M = 4;

int main(int argc, char* argv[])
{
    int ProcNum, ProcRank, Recv = 0;
    MPI_Status Status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    
    if (ProcRank == 0)
    {
        for ( int i=0; i <= M; i++ )
        {
            if (Recv == M){
                break;
            }
            Recv += 1;
            printf("\n Round %3d", Recv);
            MPI_Send(&Recv
            ,1,MPI_INT,(ProcRank + 1)%ProcNum,0,MPI_COMM_WORLD);
            printf("\n%d -> %d: %d", ProcRank, (ProcRank + 1)%ProcNum, Recv);
            MPI_Recv(&Recv, 1, MPI_INT, ProcNum - 1,
            MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
        }
     } else {
        for(int i = 0; i < M; i++) {
            MPI_Recv(&Recv, 1, MPI_INT, ProcRank - 1,
            MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
            MPI_Send(&Recv
            ,1,MPI_INT,(ProcRank + 1)%ProcNum,0,MPI_COMM_WORLD);
            printf("\n%d -> %d: %d", ProcRank, (ProcRank + 1)%ProcNum, Recv);
        }
    }
    MPI_Finalize();

    return 0;
}