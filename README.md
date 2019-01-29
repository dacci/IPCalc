To generate project files for 64-bit binaries:

``` bat
gyp --depth=. IPCalc.gyp
```

To generate project files for 32-bit binaries:

``` bat
gyp --depth=. -Dtarget_arch=ia32 IPCalc.gyp
```
