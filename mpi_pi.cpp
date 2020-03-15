#include <mpi.h>

/*
 * This program computes pi number by integrating the function
 * dx/(1 + x^2) from [0,1] then multiple by 4
 * */

int main(int argc, char *argv[])
{
    int myid, num_procs, i, n=0;
    double sum, width, local, mypi, pi;
    double start=0, stop=0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    
    // root process: recieve parameter and send to worker
    if(myid == 0)
    {
        std::cout << "please give n = ";
        std::cin >> n;
        std::cout << std::endl;
        start = MPI_Wtime();
    }
    
    // all process send the data to others
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
    // reduce the operation on data from all processes and put the result on root process
    if(myid == 0)
    {
        std::cout << "PI is " << pi << "\n";
        stop = MPI_Wtime();
        std::cout << "Time: " << stop-start << "\n";
    }
    // finish MPI enviroment
    MPI_Finalize();
    return 0;

}
