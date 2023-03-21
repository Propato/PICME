#include <stdio.h>
#include <stdlib.h>

#include "include/dados.h"
#include "include/LU.h"
#include "include/cholesky.h"
#include "include/gauss_jacobi.h"
#include "include/gauss_seidel.h"

int main(int argc, char** argv){
    
    main_C(argv);
    main_LU(argv);
    main_GJ(argv);
    main_GS(argv);

    return 0;
}