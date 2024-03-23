
#GARLAND OPERATING SYSTEM

include ./metadata/build.mk

#INCLUDED ABSTRACTION
all:clear clone_directories limine_header compile_kernel limine_build

#SECURE RULES
.PHONY:                     \
compile_kernel              \
run                         \
debug                       \
runusb                      \
push                        \
clear                       \
write                       \
limine_build                \
limine_download             \
limine_header               \
specify_compiler_path       

                
run:                
	$(QEMU)                                                                  \
	$(QEMU_FLAGS)                                                            \
	$(QEMU_LOCAL_SOURCE)                                                     

pauserun:                
	$(QEMU)                                                                  \
	$(QEMU_FLAGS)                                                            \
	$(QEMU_LOCAL_SOURCE)                                                     \
	$(QEMU_PAUSE_ON_START_FLAG)
                
debug:                                                    
	$(QEMU)                                                                  \
	$(QEMU_FLAGS)                                                            \
	$(QEMU_LOCAL_SOURCE)                                                     \
	$(QEMU_DEBUG_FLAG)                                                    	 \
	$(QEMU_PAUSE_ON_START_FLAG)
                
runusb:                                                    
	$(QEMU)                                                                  \
	$(QEMU_FLAGS)                                                            \
	$(QEMU_USB_SOURCE)

#GIT HUB UPLOAD
push:clear
	git add .                                                               ;\
	read -p "commit text : " COMMIT                                          \
	&& echo "commit : $${COMMIT}"                                           ;\
	git commit -a -m "$$COMMIT"                                             ;\
	git push -f

#CLEANING TOOLS
clear:
	clear
	@echo -e "\n=>\e[0;31mCLEANING...\e[0m"
	@-mkdir -p ./Build
	@rm -rf $(BUILD_DIRECTORY)/*

#WRITING ONTO A MOUNTING POINT
write:
	dd if=$(BUILD_DIRECTORY)/$(IMAGE_NAME) of=$(USB_MOUNT_POINT) obs=1M oflag=direct status=none
#it might brick your mouse if the usb devuce is not plugged, to fix close qemu windows through shortcuts

#LIMINE SETUP

limine: limine_download

limine_build:
	@echo -e "\n=>\e[0;31mBUILDING LIMINE...\e[0m"
	@-mkdir -p $(BUILD_DIRECTORY)/IsoRoot
	@cp                                                  \
	$(BUILD_DIRECTORY)/$(KERNEL_NAME)                    \
	$(LIMINE_CONFIGURATION_FILE)                         \
	$(LIMINE_DIRECTORY)/limine.sys                       \
	$(LIMINE_DIRECTORY)/limine-cd.bin                    \
	$(LIMINE_DIRECTORY)/limine-cd-efi.bin                \
	$(BUILD_DIRECTORY)/IsoRoot            	
	@xorriso                                                 \
        -as mkisofs                                          \
        -b limine-cd.bin                                     \
        -no-emul-boot                                        \
        -boot-load-size 4                                    \
        -boot-info-table                                     \
        --efi-boot limine-cd-efi.bin                         \
        -efi-boot-part                                       \
        --efi-boot-image                                     \
        --protective-msdos-label                             \
        $(BUILD_DIRECTORY)/IsoRoot                           \
        -o $(BUILD_DIRECTORY)/$(IMAGE_NAME)

	@$(LIMINE_DIRECTORY)/limine-deploy $(BUILD_DIRECTORY)/$(IMAGE_NAME)


limine_download:
	@echo -e "\n=>\e[0;31mDOWNLOADING LIMINE...\e[0m"
	rm -rf $(LIMINE_DIRECTORY)
	git clone https://github.com/limine-bootloader/limine.git $(LIMINE_DIRECTORY) --branch=v4.x-branch-binary --depth=1 && make -C $(LIMINE_DIRECTORY)

limine_header:
	cp $(LIMINE_DIRECTORY)/limine.h $(BUILD_DIRECTORY)/limine_header/


#INCLUDING RULES
include ./src/kernel/kernel.mk

#FOR FUTURE FEATURES

compile_kernel: build_kernel


#CREATES A CLONE OF THE SOURCE DIRECTORIES TO BUILD IN

clone_directories:
	@echo -e "\n=>\e[0;31mCREATING DIRECTORIES...\e[0m"
	@rsync -av -f"+ */" -f"- *" "./src" "$(BUILD_DIRECTORY)"
	@mkdir -p $(BUILD_DIRECTORY)/limine_header


        