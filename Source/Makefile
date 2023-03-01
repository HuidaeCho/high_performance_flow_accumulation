CXXFLAGS=-std=c++11 -O3 -fopenmp -Wall
LDFLAGS=-O3 -fopenmp

all: hpfa

clean:
	$(RM) *.o

hpfa: main.o BottomUpRecursiveOpenMpAlgorithm.o BottomUpRecursiveSequentialAlgorithm.o BottomUpRecursiveTasksAlgorithm.o FlowAccumulationLoader.o FlowAccumulationMatrix.o FlowDirectionLoader.o FlowDirectionMatrix.o FlowDirectionReverser.o IFlowAccumulationAlgorithm.o InletNumberCalculator.o InletNumberMatrix.o TopDownOpenMpAlgorithm.o TopDownSequentialAlgorithm.o TopDownTasksAlgorithm.o gettimeofday.o timeval_diff.o TopDownOpenMpMeffaHpAlgorithm.o
	$(CXX) $(LDFLAGS) -o $@ $^ `gdal-config --libs`

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<
