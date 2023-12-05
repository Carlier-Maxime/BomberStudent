CC = g++
LD = g++
CFLAGS = -Wall -Wextra -pedantic -std=c++17 -pthread -Ithird_party
ifdef DEBUG
    CFLAGS += -g
endif
LD_FLAGS = -lpthread -lstdc++fs
SRC_DIR = src
OBJ_DIR = obj
GLOBAL_DIR = utils socket ipc json game
OBJS_GLOBAL = $(foreach dir, $(GLOBAL_DIR), $(patsubst $(SRC_DIR)/$(dir)/%.cpp,$(OBJ_DIR)/$(dir)/%.o,$(wildcard $(SRC_DIR)/$(dir)/*.cpp)))
EXE = bomberStudentServer clientDev
OBJ_DIRS := $(addprefix $(OBJ_DIR)/, $(EXE) $(GLOBAL_DIR))

all : $(OBJ_DIRS) $(EXE)
$(OBJ_DIRS):
	@mkdir -p $@

define build_exe
$(1) : $(OBJS_GLOBAL) $(patsubst $(SRC_DIR)/$(1)/%.cpp,$(OBJ_DIR)/$(1)/%.o,$(wildcard $(SRC_DIR)/$(1)/*.cpp))
	$(LD) $$^ $(LD_FLAGS) -o $$@
endef


$(foreach exe, $(EXE), $(eval $(call build_exe,$(exe))))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf  $(OBJ_DIR) $(EXE)

define build_dep
$(OBJ_DIR)/$(1)/%.d: $(SRC_DIR)/$(1)/%.cpp $(OBJ_DIR)/$(1)
	@$(CC) -MM $$< | sed 's/\($$*\)\.o[ :]*/$(OBJ_DIR)\/$(1)\/\1.o : /g' > $$@
endef

$(foreach exe, $(EXE) $(GLOBAL_DIR), $(eval $(call build_dep,$(exe))))

DEPS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.d,$(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp))


.PHONY: clean all

-include $(DEPS)