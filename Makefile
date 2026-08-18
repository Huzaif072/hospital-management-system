CXX      = g++
CXXFLAGS = -std=c++17 -I/usr/local/opt/sfml@2/include
LDFLAGS  = -L/usr/local/opt/sfml@2/lib \
           -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCS     = $(wildcard coding/*.cpp)
OBJS     = $(SRCS:.cpp=.o)
TARGET   = HospitalManagement

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

coding/%.o: coding/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f coding/*.o $(TARGET)

.PHONY: all clean
