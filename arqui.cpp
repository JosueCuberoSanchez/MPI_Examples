#include <stdio.h>
#include <string>
#include "mpi.h" 

using namespace std;

int main(int argc, char **argv) {
	MPI_Init(&argc, &argv); //initialize the MPI environment
	int myid, numprocs, namelen, next, last, size;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs); //number of processes
	MPI_Comm_rank(MPI_COMM_WORLD,&myid); //my id
	MPI_Get_processor_name(processor_name,&namelen); //my processor

	// cout << myid << " in " << processor_name << endl;

	// Anillo

	/*
	int received = myid;
	next = (myid+1)%numprocs;
	last = (myid-1)%numprocs;

	//MPI_Send (&buf(dato a enviar), cuántos, tipo de datos, destino, etiqueta, Comunicador)
	MPI_Send (&received, 1, MPI_INT, next, 0, MPI_COMM_WORLD);

	//MPI_Recv (&buf(donde recibo el dato), cuántos, tipo de datos, fuente, etiqueta, Comunicador, &status)
	MPI_Recv (&received, 1, MPI_INT, myid-1, 0, MPI_COMM_WORLD, 0);

	cout << "Se recibe en " << myid << " a " << received << endl;*/

	// Fin de anillo

	// Broadcast

	/* //MPI_Bcast (&BUFFER(dato a mandar), COUNT, DATATYPE, ROOT, COMM)
	MPI_Bcast(&received, 1, MPI_INT, 0, MPI_COMM_WORLD);

	cout << "Se recibe en " << myid << " " << received << endl;*/

	// Fin de broadcast

	// Reduce 

	/*int sum;

	//MPI_Reduce (&SENDBUF(para el root, donde se hace la operacion), &RECVBUF(donde reciben los datos los demas), COUNT, DATATYPE, OP, ROOT, COMM)
	MPI_Reduce(&myid, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(myid == 0) {
		cout << "Root recibe " << sum << endl;
	}*/

	// Fin de reduce

	// Scatter, es diferente a scatterv en que scatter los parte uniformemente y con scatterv pueden haber huecos. Incluye gather.

	/*int* matrix = new int[numprocs*numprocs];
	for(int i=0; i<numprocs*numprocs; i++){
		matrix[i] = i;
	}

	int* array = new int[numprocs];

	//MPI_Scatter (SENDBUF(arreglo), SENDCOUNT(cuantos a cada proceso), SENDTYPE(tipo de datos en el arreglo),RECVBUF(arreglo que recibe)
	//, RECVCOUNT(cuantos datos se reciben), RECVTYPE(tipo de datos a recibir), ROOT, COMM)
	MPI_Scatter(matrix, 10, MPI_INT, array, 10, MPI_INT, 0, MPI_COMM_WORLD);

	string message = "Desde el proceso ";
	message += std::to_string(myid);
	message += " se recibe: ";
	for(int i=0; i<numprocs; i++){
		message += std::to_string(array[i]) + " ";
	}
	cout << message << endl;

	int* gatheredMatrix = new int[numprocs*numprocs];

	//MPI_Gather (SENDBUF(lo que manda cada proceso), SENDCOUNT(cuantos datos manda), SENDTYPE(tipo de datos que manda), 
	// RECVBUF(donde recibe),RECVCOUNT(cuanto recibe),RECVTYPE(tipo de datos que recibe), ROOT, COMM)
	MPI_Gather(array, 10, MPI_INT, gatheredMatrix, 10, MPI_INT, 0, MPI_COMM_WORLD);

	if(myid == 0){
		string message2 = "Desde el proceso ";
		message2 += std::to_string(myid);
		message2 += " se recibe: ";
		for(int i=0; i<numprocs*numprocs; i++){
			message2 += std::to_string(gatheredMatrix[i]) + " ";
		}
		cout << message2 << endl;
	}*/

	// Scatterv, el ejemplo va a ser como en la TP

	/*int* matrix = new int[numprocs*numprocs];
	for(int i=0; i<numprocs*numprocs; i++){
		matrix[i] = i;
	}

	int* sendcounts = new int[numprocs];
	int* displacement = new int[numprocs];
	for(int i=0; i<numprocs; i++){
		sendcounts[i] = numprocs*3;
		displacement[i] = (i*numprocs)-numprocs;
	}

	sendcounts[0] -= numprocs;
	sendcounts[numprocs-1] -= numprocs;
	displacement[0] = 0;

	int* array;
	if(myid == 0 || myid == numprocs-1) {
		array = new int[numprocs*2];
	} else {
		array = new int[numprocs*3];
	}

	//MPI_Scatterv(sendbuf(arreglo a dividir),sendcounts(numero de elementos por proceso),displs(desde que i comienza a mandar al otro proceso)
	//,sendtype(tipo de datos en el arreglo),recvbuf(arreglo donde recibo),recvcount(numero de elementos que recibo),recvtype(tipo de datos que recibo),root,comm)
	MPI_Scatterv(matrix, sendcounts, displacement, MPI_INT, array, numprocs*numprocs, MPI_INT, 0, MPI_COMM_WORLD);

	string message = "Desde el proceso ";
	message += std::to_string(myid);
	message += " se recibe: ";
	int limit;

	if(myid == 0 || myid == numprocs-1) {
		limit = numprocs*2;
	} else {
		limit = numprocs*3;
	}

	for(int i=0; i<limit; i++){
		message += std::to_string(array[i]) + " ";
	}
	cout << message << endl;*/


	MPI_Finalize(); //finalize the MPI environment
	return 0;
}