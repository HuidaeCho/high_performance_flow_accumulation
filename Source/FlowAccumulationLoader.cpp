#include "FlowAccumulationLoader.h"


FlowAccumulationMatrix FlowAccumulationLoader::loadGdal(std::string filename, RasterInfo& rasterInfo, int bandIndex)
{
  return GdalMatrixLoader::load<FlowAccumulationMatrix, unsigned int>(filename, GDT_UInt32, -1, rasterInfo, bandIndex);
}


void FlowAccumulationLoader::saveGdal(std::string filename, const FlowAccumulationMatrix& accumulationMatrix, RasterInfo& rasterInfo, int bandIndex)
{
  GdalMatrixLoader::save<FlowAccumulationMatrix>(filename, accumulationMatrix, GDT_UInt32, rasterInfo, bandIndex);
}
