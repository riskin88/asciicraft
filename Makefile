CXXFLAGS = -Wall -pedantic -std=c++14
USERNAME = hlavaj39

HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
TESTS = $(wildcard tests/*.test.cpp)

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	./$(USERNAME)

.PHONY: compile
compile: build/main
	cp $< $(USERNAME)

build/main: $(OBJECTS)
	mkdir -p $(@D)
	g++ $^ -o $@

build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< -c -o $@


doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

.PHONY: clean
clean:
	rm -rf $(USERNAME) build/ doc/ 2>/dev/null


build/CAgent.o: src/CAgent.cpp src/CAgent.h src/CCoord.h src/EDirection.h \
 src/EState.h src/CExtendedChar.h
build/CApplication.o: src/CApplication.cpp src/CApplication.h src/CInterface.h \
 src/CGame.h src/CInventory.h src/CItem.h src/EID.h src/CAgent.h \
 src/CCoord.h src/EDirection.h src/EState.h src/CGrid.h src/CBlock.h \
 src/CExtendedChar.h src/EColor.h src/CStaticBlock.h src/CLava.h \
 src/CDynamicBlock.h src/CTree.h src/CSeed.h src/CPlayer.h \
 src/CMapBuilder.h src/CCommand.h
build/CBlock.o: src/CBlock.cpp src/CBlock.h src/CItem.h src/EID.h \
 src/CExtendedChar.h src/EColor.h
build/CCommand.o: src/CCommand.cpp src/CCommand.h src/CInterface.h src/CGame.h \
 src/CInventory.h src/CItem.h src/EID.h src/CAgent.h src/CCoord.h \
 src/EDirection.h src/EState.h src/CGrid.h src/CBlock.h \
 src/CExtendedChar.h src/EColor.h src/CStaticBlock.h src/CLava.h \
 src/CDynamicBlock.h src/CTree.h src/CSeed.h src/CPlayer.h
build/CCoord.o: src/CCoord.cpp src/CCoord.h src/EDirection.h
build/CDynamicBlock.o: src/CDynamicBlock.cpp src/CDynamicBlock.h
build/CEnemy.o: src/CEnemy.cpp src/CEnemy.h src/CAgent.h src/CCoord.h \
 src/EDirection.h src/EState.h
build/CExtendedChar.o: src/CExtendedChar.cpp src/CExtendedChar.h src/EColor.h
build/CGame.o: src/CGame.cpp src/CGame.h src/CInventory.h src/CItem.h src/EID.h \
 src/CAgent.h src/CCoord.h src/EDirection.h src/EState.h src/CGrid.h \
 src/CBlock.h src/CExtendedChar.h src/EColor.h src/CStaticBlock.h \
 src/CLava.h src/CDynamicBlock.h src/CTree.h src/CSeed.h src/CPlayer.h \
 src/CInterface.h
build/CGrid.o: src/CGrid.cpp src/CGrid.h src/CCoord.h src/EDirection.h \
 src/CInventory.h src/CItem.h src/EID.h src/CBlock.h src/CExtendedChar.h \
 src/EColor.h src/CStaticBlock.h src/CLava.h src/CDynamicBlock.h \
 src/CTree.h src/CSeed.h
build/CInterface.o: src/CInterface.cpp src/CInterface.h src/CGame.h \
 src/CInventory.h src/CItem.h src/EID.h src/CAgent.h src/CCoord.h \
 src/EDirection.h src/EState.h src/CGrid.h src/CBlock.h \
 src/CExtendedChar.h src/EColor.h src/CStaticBlock.h src/CLava.h \
 src/CDynamicBlock.h src/CTree.h src/CSeed.h src/CPlayer.h
build/CInventory.o: src/CInventory.cpp src/CInventory.h src/CItem.h src/EID.h
build/CLava.o: src/CLava.cpp src/CLava.h src/CDynamicBlock.h src/CBlock.h \
 src/CItem.h src/EID.h src/CExtendedChar.h src/EColor.h src/CCoord.h \
 src/EDirection.h src/CGrid.h src/CInventory.h src/CStaticBlock.h \
 src/CTree.h src/CSeed.h
build/CMapBuilder.o: src/CMapBuilder.cpp src/CMapBuilder.h src/CGrid.h \
 src/CCoord.h src/EDirection.h src/CInventory.h src/CItem.h src/EID.h \
 src/CBlock.h src/CExtendedChar.h src/EColor.h src/CStaticBlock.h \
 src/CLava.h src/CDynamicBlock.h src/CTree.h src/CSeed.h
build/CPlayer.o: src/CPlayer.cpp src/CPlayer.h src/CAgent.h src/CCoord.h \
 src/EDirection.h src/EState.h src/CInventory.h src/CItem.h src/EID.h \
 src/CInterface.h src/CGame.h src/CGrid.h src/CBlock.h \
 src/CExtendedChar.h src/EColor.h src/CStaticBlock.h src/CLava.h \
 src/CDynamicBlock.h src/CTree.h src/CSeed.h
build/CSeed.o: src/CSeed.cpp src/CSeed.h src/CDynamicBlock.h src/CBlock.h \
 src/CItem.h src/EID.h src/CExtendedChar.h src/EColor.h src/CCoord.h \
 src/EDirection.h src/CGrid.h src/CInventory.h src/CStaticBlock.h \
 src/CLava.h src/CTree.h
build/CStaticBlock.o: src/CStaticBlock.cpp
build/CTree.o: src/CTree.cpp src/CTree.h src/CDynamicBlock.h src/CBlock.h \
 src/CItem.h src/EID.h src/CExtendedChar.h src/EColor.h src/CCoord.h \
 src/EDirection.h src/CGrid.h src/CInventory.h src/CStaticBlock.h \
 src/CLava.h src/CSeed.h
build/EDirection.o: src/EDirection.cpp src/EDirection.h
build/main.o: src/main.cpp src/CApplication.h src/CInterface.h src/CGame.h \
 src/CInventory.h src/CItem.h src/EID.h src/CAgent.h src/CCoord.h \
 src/EDirection.h src/EState.h src/CGrid.h src/CBlock.h \
 src/CExtendedChar.h src/EColor.h src/CStaticBlock.h src/CLava.h \
 src/CDynamicBlock.h src/CTree.h src/CSeed.h src/CPlayer.h \
 src/CMapBuilder.h src/CCommand.h src/SCommands.h
build/SCommands.o: src/SCommands.cpp src/SCommands.h src/CCommand.h \
 src/CInterface.h src/CGame.h src/CInventory.h src/CItem.h src/EID.h \
 src/CAgent.h src/CCoord.h src/EDirection.h src/EState.h src/CGrid.h \
 src/CBlock.h src/CExtendedChar.h src/EColor.h src/CStaticBlock.h \
 src/CLava.h src/CDynamicBlock.h src/CTree.h src/CSeed.h src/CPlayer.h \
 src/CApplication.h src/CMapBuilder.h src/CEnemy.h
