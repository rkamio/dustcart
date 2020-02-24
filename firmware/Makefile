
CXX = g++
TARGET = dustcart
CXXFLAGS = -Wall -Wextra -O3
SRCS = cli/main.cpp src/parts/gpio_wrapper.cpp src/parts/caterpillar.cpp src/dustcart.cpp
OBJS := $(SRCS:.cpp=.o) #SRCSの各ファイルのサフィックスの.cppを.oに変換
LDLIBS := -lwiringPi

$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDLIBS)

clean:
	rm -f $(TARGET) $(OBJS)