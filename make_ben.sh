#!/bin/bash

echo "build kernel"
#source /opt/poky/2.0.2/environment-setup-cortexa9hf-vfp-neon-poky-linux-gnueabi
#export ARCH=arm
#export CROSS_COMPILE=arm-poky-linux-gnueabi-

#fsl toolchian
export ARCH=arm
export CROSS_COMPILE=/opt/fsl-linaro-toolchain/bin/arm-fsl-linux-gnueabi-

#make ../defconfig
make -j16;
#make imx6q-b506a.dtb;
#make imx6dl-b506a.dtb
make imx6ul-armt-s607.dtb
#make imx6q-s606.dtb

rm zImage uImage
rm *.dtb
cp arch/arm/boot/zImage ./
cp arch/arm/boot/uImage ./
#cp arch/arm/boot/dts/imx6q-b506a.dtb ./
#cp arch/arm/boot/dts/imx6dl-b506a.dtb ./
cp arch/arm/boot/dts/imx6ul-armt-s607.dtb ./
#cp arch/arm/boot/dts/imx6q-s606.dtb ./


echo "build end"
