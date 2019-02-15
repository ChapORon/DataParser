SHADOW_BUILD_DIR = release

SHADOW_BUILD_DEBUG_DIR = debug

OUTPUT_DIR = .

TEST_OUTPUT_DIR = test/bin

LIBNAME = DataParser

NAME = lib$(LIBNAME).so

DEBUG = lib$(LIBNAME)D.so

TEST = $(LIBNAME)DTest

all: release

$(TEST) :
	mkdir -p $(SHADOW_BUILD_DIR)
	cd $(SHADOW_BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Test ..
	make -j8 -C $(SHADOW_BUILD_DIR)
	cd $(TEST_OUTPUT_DIR) && ./$(TEST)

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
	rm -Rf $(OUTPUT_DIR)/$(NAME)
	rm -Rf $(TEST_OUTPUT_DIR)/$(TEST)
	rm -Rf $(OUTPUT_DIR)/$(DEBUG)

re: fclean all

install: uninstall fclean release
	sudo cp $(NAME) /usr/lib
	sudo cp -R include/dp /usr/include

uninstall:
	sudo rm -rf /usr/lib/$(NAME)
	sudo rm -rf /usr/include/dp
