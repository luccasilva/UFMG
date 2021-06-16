#include "Vec1D.hpp"

/**
 * \Fornece a norma do vetor, ou seja, a distância deste vetor para a origem.
 * \ retorna um double que representa a norma do vetor. 
 *   No caso de um vetor unidimensional, é simplesmente a coordenada x.
 */
double Vec1D::get_norm() const {
    if (_x<0){
        return -1*(_x);
    }
    return _x;
}

