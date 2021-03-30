# Compilation variables
CXX = g++
CXX_FLAGS = -std=c++17 -Wall -pedantic -Wextra
LIBRARIES = -lncurses -lstdc++fs

# Other variables
TARGET = paukeluk
BUILD_DIR = build
DOC_DIR = doc
SOURCE_DIR = src

# Object files
OBJECT_FILES = $(BUILD_DIR)/CApplication.o $(BUILD_DIR)/CGame.o $(BUILD_DIR)/CInventory.o \
			   $(BUILD_DIR)/CItem.o $(BUILD_DIR)/CLocation.o $(BUILD_DIR)/CMonster.o $(BUILD_DIR)/COption.o \
			   $(BUILD_DIR)/CPlayer.o $(BUILD_DIR)/CWizard.o $(BUILD_DIR)/EAction.o $(BUILD_DIR)/EGameStatus.o \
			   $(BUILD_DIR)/interface.o $(BUILD_DIR)/main.o $(BUILD_DIR)/tools.o

# Header files
HEADER_FILES = $(wildcard $(SOURCE_DIR)/*.h)

.PHONY: all
all: compile doc

.PHONY: compile
compile: $(TARGET)
	@echo "Compilation completed"

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: valgrind
valgrind: $(TARGET)
	valgrind ./$(TARGET) 2> ./valgrind.txt

.PHONY: clean
clean:
	rm -rf $(TARGET) $(BUILD_DIR)/ $(DOC_DIR)/ examples/*.save valgrind.txt 2>/dev/null

doc: Doxyfile README.md $(HEADER_FILES)
	mkdir -p $(DOC_DIR)
	doxygen Doxyfile
	@echo "Documentation was generated"

# Executable file
$(TARGET): $(OBJECT_FILES)
	$(CXX) $^ $(LIBRARIES) -o $@

# Modules
$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

# Dependencies
$(BUILD_DIR)/CApplication.o: src/CApplication.cpp src/CApplication.h src/CGame.h \
 src/EGameStatus.h src/CLocation.h src/CCreature.h src/CEntity.h \
 src/COption.h src/EAction.h src/CItem.h src/CPlayer.h src/CInventory.h \
 src/interface.h
$(BUILD_DIR)/CGame.o: src/CGame.cpp src/CGame.h src/EGameStatus.h src/CLocation.h \
 src/CCreature.h src/CEntity.h src/COption.h src/EAction.h src/CItem.h \
 src/CPlayer.h src/CInventory.h src/interface.h
$(BUILD_DIR)/CInventory.o: src/CInventory.cpp src/CInventory.h src/CItem.h \
 src/interface.h
$(BUILD_DIR)/CItem.o: src/CItem.cpp src/CItem.h
$(BUILD_DIR)/CLocation.o: src/CLocation.cpp src/CLocation.h src/CCreature.h \
 src/CEntity.h src/COption.h src/EAction.h src/CItem.h src/interface.h \
 src/CMonster.h src/CWizard.h
$(BUILD_DIR)/CMonster.o: src/CMonster.cpp src/CMonster.h src/CCreature.h src/CEntity.h \
 src/interface.h src/tools.h
$(BUILD_DIR)/COption.o: src/COption.cpp src/COption.h src/EAction.h
$(BUILD_DIR)/CPlayer.o: src/CPlayer.cpp src/CPlayer.h src/CEntity.h src/CInventory.h \
 src/CItem.h src/tools.h src/interface.h
$(BUILD_DIR)/CWizard.o: src/CWizard.cpp src/CWizard.h src/CCreature.h src/CEntity.h \
 src/interface.h
$(BUILD_DIR)/EAction.o: src/EAction.cpp src/EAction.h
$(BUILD_DIR)/EGameStatus.o: src/EGameStatus.cpp src/EGameStatus.h
$(BUILD_DIR)/interface.o: src/interface.cpp src/interface.h
$(BUILD_DIR)/main.o: src/main.cpp src/CApplication.h
$(BUILD_DIR)/tools.o: src/tools.cpp src/interface.h src/tools.h
