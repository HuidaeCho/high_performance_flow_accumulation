#ifndef FLOW_DIRECTION_LOADER_H
#define FLOW_DIRECTION_LOADER_H


#include "FlowDirectionMatrix.h"
#include "GdalMatrixLoader.h"
#include <fstream>


class FlowDirectionLoader
{
  private:
    static const int binaryDimensionSize;
    static const int binaryValueSize;

  public:
    static FlowDirectionMatrix loadGdal(std::string filename, RasterInfo& rasterInfo, int bandIndex = 1);
    static void saveGdal(std::string filename, const FlowDirectionMatrix& directionMatrix, RasterInfo& rasterInfo, int bandIndex = 1);

    static FlowDirectionMatrix loadBinary(std::string filename);
    static void saveBinary(std::string filename, const FlowDirectionMatrix& directionMatrix);
};


#endif
