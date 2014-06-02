CXXFLAGS += -O2
SRCS = computeSim.cpp svm.cpp
EXECS = computeSim
all: $(EXECS)
computeSim: svm.o

%: %.o
	${CXX} ${CXXFLAGS} $< -o $@

%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

clean:
	rm $(EXECS) *.o
