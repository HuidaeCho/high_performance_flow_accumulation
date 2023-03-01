#include "FlowDirectionLoader.h"
#include "FlowAccumulationLoader.h"
#include "TopDownOpenMpAlgorithm.h"
#include "TopDownTasksAlgorithm.h"
#include "TopDownSequentialAlgorithm.h"
#include "BottomUpRecursiveOpenMpAlgorithm.h"
#include "BottomUpRecursiveTasksAlgorithm.h"
#include "BottomUpRecursiveSequentialAlgorithm.h"
#include "TopDownOpenMpMeffaHpAlgorithm.h"
#include <iostream>
#include "timeutils.h"


std::string algorithmLabel(int algorithmIndex)
{
  switch (algorithmIndex)
  {
    case 1: return "top-down openmp";
    case 2: return "top-down tasks";
    case 3: return "top-down sequential";
    case 4: return "bottom-up recursive openmp";
    case 5: return "bottom-up recursive tasks";
    case 6: return "bottom-up recursive sequential";
    case 7: return "top-down openmp MEFFA-HP";
    default: return "";
  }
}


IFlowAccumulationAlgorithm* createAlgorithm(int algorithmIndex, int algorithmParameter)
{
  switch (algorithmIndex)
  {
    case 1: return new TopDownOpenMpAlgorithm();
    case 2: return new TopDownTasksAlgorithm();
    case 3: return new TopDownSequentialAlgorithm();
    case 4: return new BottomUpRecursiveOpenMpAlgorithm();
    case 5: return new BottomUpRecursiveTasksAlgorithm(algorithmParameter);
    case 6: return new BottomUpRecursiveSequentialAlgorithm();
    case 7: return new TopDownOpenMpMeffaHpAlgorithm();
    default: return nullptr;
  }
}


void printUsage()
{
  std::cout << "required arguments:" << std::endl
            << " 1.  flow direction filename" << std::endl
            << " 2.  flow accumulation filename" << std::endl
            << " 3.  algorithm index" << std::endl
            << "(4.) algorithm parameter (only for task-based recursive implementation: task creation limit)" << std::endl
            << std::endl
            << "available algorithms:" << std::endl;

  for (int i = 1; i <= 7; ++i)
  {
    std::cout << ' ' << i << ".  " << algorithmLabel(i) << std::endl;
  }
}


void executeMeasurement(std::string directionFilename, std::string accumulationFilename, int algorithmIndex, int algorithmParameter)
{
  RasterInfo rasterInfo;

  std::cout << "loading flow direction file (" << directionFilename << ")..." << std::endl;
  FlowDirectionMatrix directionMatrix = FlowDirectionLoader::loadGdal(directionFilename, rasterInfo);
  std::cout << "flow direction data: " << directionMatrix.height << " rows, " << directionMatrix.width << " columns" << std::endl;

  std::cout << "executing " << algorithmLabel(algorithmIndex) << " algorithm..." << std::endl;
  IFlowAccumulationAlgorithm* algorithm = createAlgorithm(algorithmIndex, algorithmParameter);

  struct timeval stamp_begin, stamp_end;
  gettimeofday(&stamp_begin, NULL);
  FlowAccumulationMatrix accumulationMatrix = algorithm->execute(directionMatrix);
  gettimeofday(&stamp_end, NULL);
  long long stamp_diff = timeval_diff(NULL, &stamp_end, &stamp_begin);

  std::cout << "flow accumulation data: " << accumulationMatrix.height << " rows, " << accumulationMatrix.width << " columns" << std::endl;
  std::cout << "execution time (microsec): " << stamp_diff << std::endl;

  std::cout << "saving flow accumulation file (" << accumulationFilename << ")..." << std::endl;
  rasterInfo.hasNoDataValue = 0;
  FlowAccumulationLoader::saveGdal(accumulationFilename, accumulationMatrix, rasterInfo);
}


int main(int argc, char** argv)
{
  if (argc < 4)
  {
    printUsage();
  }

  else
  {
    const std::string directionFilename = argv[1];
    const std::string accumulationFilename = argv[2];
    const int algorithmIndex = atoi(argv[3]);
    const int algorithmParameter = (argc > 4) ? atoi(argv[4]) : 0;

    executeMeasurement(directionFilename, accumulationFilename, algorithmIndex, algorithmParameter);
  }
}
