SRC_DIR := ./src
OBJ_DIR := ./bin
BIN_DIR := ./bin
TEST_DIR := ./test
TEST_COVERAGE_DIR := ./test-cov
TEST_COVERAGE_REPORT_FILE := coverage_report.info
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES)) 
CFLAGS := -std=c++11 -fprofile-arcs -ftest-coverage -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -lgtest

$(BIN_DIR)/test: $(OBJ_FILES) test/test.cpp
	g++ $(CFLAGS) test/test.cpp -coverage -o $@ $(OBJ_FILES)
	mkdir -p $(TEST_COVERAGE_DIR)
	$(BIN_DIR)/test
	lcov -d . --no-external --capture --output-file $(TEST_COVERAGE_DIR)/$(TEST_COVERAGE_REPORT_FILE) -rc lcov_branch_coverage=1
	genhtml $(TEST_COVERAGE_DIR)/$(TEST_COVERAGE_REPORT_FILE) --legend --output-directory=$(TEST_COVERAGE_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CFLAGS) -c -o $@ $<

clean:
	rm -rf ${BIN}

.PHONY: test clean

obj_files: 

compile_obj:
	