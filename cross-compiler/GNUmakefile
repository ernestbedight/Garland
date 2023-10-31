#BUILD STUBB
build_cross_compiler_stubb:binutils gcc  

#DEFINE VARIABLES
CROSS_COMPILER_DESTINATION  :=    ./cross-compiler
PREFIX                      :=    $(shell pwd)/compiler
TARGET                      :=    x86_64-elf

CONFIGURE_DEFAULT_FLAG      := --target=$(TARGET) --prefix="$(PREFIX)"


#gdb-binutiils INSTALL

.PHONY: binutils 

binutils:
	cd $(CROSS_COMPILER_DESTINATION)                                                                                                     ;\
	clear                                                                                                                                ;\
	echo -e "\n=>\e[0;31mCURRENT DIRECTORY \e[0m in:"                                                                                    ;\
	pwd                                                                                                                                  ;\
	echo -e "\n=>\e[0;31mCLONING BINUTILS-GDB \e[0m in:"                                                                                 ;\
	pwd                                                                                                                                  ;\
	sudo rm -rf ./binutils                                                                                                               ;\
	git clone git://sourceware.org/git/binutils-gdb.git ./binutils                                                                       ;\
	cd "./binutils/"                                                                                                                     ;\
	echo -e "\n=>\e[0;31mCONFIGURING BINUTILS-GDB \e[0m in:"                                                                             ;\
	pwd                                                                                                                                  ;\
	./configure     $(CONFIGURE_DEFAULT_FLAG) --with-sysroot --disable-nls                                                               ;\
	echo -e "\n=>\e[0;31mBUILDING BINUTILS-GDB \e[0m in:"                                                                                ;\
	pwd                                                                                                                                  ;\
	sudo make                                                                                                                            ;\
	sudo make install                                                                                                                    ;\
	sudo make all-gdb                                                                                                                    ;\
	sudo make install-gdb                                                                                                                ;


#GCC INSTALL SCRIPT

.PHONY: gcc

gcc:
	clear                                                                                                                                ;\
	echo PREFIX:$(PREFIX)                                                                                                                ;\
	echo -e "\n=>\e[0;31mCLONING GCC \e[0m in:"                                                                                          ;\
	pwd                                                                                                                                  ;\
	echo -e "\n"                                                                                                                         ;\
	git clone git://gcc.gnu.org/git/gcc.git ./gcc                                                                                        ;\
	echo -e "\n=>\e[0;31mCONFIGURING GCC \e[0m in:"                                                                                      ;\
	pwd                                                                                                                                  ;\
	echo -e "\n"                                                                                                                         ;\
	cd "./gcc"                                                                                                                           ;\
	echo sudo ./gcc/configure     $(CONFIGURE_DEFAULT_FLAG) --disable-nls --enable-languages=c,c++ --without-headers                     ;\
	./configure         $(CONFIGURE_DEFAULT_FLAG) --disable-nls --enable-languages=c,c++ --without-headers                               ;\
	echo -e "\n=>\e[0;31mBUILDING GCC \e[0m in:"                                                                                         ;\
	pwd                                                                                                                                  ;\
	echo -e "\n"                                                                                                                         ;\
	sudo -E make all-gcc                                                                                                                    ;\
	sudo -E make all-target-libgcc                                                                                                          ;\
	sudo -E make install-gcc                                                                                                                ;\
    echo checkpoint                                                                                                                      ;\
    sudo -E make install-target-libgcc


