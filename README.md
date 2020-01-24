### Credit

Original Credit goes to [@Dark_Puzzle](https://twitter.com/Dark_Puzzle) whom disclosed [Here](http://rce4fun.blogspot.com/2018/02/malwarefox-antimalware-zam64sys.html) the privileged registration. I only expanded upon this to use an additional IOCTL to open a thread (it calls ZwOpenThread())

### Build

You can build the shellcode / executable using mingw-w64. To do so, just run from a Unix / MacOS X Installation : `x86_64-w64-mingw32-gcc *.c -o ppldump.exe`. Currently only supports x64, as I have not been able to obtain a 32 bit version of the zam.sys driver.

Written by Austin Hudson of GuidePoint Security

### Usage

![](https://i.imgur.com/ShQ6ucp.png)

![](https://i.imgur.com/umaTT1x.png)
