# GarlandOS
## Dependencies
```
make gcc git xorriso qemu
```
## Cross-Compiler setup
```bash
make build_cross_compiler
```
## Limine download
To download Limine through the makefile type:
```bash
make limine
```
## OS compilation
Compile the OS in the Makefile directory with:
```bash
make
```
## USB booting
after compiling it as normal you can write the iso file to a usb device (change mounting point in the makefile var based on your own device):
```
make write
```
After making sure you have your test usb plugged in to test if it has been written correctly run:
```
make runusb
```
## photo
![image](https://github.com/ernestbedight/GarlandOS/assets/129771554/b1780f62-1d4f-4f12-970b-de214734dad8)
