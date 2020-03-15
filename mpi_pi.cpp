#include <mpi.h>
#include <math.h>

int main(int argc, char *argv[])
{
    int myid, num_procs, i, proc_len, n=0;
    double sum, width, local, mypi, pi;
    double start=0, stop=0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    
    // master node: recieve parameter and send to worker
    if(myid == 0)
    {
        std::cout << "please give n = ";
        std::cin >> n;
        std::cout << std::endl;
        start = MPI_Wtime();
    }
    
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    width = 1.0/n;
    sum = 0;
    for(i=myid; i<n; i+=num_procs)
    {
        local = width*((double)i + 0.5);
        sum += 4.0/(1.0 + local*local);
    }

    mypi = width*sum;
    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(myid == 0)
    {
        std::cout << "PI is " << pi;
        stop = MPI_Wtime();
        std::cout << "Time: " << stop-start;
    }
    
    MPI_Finalize();
    return 0;

}
