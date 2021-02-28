# Virtual_CAN_Device
[ TOC ]

## 概述

## 使用
```sh
sudo modprobe vcan
sudo ip link add can0 type vcan
sudo ip link set can0 up

./virtual_can_device -n DEV_0 -d 3

```
