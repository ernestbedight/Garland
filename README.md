# GarlandOS
## Dependencies
```
make gcc git xorriso qemu
```
## Limine download
To download Limine through the makefile type:
```bash
make limine
```
## Building the oprating system
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