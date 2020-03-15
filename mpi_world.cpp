#include "mpi.h"

int main(int argc, char *argv[])
{
    int myid, numprocs;
    
    MPI_Init(&argc, &argv); // establish the MPI environment
    
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    // MPI_COMM_WORLD: the default communicator (context and set of all processes)
    // MPI_Comm_size return the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);\
    // MPI_Comm_rank return the rank of the calling MPI process 

    std::cout << "Hello World from rank " << myid << "\n";
    if (myid ==0 ) std::cout << "MPI World size = " << numprocs << "\n";
    
    MPI_Finalize(); // MPI cleanup
    return 0;
}
