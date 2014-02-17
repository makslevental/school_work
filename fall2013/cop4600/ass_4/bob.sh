#!/bin/bash
make mrproper
make mrproper ARCH=um
make ARCH=um defconfig
make ARCH=um menuconfig
make ARCH=um
