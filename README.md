## Simple FPU benchmark

This simple program was created to collect time elapsed after doing some math and to compare
execution times using and not using Hyper Threading (HT).

All tests was executed by a CPU Intel Core i3, 2.13 GHz, with 2 real cores, 2 Threads per core,
summing up to 4 CPUs. The OS used to execute this project was Linux, with Ubuntu distribution.

All of CPU data was collected by using `lscpu` command.


### Results

1. With Hyper Threading (HT)

```
$ time ./bin/main

real    0m48,564s
user    1m22,189s
sys     1m43,546s
```

2. __Without__ Hyper Threading (HT)

```
$ time ./bin/main
real    0m35,414s
user    0m41,180s
sys     0m25,243s
```

### How to enable/disable HT usage on Linux OS

By running `lscpu --extended` I found out the following results:

```
CPU NODE SOCKET CORE L1d:L1i:L2:L3 ONLINE MAXMHZ    MINMHZ
0   0    0      0    0:0:0:0       yes    2133,0000 933,0000
1   0    0      0    0:0:0:0       yes    2133,0000 933,0000
2   0    0      1    1:1:1:0       yes    2133,0000 933,0000
3   0    0      1    1:1:1:0       yes    2133,0000 933,0000
```

Each core is represented by a special file located at `/sys/devices/system/cpu/cpuN/online`
where `N` is the core index varying between 0 and 3 on my machine (Intel Core i3).

To disable cpu1 and cpu3 just run the following commands:

```
echo 0 > /sys/devices/system/cpu/cpu1/online
echo 0 > /sys/devices/system/cpu/cpu3/online
```

To enable them:

```
echo 1 > /sys/devices/system/cpu/cpu1/online
echo 1 > /sys/devices/system/cpu/cpu3/online
```
