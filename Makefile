TARGET = kolombar
TEST_TARGET = spreadsheet-test

CXX = g++
MKDIR = mkdir -p

CXXFLAGS = -Wall -pedantic -Wextra -std=c++14 -g

VPATH = src:src/Parser

SOURCE_DIR = src
TESTS_DIR = tests
BUILD_DIR = build
BUILD_SUBDIR = build/Parser
TEST_BUILD_DIR = build

SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp $(SOURCE_DIR)/*/*.cpp)
HEADERS = $(wildcard $(SOURCE_DIR)/*.h $(SOURCE_DIR)/*/*.h)
TEST_SOURCES = $(wildcard $(TESTS_DIR)/*.cpp)
TEST_HEADERS = $(wildcard $(TESTS_DIR)/*.h)

OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
TEST_OBJECTS = $(TEST_SOURCES:tests/%.cpp=build/%.o)

.PHONY: all
all: clean compile doc

.PHONY: compile
compile: $(TARGET)


$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@


$(BUILD_DIR)/%.o: src/%.cpp
	$(MKDIR) $(BUILD_DIR) $(BUILD_SUBDIR)
	echo test
	$(CXX) $(CXXFLAGS) $< -c -o $@

.PHONY: compile-tests
compile-tests: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(filter-out build/main.o,$(OBJECTS))
	$(CXX) $^ -o $@

$(TEST_BUILD_DIR)/%.o: $(TESTS_DIR)/%.cpp $(filter-out build/main.o,$(OBJECTS))
	$(MKDIR) $(BUILD_DIR) $(BUILD_SUBDIR)
	$(CXX) $(CXXFLAGS) $< -c -o $@

.PHONY: doc
doc: $(HEADERS)
	doxygen Doxyfile


.PHONY: run
run: compile
	./$(TARGET)

.PHONY: run-tests
run-tests: compile-tests
	./$(TEST_TARGET)


.PHONY: clean
clean:
	rm -rf $(TARGET) $(TEST_TARGET) $(BUILD_DIR)/ $(TEST_BUILD_DIR)/ ./doc 2>/dev/null


#Dependencies
# Generated by "g++ -MM src/*.cpp tests/*.cpp | sed -r 's|^(.*\.o)|build/\1|'"
build/ActionStatus.o: src/ActionStatus.cpp src/ActionStatus.h
build/Application.o: src/Application.cpp src/Application.h src/Sheet.h \
 src/Table.h src/Cell.h src/Coords.h src/Parser/MathParser.h \
 src/Parser/Operator.h src/Parser/Variable.h src/Parser/Token.h \
 src/Parser/Parameters.h src/Parser/ParsedResult.h \
 src/Parser/../../tests/ParserTests.h src/View.h src/ActionStatus.h \
 src/File.h src/Command.h src/SetCommand.h src/DelCommand.h \
 src/ShowCommand.h src/HelpCommand.h src/SaveCommand.h src/FileCommand.h \
 src/LoadCommand.h src/PrintCommand.h src/ExitCommand.h src/EditCommand.h \
 src/InteractiveBuffer.h src/KeyboardDirection.h src/KeyboardControls.h
build/Cell.o: src/Cell.cpp src/Cell.h src/Coords.h
build/Command.o: src/Command.cpp src/Command.h src/View.h src/Sheet.h \
 src/Table.h src/Cell.h src/Coords.h src/Parser/MathParser.h \
 src/Parser/Operator.h src/Parser/Variable.h src/Parser/Token.h \
 src/Parser/Parameters.h src/Parser/ParsedResult.h \
 src/Parser/../../tests/ParserTests.h src/ActionStatus.h
build/Coords.o: src/Coords.cpp src/Coords.h src/View.h src/Sheet.h src/Table.h \
 src/Cell.h src/Parser/MathParser.h src/Parser/Operator.h \
 src/Parser/Variable.h src/Parser/Token.h src/Parser/Parameters.h \
 src/Parser/ParsedResult.h src/Parser/../../tests/ParserTests.h \
 src/ActionStatus.h
build/DelCommand.o: src/DelCommand.cpp src/DelCommand.h src/Command.h \
 src/View.h src/Sheet.h src/Table.h src/Cell.h src/Coords.h \
 src/Parser/MathParser.h src/Parser/Operator.h src/Parser/Variable.h \
 src/Parser/Token.h src/Parser/Parameters.h src/Parser/ParsedResult.h \
 src/Parser/../../tests/ParserTests.h src/ActionStatus.h
build/DelimitedFile.o: src/DelimitedFile.cpp src/DelimitedFile.h src/File.h \
 src/Sheet.h src/Table.h src/Cell.h src/Coords.h src/Parser/MathParser.h \
 src/Parser/Operator.h src/Parser/Variable.h src/Parser/Token.h \
 src/Parser/Parameters.h src/Parser/ParsedResult.h \
 src/Parser/../../tests/ParserTests.h src/View.h src/ActionStatus.h \
 src/Command.h
build/EditCommand.o: src/EditCommand.cpp src/EditCommand.h src/Command.h \
 src/View.h src/Sheet.h src/Table.h src/Cell.h src/Coords.h \
 src/Parser/MathParser.h src/Parser/Operator.h src/Parser/Variable.h \
 src/Parser/Token.h src/Parser/Parameters.h src/Parser/ParsedResult.h \
 src/Parser/../../tests/ParserTests.h src/ActionStatus.h \
 src/InteractiveBuffer.h src/KeyboardDirection.h src/KeyboardControls.h \
 src/SetCommand.h src/DelCommand.h src/SaveCommand.h src/FileCommand.h \
 src/File.h src/LoadCommand.h
build/ExitCommand.o: src/ExitCommand.cpp src/ExitCommand.h src/View.h \
 src/Sheet.h src/Table.h src/Cell.h src/Coords.h src/Parser/MathParser.h \
 src/Parser/Operator.h src/Parser/Variable.h src/Parser/Token.h \
 src/Parser/Parameters.h src/Parser/ParsedResult.h \
 src/Parser/../../tests/ParserTests.h src/ActionStatus.h src/Command.h
build/FileCommand.o: src/FileCommand.cpp src/FileCommand.h src/Command.h \
 src/View.h src/Sheet.h src/Table.h src/Cell.h src/Coords.h \
 src/Parser/MathParser.h src/Parser/Operator.h src/Parser/Variable.h \
 src/Parser/Token.h src/Parser/Parameters.h src/Parser/ParsedResult.h \
 src/Parser/../../tests/ParserTests.h src/ActionStatus.h src/File.h \
 src/DelimitedFile.h
build/HelpCommand.o: src/HelpCommand.cpp src/HelpCommand.h src/Sheet.h \
 src/Table.h src/Cell.h src/Coords.h src/Parser/MathParser.h \
 src/Parser/Operator.h src/Parser/Variable.h src/Parser/Token.h \
 src/Parser/Parameters.h src/Parser/ParsedResult.h \
 src/Parser/../../tests/ParserTests.h src/View.h src/ActionStatus.h \
 src/Command.h
build/InteractiveBuffer.o: src/InteractiveBuffer.cpp src/InteractiveBuffer.h \
 src/KeyboardDirection.h src/KeyboardControls.h
build/LoadCommand.o: src/LoadCommand.cpp src/LoadCommand.h src/Sheet.h \
 src/Table.h src/Cell.h src/Coords.h src/Parser/MathParser.h \
 src/Parser/Operator.h src/Parser/Variable.h src/Parser/Token.h \
 src/Parser/Parameters.h src/Parser/ParsedResult.h \
 src/Parser/../../tests/ParserTests.h src/View.h src/ActionStatus.h \
 src/FileCommand.h src/Command.h src/File.h
build/main.o: src/main.cpp src/Application.h src/Sheet.h src/Table.h src/Cell.h \
 src/Coords.h src/Parser/MathParser.h src/Parser/Operator.h \
 src/Parser/Variable.h src/Parser/Token.h src/Parser/Parameters.h \
 src/Parser/ParsedResult.h src/Parser/../../tests/ParserTests.h \
 src/View.h src/ActionStatus.h src/File.h src/Command.h
build/NumberCell.o: src/NumberCell.cpp src/NumberCell.h src/Cell.h src/Coords.h
build/PrintCommand.o: src/PrintCommand.cpp src/PrintCommand.h src/Command.h \
 src/View.h src/Sheet.h src/Table.h src/Cell.h src/Coords.h \
 src/Parser/MathParser.h src/Parser/Operator.h src/Parser/Variable.h \
 src/Parser/Token.h src/Parser/Parameters.h src/Parser/ParsedResult.h \
 src/Parser/../../tests/ParserTests.h src/ActionStatus.h
build/SaveCommand.o: src/SaveCommand.cpp src/SaveCommand.h src/Sheet.h \
 src/Table.h src/Cell.h src/Coords.h src/Parser/MathParser.h \
 src/Parser/Operator.h src/Parser/Variable.h src/Parser/Token.h \
 src/Parser/Parameters.h src/Parser/ParsedResult.h \
 src/Parser/../../tests/ParserTests.h src/View.h src/ActionStatus.h \
 src/FileCommand.h src/Command.h src/File.h src/DelimitedFile.h
build/SetCommand.o: src/SetCommand.cpp src/SetCommand.h src/Sheet.h src/Table.h \
 src/Cell.h src/Coords.h src/Parser/MathParser.h src/Parser/Operator.h \
 src/Parser/Variable.h src/Parser/Token.h src/Parser/Parameters.h \
 src/Parser/ParsedResult.h src/Parser/../../tests/ParserTests.h \
 src/Command.h src/View.h src/ActionStatus.h
build/Sheet.o: src/Sheet.cpp src/Sheet.h src/Table.h src/Cell.h src/Coords.h \
 src/Parser/MathParser.h src/Parser/Operator.h src/Parser/Variable.h \
 src/Parser/Token.h src/Parser/Parameters.h src/Parser/ParsedResult.h \
 src/Parser/../../tests/ParserTests.h src/NumberCell.h src/StringCell.h
build/ShowCommand.o: src/ShowCommand.cpp src/ShowCommand.h src/Command.h \
 src/View.h src/Sheet.h src/Table.h src/Cell.h src/Coords.h \
 src/Parser/MathParser.h src/Parser/Operator.h src/Parser/Variable.h \
 src/Parser/Token.h src/Parser/Parameters.h src/Parser/ParsedResult.h \
 src/Parser/../../tests/ParserTests.h src/ActionStatus.h
build/StringCell.o: src/StringCell.cpp src/StringCell.h src/Cell.h src/Coords.h
build/Table.o: src/Table.cpp src/Table.h src/Cell.h src/Coords.h \
 src/NumberCell.h
build/View.o: src/View.cpp src/View.h src/Sheet.h src/Table.h src/Cell.h \
 src/Coords.h src/Parser/MathParser.h src/Parser/Operator.h \
 src/Parser/Variable.h src/Parser/Token.h src/Parser/Parameters.h \
 src/Parser/ParsedResult.h src/Parser/../../tests/ParserTests.h \
 src/ActionStatus.h
build/main-tests.o: tests/main-tests.cpp tests/ParserTests.h tests/SheetTests.h \
 tests/TableTests.h
build/ParserTests.o: tests/ParserTests.cpp tests/ParserTests.h \
 tests/../src/Parser/CosFunction.h tests/../src/Parser/Variable.h \
 tests/../src/Parser/Token.h tests/../src/Parser/DivideOperator.h \
 tests/../src/Parser/Operator.h tests/../src/Table.h tests/../src/Cell.h \
 tests/../src/Coords.h tests/../src/Command.h tests/../src/View.h \
 tests/../src/Sheet.h tests/../src/Parser/MathParser.h \
 tests/../src/Parser/Parameters.h tests/../src/Parser/ParsedResult.h \
 tests/../src/ActionStatus.h tests/Assertion.h tests/../src/NumberCell.h
build/SheetTests.o: tests/SheetTests.cpp tests/SheetTests.h \
 tests/../src/Sheet.h tests/../src/Table.h tests/../src/Cell.h \
 tests/../src/Coords.h tests/../src/Parser/MathParser.h \
 tests/../src/Parser/Operator.h tests/../src/Parser/Variable.h \
 tests/../src/Parser/Token.h tests/../src/Parser/Parameters.h \
 tests/../src/Parser/ParsedResult.h \
 tests/../src/Parser/../../tests/ParserTests.h tests/Assertion.h
build/TableTests.o: tests/TableTests.cpp tests/TableTests.h \
 tests/../src/Table.h tests/../src/Cell.h tests/../src/Coords.h \
 tests/Assertion.h tests/../src/NumberCell.h tests/../src/StringCell.h