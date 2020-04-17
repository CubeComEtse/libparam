COMPONENT_NAME=serial_multiplex

# Files from the source
SRC_FILES = \
  "$(PROJECT_SRC_DIR)/serial_multiplexer.c"
TEST_SRC_FILES = \
  test_serial_multiplexer.c

all:
	$(COMPILE) $(CFLAGS) $(TEST_SRC_FILES) $(SRC_FILES) -I"$(PROJECT_INC_DIR)" -o test_$(COMPONENT_NAME)$(TARGET_EXTENSION)
