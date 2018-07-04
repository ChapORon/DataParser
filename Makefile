SHADOW_BUILD_DIR = release

SHADOW_BUILD_DEBUG_DIR = debug

LIBNAME = DataParser

NAME = lib$(LIBNAME).so

DEBUG = lib$(LIBNAME)D.so

TEST = $(LIBNAME)Test

TESTDEBUG = $(TEST)D

all: release

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

clean :
	rm -Rf $(SHADOW_BUILD_DIR)
	rm -Rf $(SHADOW_BUILD_DEBUG_DIR)

fclean : clean
	rm -Rf $(NAME)
	rm -Rf $(TEST)
	rm -Rf $(DEBUG)
	rm -Rf $(TESTDEBUG)

re: fclean all

rerelease: fclean release

redebug: fclean debug
