CXX = g++
CXXFLAGS = -Wall -std=c++17 -O3
TARGET = sorting

# Archivos fuente
SRCS = sorting.cpp \
       algorithms/mergesort.cpp \
       algorithms/quicksort.cpp \
       algorithms/patiencesort.cpp \
       algorithms/sort.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ejecuta el programa para generar los archivos de salida
run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)