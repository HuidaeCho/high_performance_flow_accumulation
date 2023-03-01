#ifndef TOP_DOWN_OPENMP_CHO_ALGORITHM_H
#define TOP_DOWN_OPENMP_CHO_ALGORITHM_H


#include "IFlowAccumulationAlgorithm.h"
#include <omp.h>

#define UP(row, col) ( \
    (directionMatrix.value[row    ][col - 1] & DIRECTION_RIGHT ? DIRECTION_LEFT : 0) | \
    (directionMatrix.value[row - 1][col - 1] & DIRECTION_DOWN_RIGHT ? DIRECTION_UP_LEFT : 0) | \
    (directionMatrix.value[row - 1][col] & DIRECTION_DOWN ? DIRECTION_UP : 0) | \
    (directionMatrix.value[row - 1][col + 1] & DIRECTION_DOWN_LEFT ? DIRECTION_UP_RIGHT : 0) | \
    (directionMatrix.value[row][col + 1] & DIRECTION_LEFT ? DIRECTION_RIGHT : 0) | \
    (directionMatrix.value[row + 1][col + 1] & DIRECTION_UP_LEFT ? DIRECTION_DOWN_RIGHT : 0) | \
    (directionMatrix.value[row + 1][col] & DIRECTION_UP ? DIRECTION_DOWN : 0) | \
    (directionMatrix.value[row + 1][col - 1] & DIRECTION_UP_RIGHT ? DIRECTION_DOWN_LEFT : 0))


class TopDownOpenMpMeffaHpAlgorithm: public IFlowAccumulationAlgorithm
{
  private:
    unsigned int sumUp(const FlowAccumulationMatrix& accumulationMatrix, int pathRow, int pathCol, unsigned char up);
  public:
    FlowAccumulationMatrix execute(const FlowDirectionMatrix& directionMatrix);
};


#endif
