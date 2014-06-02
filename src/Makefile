CXX += -std=c++0x
CXXFLAGS += -O2
SRCS = computeSim.cpp svm.cpp selectGreedy.cpp
EXECS = computeSim selectGreedy
all: $(EXECS)
computeSim: svm.o

%: %.o
	${CXX} ${CXXFLAGS} $< -o $@

%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

clean:
	rm $(EXECS) *.o
