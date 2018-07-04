SHADOW_BUILD_DIR = release

SHADOW_BUILD_DEBUG_DIR = debug

OUTPUT_DIR = .

TEST_OUTPUT_DIR = test

LIBNAME = DataParser

NAME = $(OUTPUT_DIR)/lib$(LIBNAME).so

DEBUG = $(OUTPUT_DIR)/lib$(LIBNAME)D.so

TEST = $(TEST_OUTPUT_DIR)/$(LIBNAME)DTest

all: release

$(TEST) :
	mkdir -p $(SHADOW_BUILD_DIR)
	cd $(SHADOW_BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Test ..
	make -j8 -C $(SHADOW_BUILD_DIR)
	@$(TEST)

$(NAME) :
	mkdir -p $(SHADOW_BUILD_DIR)
	cd $(SHADOW_BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Release ..
	make -j8 -C $(SHADOW_BUILD_DIR)

$(DEBUG) :
	mkdir -p $(SHADOW_BUILD_DEBUG_DIR)
	cd $(SHADOW_BUILD_DEBUG_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug ..
	make -j8 -C $(SHADOW_BUILD_DEBUG_DIR)

release : $(NAME)

debug : $(DEBUG)

test : $(TEST)

clean :
	rm -Rf $(SHADOW_BUILD_DIR)
	rm -Rf $(SHADOW_BUILD_DEBUG_DIR)

fclean : clean
	rm -Rf $(NAME)
	rm -Rf $(TEST)
	rm -Rf $(DEBUG)

re: fclean all

rerelease: fclean release

redebug: fclean debug
