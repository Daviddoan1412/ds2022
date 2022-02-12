

from mpi4py import MPI

def mpi():
    filename="send.txt"
    comm=MPI.COMM_WORLD
    Rank=comm.Get_rank()
    Size=comm.Get_size()

    if Rank==0:
        file=open(filename,'r')
        data=file.read()
        comm.send(data,dest=1,tag=1)
        print("-------Processing-----------")
    elif Rank==1:
        data=comm.recv(source=0,tag=1)
        filename_recv="recv.txt"
        filenew=open(filename_recv,'w')
        filenew.write(data)
        print("--------------Completed---------------")
if __name__ == '__main__':
    mpi()
