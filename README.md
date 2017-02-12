# Linux Kernel Module Configuration Tool
`lsmodconf` can be used to determine which of loadable Linux kernel modules  
are essential for an OS to operate on the current machine.
Its aim is to help build lightweight kernels which omit everything
that the current hardware does not require to operate.

### Usage
Within Linux source code tree:
    lsmod | ./lsmodconf .config
Against /boot/config:
    lsmod | ./lsmodconf /boot/config-`uname -r`

### How it works
Once you pipe the output of `lsmod` into `lsmodconf` via stdin and specify the location
of your Linux Kernel `.config` file you're about to use for compiling
your new kernel, `lsmodconf` will point out the current choices [n/m/y]
for those modules which seem to be important for your system to operate.  
Disabling as many modules as possible and turning only the ones that your
system automatically loads seems to be the easiest way to build
a very lightweight yet fully operational kernel.

### Copying
Licensed under GPLv3
