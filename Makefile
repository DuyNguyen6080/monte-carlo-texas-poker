# Compiler
compiler = g++

# Compiler flags
flags = -std=c++11 -Wall

# Source files
main = Game_World.cpp

# Executable name
TARGET = game

#dependency
card = Card/Card.cpp
player = Player/Player.cpp
table = Table/Table.cpp
# Build rule
$(TARGET): $(SRCS)
	$(compiler) $(flags)  $(card)  $(player)  $(table) $(main) -o $(TARGET)
	./$(TARGET)

# Clean rule
clean:
	rm -f $(TARGET)