CXX += -std=c++0x -g
CXXFLAGS += -O2
SRCS = computeSim.cpp svm.cpp selectGreedy.cpp modifyModel.cpp
EXECS = computeSim selectGreedy modifyModel
all: $(EXECS)
computeSim modifyModel: svm.o
selectGreedy: NVMUtils.hpp

%: %.o
	${CXX} ${CXXFLAGS} $< -o $@

%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

clean:
	rm $(EXECS) *.o
