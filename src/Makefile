##########################################
# Common C project variables and targets #
##########################################

SHELL = bash

CC = gcc -std=c11 -g
CFLAGS = -Wall -Werror -Wextra
LIBFLAGS = -lm
LIBSTATIC = s21_postfix.a

CC += $(CFLAGS)

MAIN = main.c
TMAIN = s21_tests.c
CFILES = $(filter-out tests.c,$(wildcard *.c))
OBJS = $(CFILES:.c=.o)

TFLAGS = -lcheck

OS = $(shell uname)
ifeq ($(OS), Linux)
TFLAGS += -lm -lrt -lpthread -lsubunit
endif

EXEC = $(MAIN:.c=)
TEXEC = $(TMAIN:.c=)

all: tests gcov_report dvi install

build: $(LIBSTATIC) clean_build
	@$(CC) $(MAIN) $(LIBSTATIC) -o $(EXEC) $(LIBFLAGS)

rebuild: clean build

build_tests: $(LIBSTATIC)
	@$(CC) $(TMAIN) $(LIBSTATIC) -o $(TEXEC) $(TFLAGS)

style:
	@cp ../materials/linters/CPPLINT.cfg .
	@python3 ../materials/linters/cpplint.py --extensions=c *.c

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c

leaks: build_tests
ifeq ($(OS), Darwin)
	@leaks --atExit -- ./$(TEXEC)
else
	@valgrind --leak-check=full -s ./$(TEXEC)
endif

tests: build_tests
	@./$(TEXEC)

test: tests

$(OBJS):
	@$(CC) -c $(CFILES) $(LIBFLAGS)

$(LIBSTATIC): $(OBJS)
	@ar -rcs $(LIBSTATIC) $(OBJS)

################################
# GCOV Report vars and targets #
################################

GFLAGS = --coverage
REPORT_FOLDER = gcov_report

GCOV_OBJS:
	@$(CC) -c $(CFILES) $(LIBFLAGS) $(GFLAGS)

GCOV_STATIC_LIB: GCOV_OBJS
	@ar -rcs $(LIBSTATIC:.a=_gcov.a) $(OBJS)

gcov_report: clean GCOV_STATIC_LIB
	@$(CC) $(TMAIN) $(LIBSTATIC:.a=_gcov.a) -o $(TEXEC) $(TFLAGS) $(GFLAGS)
	@./$(TEXEC) > /dev/zero 2> /dev/zero
	-@lcov -t "Coverage report" -o $(REPORT_FOLDER).info -c -d .
	-@genhtml -o $(REPORT_FOLDER) $(REPORT_FOLDER).info

###################
# Building QT app #
###################

QT_PROJECT_NAME = SmartCalc
QT_PROJECT_FOLDER = ./$(QT_PROJECT_NAME)
QT_PRO = $(QT_PROJECT_NAME).pro
QT_MAKEFILE = $(QT_PROJECT_NAME)_Makefile
QT_BUILD_FOLDER = Build
QT_APP_FOLDER = App

generate_make:
	@qmake6 $(QT_PROJECT_FOLDER)/$(QT_PRO) -o ./$(QT_BUILD_FOLDER)/$(QT_MAKEFILE) 2> /dev/zero > /dev/zero
	@rm -rf .qmake.stash

install: generate_make
	@echo "Building application..."
	@cd ./$(QT_BUILD_FOLDER) && make -sf $(QT_MAKEFILE)
	@echo "Application builded."
	@echo -n "Moving application to folder \"$(QT_APP_FOLDER)\"..."
	@mkdir ./$(QT_APP_FOLDER)
ifeq ($(OS), Darwin)
	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME).app/Contents/MacOS/SmartCalc ./$(QT_APP_FOLDER)/$(QT_PROJECT_NAME).app
else
	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME) ./$(QT_APP_FOLDER)/$(QT_PROJECT_NAME)
endif
	@echo " Done."
	@echo -n "Deleting build folder..."
	@rm -rf $(QT_BUILD_FOLDER)
	@echo " Done."
	@echo "Installation complete!"

uninstall:
	@echo -n "Uninstalling application..."
	@rm -rf $(QT_APP_FOLDER)
	@echo " Done."

DIST_FOLDER_NAME = SmartCalc-1.0

dist:
	@echo -n "Creating \"$(DIST_FOLDER_NAME).tar.gz\"..."
	@rm -rf $(DIST_FOLDER_NAME)
	@mkdir ./$(DIST_FOLDER_NAME)
	@cp *.c ./$(DIST_FOLDER_NAME)/
	@cp *.h ./$(DIST_FOLDER_NAME)/
	@cp Makefile ./$(DIST_FOLDER_NAME)/
	@cp -r $(DVI_FOLDER) ./$(DIST_FOLDER_NAME)/
	@cp -r SmartCalc ./$(DIST_FOLDER_NAME)/
	@tar -cf $(DIST_FOLDER_NAME).tar.gz ./$(DIST_FOLDER_NAME)
	@rm -rf $(DIST_FOLDER_NAME)
	@echo " Done."

DVI_NAME = documentation
DVI_FOLDER = Docs

dvi:
	@echo -n "Opening documentation..."
ifeq ($(OS), Darwin)
	@open ./$(DVI_FOLDER)/$(DVI_NAME).html &
else
	@xdg-open ./$(DVI_FOLDER)/$(DVI_NAME).html &
endif
	@echo " Done."

#################
# Other targets #
#################

clean:
	@echo -n "Cleanup started..."
	@rm -rf *.o *.a *.out
	@rm -rf *.gcov *.gcda *.gcno *.info
	@rm -rf *.gch
	@rm -rf $(EXEC) $(CEXEC) $(TEXEC)
	@rm -rf *.dSYM
	@rm -rf $(QT_BUILD_FOLDER)
	@rm -rf .qmake.stash
	@rm -rf $(REPORT_FOLDER)
	@rm -rf $(DIST_FOLDER_NAME) $(DIST_FOLDER_NAME).tar.gz
	@echo " Done."
