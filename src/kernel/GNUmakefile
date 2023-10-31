

# PARSING FILES AND DEFINING THEIR OUTPUT VARIANTS

# Finds all .c and .s files and converts to the output files (with .o extension)
KERNEL_C_FILES              := $(shell find -L src/kernel/ -type f -name '*.c')
KERNEL_ASSEMBLY_FILES       := $(shell find -L src/kernel/ -type f -name '*.S')
KERNEL_OUTPUT_FILES         := $(addprefix $(BUILD_DIRECTORY)/, $(patsubst %.c, %.o, $(KERNEL_C_FILES)) $(patsubst %.S, %.o, $(KERNEL_ASSEMBLY_FILES)))


#COMPILES SOURCE FILES IN TO OUTPUT FILES (parsed above)

$(addprefix $(BUILD_DIRECTORY)/, %.o)    : %.c
	@echo -e "\n=>\e[0;31mCOMPILING FILE: \e[0m:$<"    
	@$(KERNEL_COMPILER) $(KERNEL_C_FLAGS) -c $< -o ./$@


$(addprefix $(BUILD_DIRECTORY)/, %.o)    : %.S
	@echo -e "\n=>\e[0;31mASSEMBLING FILE: \e[0m:$<"
	$(KERNEL_ASSEMBLER) $(INCLUDE_DIRECTORIES) -E ./$< -o ./$(patsubst %.o,%.S, $@)
	$(KERNEL_ASSEMBLER) $(KERNEL_ASSEMBLER_FLAGS) -c ./$(patsubst %.o,%.S, $@) -o ./$@
	


#LINKS OUTPUT FILES

link_kernel:
	@echo -e "\n=>\e[0;31mLINKING KERNEL...\e[0m"
	@$(KERNEL_LINKER) $(KERNEL_OUTPUT_FILES) $(KERNEL_LINKER_FLAGS) -o $(BUILD_DIRECTORY)/$(KERNEL_NAME)


#PRINTS SOME INFO ABOUT COMPILATION
kernel_info:
	@echo compiler: $(KERNEL_COMPILER)
	@echo -e "\nfiles:\n$(KERNEL_OUTPUT_FILES)" | tr " " "\n"


#BUILD KERNEL GROUPING

build_kernel: kernel_info $(KERNEL_OUTPUT_FILES) link_kernel






    