# Compiler options
CXX = g++
CXX_FLAGS = -std=c++17 -g #-Wall -Werror -Wextra -Wshadow

# App name
INITIAL_APP_NAME = view
APP_NAME = SmartCalc

# Project directories
DIR_MODEL = model
DIR_CONTROLLER = controller
DIR_VIEW = view
DIR_ASSETS = assets
DIR_DOCS = docs
DIR_TESTS = tests

DIRECTORIES = $(DIR_MODEL) $(DIR_CONTROLLER) $(DIR_VIEW) $(DIR_ASSETS) $(DIR_DOCS) $(DIR_TESTS)

# Add searching flags for compiler
CXX_FLAGS += -I$(DIR_MODEL) -I$(DIR_CONTROLLER) -I$(DIR_VIEW)

# Project files
CXX_FILES_MODEL = $(wildcard $(DIR_MODEL)/*.cc $(DIR_MODEL)/*.cpp)
CXX_FILES_CONTROLLER = $(wildcard $(DIR_CONTROLLER)/*.cc $(DIR_CONTROLLER)/*.cpp)
CXX_FILES_VIEW = $(filter-out $(DIR_VIEW)/qcustomplot.cpp, $(wildcard $(DIR_VIEW)/*.cc $(DIR_VIEW)/*.cpp))

H_FILES_MODEL = $(wildcard $(DIR_MODEL)/*.h)
H_FILES_CONTROLLER = $(wildcard $(DIR_CONTROLLER)/*.h)
H_FILES_VIEW = $(filter-out $(DIR_VIEW)/qcustomplot.h, $(wildcard $(DIR_VIEW)/*.h))

CXX_FILES = $(CXX_FILES_MODEL) $(CXX_FILES_CONTROLLER)
H_FILES = $(H_FILES_MODEL)

OBJ_FILES = $(addprefix build/, $(addsuffix .o, $(basename $(notdir $(CXX_FILES)))))

CXX_FILES_ALL = $(CXX_FILES_MODEL) $(CXX_FILES_CONTROLLER) $(CXX_FILES_VIEW)
H_FILES_ALL = $(H_FILES_MODEL) $(H_FILES_CONTROLLER) $(H_FILES_VIEW)

MAIN = main.cpp

# Miscelaneous
SHELL = /bin/bash
OS = $(shell uname)

# Tests variables
TEST_FILES = $(wildcard $(DIR_TESTS)/*.cc)
TEST_EXEC = build/tests.out
TEST_FLAGS = -lgtest -lgtest_main

# GCOV report variables
GCOV_OBJ_FILES = $(addsuffix _gcov.o, $(basename $(OBJ_FILES)))
GCOV_EXEC = $(addsuffix _gcov.out, $(basename $(TEST_EXEC)))
GCOV_FLAGS = --coverage

all: clang-format leak-check install

#### Checks ####

leak-check: build_test
	@echo "Starting leak checking..."
ifeq ($(OS), Linux)
	@valgrind --leak-check=full --show-leak-kinds=all -s -- ./$(TEST_EXEC)
else
	@leaks --atExit -q -- ./$(TEST_EXEC)
endif
	@echo "Done leak-check target"

clang-format:
	@echo "Checking styles using clang-format utility..."
	@clang-format --verbose --Werror -n --style=google $(MAIN) $(CXX_FILES_ALL) $(H_FILES_ALL)
	@echo "Done clang-format target"

#### Tests compilation ####

create_build:
	@echo -n "Creating build folder..."
	@mkdir -p build
	@echo " Done create_build target"

build/%.o: model/%.cc
	@$(CXX) $(CXX_FLAGS) -c $< -o $@

build_objects: $(OBJ_FILES)
	@echo "Done build_objects target"

$(TEST_EXEC): create_build build_objects
	@echo -n "Compiling executable..."
	@$(CXX) $(CXX_FLAGS) $(TEST_FILES) $(OBJ_FILES) -o $(TEST_EXEC) $(TEST_FLAGS)
	@echo " Executable compiled succesfully"

build_test: $(TEST_EXEC)

tests: build_test
	@echo "Running tests..."
	@echo "----------------"
	@./$(TEST_EXEC)
	@echo "----------------"
	@echo "Tests ended"

#### App compilation ####

cmake-target:
	@echo "Creating Makefile..."
	@mkdir -p build
	@cmake -B build
	@echo "Done"

install: cmake-target
	@echo "Installing app..."
	@cd build; make
	@mkdir -p app
ifeq ($(OS), Darwin)
	@mv build/$(INITIAL_APP_NAME).app app/$(APP_NAME).app
else
	@mv build/$(INITIAL_APP_NAME) app/$(APP_NAME)
endif
	@echo "Done. App now situated in the 'app' folder and called '$(APP_NAME)'."

run: install
	@echo "Running application..."
ifeq ($(OS), Darwin)
	@open app/$(APP_NAME).app
else
	@app/$(APP_NAME)
endif

uninstall:
	@echo -n "Uninstalling app..."
	@rm -rf app
	@echo " Done"

#### GCOV report ####

build/%_gcov.o: model/%.cc
	@$(CXX) $(CXX_FLAGS) -c $< -o $@ $(GCOV_FLAGS)

$(GCOV_EXEC): create_build $(GCOV_OBJ_FILES)
	@$(CXX) $(CXX_FLAGS) $(TEST_FILES) $(GCOV_OBJ_FILES) -o $(GCOV_EXEC) $(TEST_FLAGS) $(GCOV_FLAGS)

gcov_report: $(GCOV_EXEC)
	@echo "Creating GCOV report..."
	@./$(GCOV_EXEC) > /dev/zero 2> /dev/zero
	@rm -rf build/tests_gcov.out-*
	@lcov --no-external -t "Coverage report" -o build/report.info -c -d . --exclude '$(DIR_TESTS)/*'
	@genhtml -o report build/report.info
	@echo "Done gcov_report target"

open_report: gcov_report
	@open report/index.html

#### Other targets ####

dvi:
	@echo -n "Opening documentation..."
	@open docs/html/index.html
	@echo " Done"

DIR_PROJECT = SmartCalc-2.0
ARCHIVE_NAME = $(DIR_PROJECT).tar

dist: clean
	@echo -n 'Creating archive "$(ARCHIVE_NAME)"...'
	@mkdir $(DIR_PROJECT)
	@cp -r $(DIRECTORIES) CMakeLists.txt $(MAIN) Makefile $(DIR_PROJECT)/
	@tar -zcf $(ARCHIVE_NAME) $(DIR_PROJECT)
	@rm -rf $(DIR_PROJECT)
	@echo " Done"

clean:
	@echo -n Cleaning...
	@rm -rf *.out */*.out *.a */*.a *.o */*.o *.gcda */*.gcda *.gcno */*.gcno *.dSYM */*.dSYM
	@rm -rf build* ../build*
	@rm -rf report report.info
	@rm -rf CMakeLists.txt.user view/CMakeLists.txt.user
	@rm -rf $(DIR_PROJECT) $(ARCHIVE_NAME)
	@echo " Done"