#include "FlowDirectionLoader.h"
#include "BottomUpRecursiveOpenMpAlgorithm.h"
#include "BottomUpRecursiveSequentialAlgorithm.h"
#include "BottomUpRecursiveTasksAlgorithm.h"
#include "TopDownOpenMpAlgorithm.h"
#include "TopDownSequentialAlgorithm.h"
#include "TopDownTasksAlgorithm.h"
#include <chrono>
#include <iostream>


std::string algorithmLabel(int algorithmIndex)
{
  switch (algorithmIndex)
  {
    case 1: return "bottom-up recursive openmp";
    case 2: return "bottom-up recursive sequential";
    case 3: return "bottom-up recursive tasks";
    case 4: return "top-down openmp";
    case 5: return "top-down sequential";
    case 6: return "top-down tasks";
    default: return "";
  }
}


IFlowAccumulationAlgorithm* createAlgorithm(int algorithmIndex, int algorithmParameter)
{
  switch (algorithmIndex)
  {
    case 1: return new BottomUpRecursiveOpenMpAlgorithm();
    case 2: return new BottomUpRecursiveSequentialAlgorithm();
    case 3: return new BottomUpRecursiveTasksAlgorithm(algorithmParameter);
    case 4: return new TopDownOpenMpAlgorithm();
    case 5: return new TopDownSequentialAlgorithm();
    case 6: return new TopDownTasksAlgorithm();
    default: return nullptr;
  }
}


void printUsage()
{
  std::cout << "required arguments:" << std::endl
            << " 1.  flow direction filename" << std::endl
            << " 2.  algorithm index" << std::endl
            << "(3.) algorithm parameter (only for task-based recursive implementation: task creation limit)" << std::endl
            << std::endl
            << "available algorithms:" << std::endl;

  for (int i = 1; i <= 6; ++i)
  {
    std::cout << ' ' << i << ".  " << algorithmLabel(i) << std::endl;
  }
}


void executeMeasurement(std::string directionFilename, int algorithmIndex, int algorithmParameter)
{
  std::cout << "loading flow direction file (" << directionFilename << ")..." << std::endl;
  FlowDirectionMatrix directionMatrix = FlowDirectionLoader::loadGdal(directionFilename);
  std::cout << "flow direction data: " << directionMatrix.height << " rows, " << directionMatrix.width << " columns" << std::endl;

  std::cout << "executing " << algorithmLabel(algorithmIndex) << " algorithm..." << std::endl;
  IFlowAccumulationAlgorithm* algorithm = createAlgorithm(algorithmIndex, algorithmParameter);

  auto stamp_begin = std::chrono::high_resolution_clock::now();
  FlowAccumulationMatrix accumulationMatrix = algorithm->execute(directionMatrix);
  auto stamp_end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> stamp_diff = stamp_end - stamp_begin;

  std::cout << "flow accumulation data: " << accumulationMatrix.height << " rows, " << accumulationMatrix.width << " columns" << std::endl;
  std::cout << "execution time (ms): " << lround(stamp_diff.count()) << std::endl;
}


int main(int argc, char** argv)
{
  if (argc < 3)
  {
    printUsage();
  }

  else
  {
    const std::string directionFilename = argv[1];
    const int algorithmIndex = atoi(argv[2]);
    const int algorithmParameter = (argc > 3) ? atoi(argv[3]) : 0;

    executeMeasurement(directionFilename, algorithmIndex, algorithmParameter);
  }
}
