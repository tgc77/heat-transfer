/*******************************************************************************
  Name: EqHeatImplicitMethod.h
  Copyright:
  Author: Tiago Goncalves Cunha
  Date: 20/05/05 09:14
  Description:
*******************************************************************************/

#ifndef _EqHeatImplicitMethod_H
#define _EqHeatImplicitMethod_H

#include <string>

#define I_ 6  // n. de nos da malha
#define N_ 10 // n. de intervalos de tempo(deltaT), em segundos, para discretizar os I nos na barra
#define L_ 10
#define K 0.49
#define C 0.2174
#define Rho 2.7
#define DeltaT 0.1

typedef float REAL;

typedef struct NO **ptrNO;
struct NO
{
  REAL x;
  REAL t;
  REAL u;
};

typedef struct EqCondutionHeat *EqHeat;
struct EqCondutionHeat
{
  ptrNO node;
  REAL alfa, k, c, rho, lambda;
  REAL deltaX, deltaT, L;
  REAL Uo, UL;
  long I, N;
};

template<typename Type, typename TType>
void getInputNumber(Type &param, std::string label, TType default_val);

class EqHeatImplicitMethod {
public:
	EqHeatImplicitMethod();

	virtual ~EqHeatImplicitMethod() {
		desaloca_SEL();
  		free(mesh->node);
  		free(mesh);
	}
	//=========================================================================
	void initializeMeshParameters();
	//=========================================================================
	void alocar_SEL(const int LIN, const int COL);
	//=========================================================================
	void desaloca_SEL();
	//=========================================================================
	REAL calcularDeltaX();
	//=========================================================================
	void applyInitialConditionBoundary();
	//=========================================================================
	REAL calcularAlfa();
	//=========================================================================
	REAL calcularLambda();
	//=========================================================================
	void solve();
	//=========================================================================
	void imprimirMesh();
	//=========================================================================
	void salvarDadosEmArquivo();
	//=========================================================================
	void imprimirSEL(const int LIN, const int COL);
	//=========================================================================
	REAL *method_Gauss_Jordan(REAL **SEL, const int LIN, const int COL);
	//=========================================================================
	void ler_SEL(REAL **SEL);

	private:
		REAL **_SEL;
		REAL *U;
		EqHeat mesh;
		
		void alocateMeshMemory();
		void alocateSolverParametersMemory();
};
//=============================================================================
#endif
