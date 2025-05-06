# Nexmon for Vanilla/Wii U

Nexmon is a framework for patching Broadcom Wi-Fi firmware. Since Broadcom chipsets are largely [FullMAC](https://wireless.docs.kernel.org/en/latest/en/developers/documentation/glossary.html#term-FullMAC), it is harder to do nonstandard things with them, such as the [patches required to connect to the Wii U as a gamepad](https://github.com/vanilla-wiiu/vanilla/wiki/Pipe). This repository adds patches to enable Broadcom chipsets to do that.

## Currently supported chipsets

- BCM4356 (Nintendo Switch)

## Usage (Nintendo Switch)

For the Nintendo Switch running L4T kernel 4.9, you should be able to download the release files and do the following:

1. Back up the original firmware located at the following location to somewhere safe:
   ```
   /lib/firmware/brcm/brcmfmac4356-pcie.bin
   ```

1. Replace the original firmware:
   ```
   sudo cp brcmfmac4356-pcie.bin /lib/firmware/brcm/
   ```

1. Load the new kernel module:
   The standard `brcmfmac` kernel module refuses to load custom firmware we installed, so we must use a modified version. This can be loaded temporarily, but upon next boot the original module will refuse to load until the original firmware is restored (or the custom module is once again loaded). Therefore you may find it more convenient to install it permanently. The custom module/firmware should still remain compatible with standard Wi-Fi connections, however there's a chance you will experience degraded network performance due to the lack of Switch-specific patches in our custom firmware.
   
   - Load custom kernel module temporarily:
     ```
     sudo rmmod brcmfmac
     sudo insmod brcmfmac.ko
     ```
   - Install and load custom kernel module permanently:
     ```
     sudo rmmod brcmfmac
     sudo cp brcmfmac.ko 
     sudo modprobe brcmfmac
     ```

You should now be able to use Vanilla as normal.

## Compiling (Nintendo Switch)

1. Open a Terminal. It is recommended to enter root mode to make installation easier using one of the following:

   ```
   sudo -i
   ```
   OR
   ```
   su
   ```

1. Install the dependencies:

   ```
   apt install linux-headers-$(uname -r) git libgmp3-dev gawk qpdf bison flex make autoconf libtool texinfo
   ```

   - On 32-bit systems:
     ```
     TODO
     ```
   - On 64-bit systems:
     ```
     sudo dpkg --add-architecture armhf
     sudo apt-get update
     sudo apt-get install libc6:armhf libisl23:armhf libmpfr6:armhf libmpc3:armhf libstdc++6:armhf
     sudo ln -s /usr/lib/arm-linux-gnueabihf/libisl.so.23.*  /usr/lib/arm-linux-gnueabihf/libisl.so.10
     sudo ln -s /usr/lib/arm-linux-gnueabihf/libmpfr.so.6.* /usr/lib/arm-linux-gnueabihf/libmpfr.so.4
     ```

1. Clone the repository and enter it:

   ```
   git clone https://github.com/vanilla-wiiu/nexmon.git
   cd nexmon
   ```

1. Set up the build environment:

   ```
   source setup_env.sh
   ```

1. Compile various tools used during the patching process:

   ```
   make
   ```

1. Browse to the `wiiu` patch for your chipset. For example, for BCM4356:

   ```
   cd patches/bcm4356/7_35_101_5_sta/wiiu
   ```

1. Backup the original firmware:

   ```
   make backup-firmware
   ```

7. Compile and install the new firmware:

   ```
   make install-firmware
   ```

## For more information

This is merely a fork of Nexmon that adds patches for the Wii U. For more information about Nexmon, please [check the upstream repository](https://github.com/seemoo-lab/nexmon).
