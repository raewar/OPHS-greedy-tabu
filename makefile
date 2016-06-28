  # the compiler: gcc for C program, define as g++ for C++
  CC = g++

  # compiler flags:
  CFLAGS  = -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE

  # the build target executable:
  TARGET = tabu

  # hace carpeta
  MKDIR_P = mkdir -p

  all: $(TARGET)

  $(TARGET): $(TARGET).cpp
  	$(CC) $(CFLAGS) $(TARGET).cpp -o $(TARGET).out

  clean:
  	$(RM) $(TARGET)