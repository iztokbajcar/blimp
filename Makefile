# prod params
SRC_DIR := ./src
OBJ_DIR := ./bin
BIN_DIR := ./bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES)) 
CFLAGS_PROD := -std=c++11 -fPIC -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

# demo params
DEMO_DIR := ./demo
DEMO_SRC_DIR := ./demo/src
DEMO_OBJ_DIR := ./demo/bin
DEMO_BIN_DIR := ./demo/bin

# test params
TEST_DIR := ./test
TEST_COVERAGE_DIR := ./test-cov
TEST_COVERAGE_REPORT_FILE := coverage_report.info
TEST_SRC_DIR := ./test/src
TEST_OBJ_DIR := ./test/bin
TEST_BIN_DIR := ./test/bin
TEST_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(TEST_OBJ_DIR)/%.o,$(SRC_FILES)) 
CFLAGS_TEST := -std=c++11 --coverage -O0 -fprofile-arcs -ftest-coverage -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -lgtest

demo: $(DEMO_BIN_DIR)/demo

$(DEMO_BIN_DIR)/demo: $(OBJ_FILES) $(DEMO_SRC_DIR)/demo.cpp
	g++ $(CFLAGS_PROD) $(DEMO_SRC_DIR)/demo.cpp -o $@ $(OBJ_FILES)
	$(DEMO_BIN_DIR)/demo

test: $(TEST_BIN_DIR)/test

$(TEST_BIN_DIR)/test: $(TEST_OBJ_FILES) $(TEST_SRC_DIR)/test.cpp
	g++ $(CFLAGS_TEST) $(TEST_SRC_DIR)/test.cpp -o $@ $(TEST_OBJ_FILES)
	mkdir -p $(TEST_COVERAGE_DIR)
	$(TEST_BIN_DIR)/test
	lcov -d . --no-external --capture --output-file $(TEST_COVERAGE_DIR)/$(TEST_COVERAGE_REPORT_FILE) -rc lcov_branch_coverage=1
	genhtml $(TEST_COVERAGE_DIR)/$(TEST_COVERAGE_REPORT_FILE) --legend --output-directory=$(TEST_COVERAGE_DIR)

$(TEST_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CFLAGS_TEST) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CFLAGS_PROD) -c -o $@ $<

build: $(OBJ_FILES)
	g++ --shared -fPIC -o $(BIN_DIR)/libblimp.so $(OBJ_FILES)

clean:
	rm -rf ${BIN_DIR}
	mkdir -p ${BIN_DIR}
	rm -rf ${TEST_BIN_DIR}
	mkdir -p ${TEST_BIN_DIR}


.PHONY: test clean build
	