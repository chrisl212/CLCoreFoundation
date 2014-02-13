header_dir=/usr/include/CLCoreFoundation
lib_dir=/usr/lib
LIB_NAME=libclcorefoundation
LIB_EXT=so
LDCONFIG=ldconfig
UNAME := $(shell uname)
ifeq ($(UNAME),Darwin)
LIB_EXT=dylib
LDCONFIG=echo
endif

library:
@echo Compiling source...
	@gcc -c *.c
	@echo Creating library...
	@gcc -shared -o $(LIB_NAME).$(LIB_EXT) *.o -lm
	@echo Installing library...
	@cp $(LIB_NAME).$(LIB_EXT) $(lib_dir)
	@$(LDCONFIG)
	@echo Copying headers...
	@mkdir -p $(header_dir)
	@cp *.h $(header_dir)
	@echo Cleaning up...
	@rm *.o
	@echo Done