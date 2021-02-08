#include <iostream>
#include <exception>

#ifndef _EqHeatImplicitMethod_H
#include "EqHeatImplicitMethod.h"
#endif

int main(void)
{
    EqHeatImplicitMethod eqHeatIMSolver = EqHeatImplicitMethod();
    
    try {
        eqHeatIMSolver.initializeMeshParameters();
        eqHeatIMSolver.applyInitialConditionBoundary();
        eqHeatIMSolver.solve();

        eqHeatIMSolver.salvarDadosEmArquivo();
        std::cout <<"\n\nFoi gerado um arquivo chamado: MeshPoints_ImplicitMethod.txt, com os dados calculados...\n\n";
    }
    catch(std::exception &e) {
        std::cout <<"Oopps! " << e.what() << std::endl;
    }

  return EXIT_SUCCESS;
}
