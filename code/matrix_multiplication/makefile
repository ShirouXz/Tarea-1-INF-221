CXX = g++
CXXFLAGS = -Wall -std=c++17 -O3
TARGET = matrix_multiplication

# Archivos fuente
SRCS = matrix_multiplication.cpp \
       algorithms/naive.cpp \
       algorithms/strassen.cpp

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