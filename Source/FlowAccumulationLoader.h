#ifndef FLOW_ACCUMULATION_LOADER_H
#define FLOW_ACCUMULATION_LOADER_H


#include "FlowAccumulationMatrix.h"
#include "GdalMatrixLoader.h"


class FlowAccumulationLoader
{
  public:
    static FlowAccumulationMatrix loadGdal(std::string filename, RasterInfo& rasterInfo, int bandIndex = 1);
    static void saveGdal(std::string filename, const FlowAccumulationMatrix& accumulationMatrix, RasterInfo& rasterInfo, int bandIndex = 1);
};


#endif
