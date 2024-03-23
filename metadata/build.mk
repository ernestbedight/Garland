

#GENERAL SPECIFICATIONS

IMAGE_NAME                      :=    garland.iso
USB_MOUNT_POINT                 :=    /dev/sda
BUILD_DIRECTORY                 :=    ./Build
CROSS_COMPILER_DESTINATION      :=    ./cross-compiler


#KERNEL SPECIFICATIONS

KERNEL_NAME                     :=     garland.elf

ifneq ($(wildcard ./cross-compiler/compiler/bin/x86_64-elf-gcc),)
KERNEL_COMPILER                 :=     ./cross-compiler/compiler/bin/x86_64-elf-gcc
else
KERNEL_COMPILER                 :=     gcc
endif

KERNEL_LINKER                   :=     ld
KERNEL_ASSEMBLER                :=     gcc

# All the flags for linker and compiler

INCLUDE_DIRECTORIES       :=                                                 \
                            -I src/kernel/common/                            \
                            -I src/kernel/sys_lib/                           \
                            -I $(BUILD_DIRECTORY)/limine_header              

KERNEL_C_FLAGS            :=                                                 \
                            -Wall                                            \
                            -Wextra                                          \
                            -Wno-unused-parameter                            \
                            -std=gnu11                                       \
                            -ffreestanding                                   \
                            -fno-stack-protector                             \
                            -fno-stack-check                                 \
                            -fno-lto                                         \
                            -fno-PIE                                         \
                            -fno-PIC                                         \
                            -m64                                             \
                            -march=x86-64                                    \
                            -mabi=sysv                                       \
                            -mno-80387                                       \
                            -mno-mmx                                         \
                            -msoft-float                                     \
                            -mgeneral-regs-only                              \
                            -mno-sse                                         \
                            -mno-red-zone                                    \
                            -mcmodel=kernel                                  \
                            $(INCLUDE_DIRECTORIES)                           \
                            -g                                               \
                            -O3


KERNEL_ASSEMBLER_FLAGS      :=                                               \
                            $(KERNEL_C_FLAGS)                                \
                            -no-pie                                          \
                            -g                                               
                            
KERNEL_LINKER_FLAGS         :=                                               \
                            -nostdlib                                        \
                            -static                                          \
                            -m elf_x86_64                                    \
                            -z                                               \
                            max-page-size=0x1000                             \
                            -no-pie                                          \
                            -T src/kernel/linker_scripts/linker.ld           \

#LIMINE INFO

LIMINE_CONFIGURATION_FILE     := ./src/kernel/limine_configuration/limine.cfg
LIMINE_DIRECTORY              := ./packages/limine

#RUN TOOLS
QEMU                        :=     qemu-system-x86_64

QEMU_FLAGS                  :=                                               \
                            -d int,guest_errors,cpu_reset                    \
                            -no-reboot                                       \
                            -no-shutdown                                     \
                            -device                                          \
                            VGA,edid=on,xres=1920,yres=1080                  \
                            -cpu Skylake-Client-v4                           \
                            -machine type=q35                                \
                            -m 2G                                            
                
#,-sse,-sse2,-sse3,-ssse3,-sse4.1,-sse4.2,-fpu                
#add to -cpu to test without certain features                
                
QEMU_DEBUG_FLAG            :=    -s     
QEMU_PAUSE_ON_START_FLAG   :=    -S           
                
QEMU_LOCAL_SOURCE          :=    -hda $(BUILD_DIRECTORY)/$(IMAGE_NAME)                
QEMU_USB_SOURCE            :=    -hda $(USB_MOUNT_POINT)
