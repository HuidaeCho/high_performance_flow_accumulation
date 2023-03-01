#include "FlowDirectionLoader.h"


const int FlowDirectionLoader::binaryDimensionSize = 4;
const int FlowDirectionLoader::binaryValueSize = 1;


FlowDirectionMatrix FlowDirectionLoader::loadGdal(std::string filename, RasterInfo& rasterInfo, int bandIndex)
{
  FlowDirectionMatrix x= GdalMatrixLoader::load<FlowDirectionMatrix, unsigned char>(filename, GDT_Byte, DIRECTION_NONE, rasterInfo, bandIndex);
  return x;
}


void FlowDirectionLoader::saveGdal(std::string filename, const FlowDirectionMatrix& directionMatrix, RasterInfo& rasterInfo, int bandIndex)
{
  GdalMatrixLoader::save<FlowDirectionMatrix>(filename, directionMatrix, GDT_Byte, rasterInfo, bandIndex);
}


FlowDirectionMatrix FlowDirectionLoader::loadBinary(std::string filename)
{
  std::fstream file(filename, std::ios::in | std::ios::binary);

  int height;
  int width;

  file.read((char*) &height, binaryDimensionSize);
  file.read((char*) &width, binaryDimensionSize);

  FlowDirectionMatrix directionMatrix(height, width);

  for (int i = 0; i < height; ++i)
  {
    file.read((char*) (directionMatrix.value[i + 1] + 1), width * binaryValueSize);
  }

  file.close();

  return directionMatrix;
}


void FlowDirectionLoader::saveBinary(std::string filename, const FlowDirectionMatrix& directionMatrix)
{
  const int height = directionMatrix.height;
  const int width = directionMatrix.width;

  std::fstream file(filename, std::ios::out | std::ios::binary);

  file.write((char*) &height, binaryDimensionSize);
  file.write((char*) &width, binaryDimensionSize);

  for (int i = 0; i < height; ++i)
  {
    file.write((char*) (directionMatrix.value[i + 1] + 1), width * binaryValueSize);
  }

  file.close();
}
