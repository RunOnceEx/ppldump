# About

ppldump (c) is an experimental utility for dumping Protected Process Light process'es, specifically Lsass to retrive credentials from remote memory. With modifications, and possibly for a later addition in the future, it supports injecting shellcode into EDR Engine(s) and Windows Defender.

It achives this ability through the abuse of signed AntiVirus Engine Driver from a third-party develop whom has refused to patch a flaw concerning their driver. As a result, it permits an authenticted user to impersonate the engine and execute privilege'd operations such as the ability to steal processes handles in kernel memory, as well as thread handles to perform privileged operations with full access.

The bug itself concerning the theft of privileged process handles was disclosed previously to the vendor, however, I did not disclose the theft of thread handles as it required the original pre-requisitie of registering itself with the driver.

### Build

You can build the shellcode / executable using mingw-w64. To do so, just run from a Unix / MacOS X Installation : `x86_64-w64-mingw32-gcc *.c -o ppldump.exe`. Currently only supports x64, as I have not been able to obtain a 32 bit version of the zam.sys driver.

Written by Austin Hudson of GuidePoint Security

### Usage

![](https://i.imgur.com/ShQ6ucp.png)
