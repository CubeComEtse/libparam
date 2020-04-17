
ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

#################################### C Compiler settings #####################

C_COMPILER=gcc

# CFLAGS=-std=c99
CFLAGS= -Wall
CFLAGS += -Wextra
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-align
CFLAGS += -Wwrite-strings
CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -Wold-style-definition
CGLAGS += -v
CGLAGS += -g

DEFINES=-Dbool=_Bool 

LIBS=

SYMBOLS=

export C_COMPILER CFLAGS DEFINES  LIBS SYMBOLS

#################################### Code Includes ###########################

CC=gcc

GENERAL_DEFINES = -DASF_ADC\
				  -DPROGMEM=\
				  -Dbool=_Bool\
				  -DTEST

CODE_INCLUDE=\
		-I./mocks \
		-I./header_replacements \
		-I../src \
		-I../src/config \
		-I../inc

LIBRARIES= -lcmocka-static -lm

# Its easier just to compile all the mocks
MOCKED_MODULES = usart bsp
MOCKED_FILES_OUTPUT = $(foreach MOCK,$(MOCKED_MODULES),obj/$(MOCK)_mocks.o)
$(info $$MOCKED_FILES_OUTPUT is [${MOCKED_FILES_OUTPUT}])

# TEST_SOURCE = obj/test_data_logger.o
# SOURCE = obj/data_logger.o

# Gather all the test targets by collecting the folders starting with test_
# No validation is done that the files exist, you have to do this yourself.
TEST_DIRECTORIES = $(subst /,,$(subst ./,,$(sort $(dir $(wildcard ./test_*/)))))
TEST_EXECUTABLES = $(foreach DIR,$(TEST_DIRECTORIES),executables/$(DIR)$(TARGET_EXTENSION))

$(info $$TEST_EXECUTABLES is [${TEST_EXECUTABLES}])

$(foreach DIR,$(TEST_DIRECTORIES),$(eval include ./$(DIR)/makefile))

vpath %.c $(TEST_DIRECTORIES) ./mocks/

test_%_makefile:
	# Setting specific Wraps for $@
	$(eval SPECIFIC_WRAPS = $(shell echo test_$*_wraps | tr a-z A-Z ))
	$(eval SPECIFIC_WRAP_FLAG = $(foreach MOCK,$($(SPECIFIC_WRAPS)),-Wl,--wrap=$(MOCK)))

	# Setting specific defines for $@
	$(eval SPECIFIC_DEFINES = $(shell echo test_$*_defines | tr a-z A-Z ))
	$(eval SPECIFIC_DEFINES_FLAG= $($(SPECIFIC_DEFINES)))

	$(eval SPECIFIC_LINKS = $(shell echo test_$*_links | tr a-z A-Z ))
	$(eval SPECIFIC_LINKS_FLAG = $($(SPECIFIC_LINKS)))

	$(info '---------------------------------------------------------------------')
	$(info $$SPECIFIC_WRAPS is [${SPECIFIC_WRAPS}])
	$(info $$SPECIFIC_WRAPS value is  [$($(SPECIFIC_WRAPS))])
	$(info $$SPECIFIC_WRAP_FLAG value is [$(SPECIFIC_WRAP_FLAG)])
	$(info $$SPECIFIC_DEFINES is [${SPECIFIC_DEFINES}])
	$(info $$SPECIFIC_DEFINES value is [$($(SPECIFIC_DEFINES))])
	$(info $$SPECIFIC_DEFINES_FLAG is [${SPECIFIC_DEFINES_FLAG}])
	$(info $$SPECIFIC_LINKS_FLAG is [${SPECIFIC_LINKS_FLAG}])
	$(info $$MOCKED_FILES_OUTPUT is [${MOCKED_FILES_OUTPUT}])

	$(eval SPECIFIC_INCLUDES=-I./test_$*/)

# Rule for mock files
# obj/%.o: mocks/%.c
# 	$(C_COMPILER) -c $(GENERAL_DEFINES) $(CODE_INCLUDE) $(LIBRARIES) $< -o $@

# Rule for tests and source
obj/%.o: %.c
	$(C_COMPILER) -c $(GENERAL_DEFINES) $($(SPECIFIC_DEFINES)) $(SPECIFIC_INCLUDES) $(CODE_INCLUDE) $(LIBRARIES) $< -o $@

#Rule for source
obj/%.o: ../src/%.c
	$(C_COMPILER) -c $(GENERAL_DEFINES) $($(SPECIFIC_DEFINES)) $(SPECIFIC_INCLUDES) $(CODE_INCLUDE) $(LIBRARIES) $< -o $@

# Link everyting together
executables/test_%$(TARGET_EXTENSION):  test_%_makefile obj/test_%.o obj/%.o  $(MOCKED_FILES_OUTPUT)
	# We have to call recursively:
	# The variable can't be used in the rules, since these are evaluated only once.
	# The same goes for if/endif statements, the comparision is done at startup
	$(if $(SPECIFIC_LINKS_FLAG),$(MAKE) $(SPECIFIC_LINKS_FLAG),)

	$(C_COMPILER) $(GENERAL_DEFINES) $(SPECIFIC_INCLUDES)  $(CODE_INCLUDE) $(SPECIFIC_WRAP_FLAG) $(SPECIFIC_LINKS_FLAG) $(MOCKED_FILES_OUTPUT) $(word 2,$^) $(word 3,$^) $(LIBRARIES) -o $@

all: directories $(TEST_EXECUTABLES)

.PHONY: directories clean
.SECONDARY: $(TEST_EXECUTABLES)

directories:
	$(MKDIR) obj
	$(MKDIR) executables

clean:
	$(CLEANUP) obj/*.o
	$(CLEANUP) executables/*$(TARGET_EXTENSION)