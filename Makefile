# prod params
SRC_DIR := ./src
BIN_DIR := ./bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRC_FILES)) 
CFLAGS_PROD := -std=c++14 -fPIC -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi

# demo params
DEMO_DIR := ./demo
DEMO_SRC_DIR := ./demo/src
DEMO_BIN_DIR := ./demo/bin

# test params
TEST_DIR := ./test
TEST_COVERAGE_DIR := ./test-cov
TEST_COVERAGE_REPORT_FILE := coverage_report.info
TEST_SRC_DIR := ./test/src
TEST_BIN_DIR := ./test/bin
TEST_OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(TEST_BIN_DIR)/%.o,$(SRC_FILES)) 
CFLAGS_TEST := -std=c++14 --coverage -O0 -fprofile-arcs -ftest-coverage -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -lgtest

DOCS_DIR := ./docs

demo: $(DEMO_BIN_DIR)/demo

$(DEMO_BIN_DIR)/demo: $(OBJ_FILES) $(DEMO_SRC_DIR)/demo.cpp
	mkdir -p $(DEMO_BIN_DIR)
	g++ $(CFLAGS_PROD) $(DEMO_SRC_DIR)/demo.cpp -o $@ $(OBJ_FILES)
	$(DEMO_BIN_DIR)/demo

test: $(TEST_BIN_DIR)/test

$(TEST_BIN_DIR)/test: $(TEST_OBJ_FILES) $(TEST_SRC_DIR)/test.cpp
	mkdir -p $(TEST_BIN_DIR)
	g++ $(CFLAGS_TEST) $(TEST_SRC_DIR)/test.cpp -o $@ $(TEST_OBJ_FILES)
	mkdir -p $(TEST_COVERAGE_DIR)
	$(TEST_BIN_DIR)/test
	lcov -d . --no-external --capture --output-file $(TEST_COVERAGE_DIR)/$(TEST_COVERAGE_REPORT_FILE) -rc lcov_branch_coverage=1
	genhtml $(TEST_COVERAGE_DIR)/$(TEST_COVERAGE_REPORT_FILE) --legend --output-directory=$(TEST_COVERAGE_DIR)

$(TEST_BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(TEST_BIN_DIR)
	g++ $(CFLAGS_TEST) -c -o $@ $<

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(BIN_DIR) 
	g++ $(CFLAGS_PROD) -c -o $@ $<

build: $(OBJ_FILES)
	g++ --shared -fPIC -o $(BIN_DIR)/libblimp.so $(OBJ_FILES)

docs: $(SRC_FILES)
	cd $(DOCS_DIR); doxygen

clean:
	-rm ${BIN_DIR}/*.o
	-rm ${TEST_BIN_DIR}/*.o

.PHONY: test clean build
	