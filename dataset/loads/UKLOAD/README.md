The UK-DALE dataset, domestic appliance-level electricity demand and whole-house demand from five UK homes.

1 second data
There are four columns in each CSV file recording the whole-house power demand every second:
(1) UNIX timestamp. (GMT 2013/03/18 00:00 to 7days)
(2) Active power (watts).
(3) Apparent power (volt-amperes).
(4) Mains RMS voltage.



Example for reading MAT file in systemC
#include <mat.h>

MATFile *pmatFile = NULL;
mxArray *pMxArray = NULL;
 

double *initA;
 
pmatFile = matOpen("initUrban.mat","r");
pMxArray = matGetVariable(pmatFile, "initA");
initA = (double*) mxGetData(pMxArray);
M = mxGetM(pMxArray);
N = mxGetN(pMxArray);
Matrix<double> A(M,N);
for (int i=0; i<M; i++)
	for (int j=0; j<N; j++)
		A[i][j] = initA[M*j+i];
 
matClose(pmatFile);
mxFree(initA);
 

double *outA = new double[M*N];
	for (int i=0; i<M; i++)
		for (int j=0; j<N; j++)
			outA[M*j+i] = A[i][j];
pmatFile = matOpen("A.mat","w");
pMxArray = mxCreateDoubleMatrix(M, N, mxREAL);
mxSetData(pMxArray, outA);
matPutVariable(pmatFile, "A", pMxArray);
matClose(pmatFile);

