# Virtual_CAN_Device
[ TOC ]

## 概述

## 使用
```sh
$ sudo modprobe vcan
$ sudo ip link add can0 type vcan
$ sudo ip link set can0 up

$ ifconfig can0
can0: flags=193<UP,RUNNING,NOARP>  mtu 72
        unspec 00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00  txqueuelen 1000  (UNSPEC)
        RX packets 185  bytes 1480 (1.4 KiB)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 185  bytes 1480 (1.4 KiB)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0

./virtual_can_device -n DEV_0 -d 3

```
