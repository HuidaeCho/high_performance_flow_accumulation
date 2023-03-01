#include "TopDownOpenMpMeffaHpAlgorithm.h"


unsigned int TopDownOpenMpMeffaHpAlgorithm::sumUp(const FlowAccumulationMatrix& accumulationMatrix, int pathRow, int pathCol, unsigned char up)
{
    int sum = 0;
    int accum;

#pragma omp flush
    if (up & DIRECTION_UP_LEFT)
    {
        if (!(accum = accumulationMatrix.value[pathRow - 1][pathCol - 1]))
            return 0;
        sum += accum;
    }
    if (up & DIRECTION_UP)
    {
        if (!(accum = accumulationMatrix.value[pathRow - 1][pathCol]))
            return 0;
        sum += accum;
    }
    if (up & DIRECTION_UP_RIGHT)
    {
        if (!(accum = accumulationMatrix.value[pathRow - 1][pathCol + 1]))
            return 0;
        sum += accum;
    }
    if (up & DIRECTION_LEFT)
    {
        if (!(accum = accumulationMatrix.value[pathRow][pathCol - 1]))
            return 0;
        sum += accum;
    }
    if (up & DIRECTION_RIGHT)
    {
        if (!(accum = accumulationMatrix.value[pathRow][pathCol + 1]))
            return 0;
        sum += accum;
    }
    if (up & DIRECTION_DOWN_LEFT)
    {
        if (!(accum = accumulationMatrix.value[pathRow + 1][pathCol - 1]))
            return 0;
        sum += accum;
    }
    if (up & DIRECTION_DOWN)
    {
        if (!(accum = accumulationMatrix.value[pathRow + 1][pathCol]))
            return 0;
        sum += accum;
    }
    if (up & DIRECTION_DOWN_RIGHT)
    {
        if (!(accum = accumulationMatrix.value[pathRow + 1][pathCol + 1]))
            return 0;
        sum += accum;
    }

    return sum;
}


FlowAccumulationMatrix TopDownOpenMpMeffaHpAlgorithm::execute(const FlowDirectionMatrix& directionMatrix)
{
  const int matrixHeight = directionMatrix.height;
  const int matrixWidth = directionMatrix.width;

  FlowAccumulationMatrix accumulationMatrix(matrixHeight, matrixWidth, 0);

  #pragma omp parallel
  {
    #pragma omp for schedule(dynamic)
    for (int row = 1; row <= matrixHeight; ++row)
    {
      for (int col = 1; col <= matrixWidth; ++col)
      {
        if ((directionMatrix.value[row][col] != DIRECTION_NONE) && !UP(row, col))
        {
          int pathRow = row;
          int pathCol = col;
          unsigned int pathLoad = 0;
          unsigned char up;

          do
          {
            // accumulate the current cell; different from the other algorithms
            accumulationMatrix.value[pathRow][pathCol] = pathLoad + 1;

            switch (directionMatrix.value[pathRow][pathCol])
            {
              case DIRECTION_RIGHT:                 ++pathCol; break;
              case DIRECTION_DOWN_RIGHT: ++pathRow; ++pathCol; break;
              case DIRECTION_DOWN:       ++pathRow;            break;
              case DIRECTION_DOWN_LEFT:  ++pathRow; --pathCol; break;
              case DIRECTION_LEFT:                  --pathCol; break;
              case DIRECTION_UP_LEFT:    --pathRow; --pathCol; break;
              case DIRECTION_UP:         --pathRow;            break;
              case DIRECTION_UP_RIGHT:   --pathRow; ++pathCol; break;
            }
          }
          while ((directionMatrix.value[pathRow][pathCol] != DIRECTION_NONE) && (up = UP(pathRow, pathCol)) && (pathLoad = sumUp(accumulationMatrix, pathRow, pathCol, up)));
        }
      }
    }
  }

  return accumulationMatrix;
}
