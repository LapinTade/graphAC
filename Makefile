OBJ_DIR=OBJ
SRC_DIR=SRC
BIN_DIR=BIN
LIB_DIR=LIB
MAIN=$(BIN_DIR)/main
CFLAGS= -g
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CC = gcc
ARBORESCENCE=$(OBJ_DIR) $(SRC_DIR) $(BIN_DIR) $(LIB_DIR)
LIB_LISTE=$(LIB_DIR)/libliste.a
LIB_GRAPHE=$(LIB_DIR)/libprojet.a
LIBS=$(LIB_LISTE) $(LIB_GRAPHE)
LINK_LIBS=-lprojet -lliste 
O_FILES=$(filter-out $(OBJ_DIR)/lib%.o, $(OBJ))

all: $(ARBORESCENCE) $(MAIN)

$(MAIN): $(O_FILES) $(LINK_LIBS) 
	$(CC) $(CFLAGS) -L $(LIB_DIR) $(O_FILES) -o $@ $(LINK_LIBS)

$(LINK_LIBS): $(LIBS)

$(LIBS): $(LIB_DIR)/%.a : $(OBJ_DIR)/%.o
	ar rvs $@ $<

$(ARBORESCENCE):
	mkdir $@

$(OBJ) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(OBJ) $(BIN_DIR) $(LIB_DIR)
	
mrproper : clean
	rm -f $(MAIN)
