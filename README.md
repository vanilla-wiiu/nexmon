# Nexmon for Vanilla/Wii U

Nexmon is a framework for patching Broadcom Wi-Fi firmware. Since Broadcom chipsets are largely [FullMAC](https://wireless.docs.kernel.org/en/latest/en/developers/documentation/glossary.html#term-FullMAC), it is harder to do nonstandard things with them, such as the [patches required to connect to the Wii U as a gamepad](https://github.com/vanilla-wiiu/vanilla/wiki/Pipe). This repository adds patches to enable Broadcom chipsets to do that.

## Currently supported chipsets

- BCM4356 (Nintendo Switch)

## Usage (Nintendo Switch)

The release builds have been tested to work with L4T **Ubuntu 24.04**. For other distros, it's recommended you follow the **Compiling** instructions below instead.

1. If it exists, back up the original firmware located at the following location to somewhere safe:
   ```
   /lib/firmware/brcm/brcmfmac4356-pcie.bin
   ```

1. Replace the original firmware:
   ```
   sudo cp brcmfmac4356-pcie.bin /lib/firmware/brcm/
   ```

1. Copy the sidecar text file into the same location:
   ```
   sudo cp brcmfmac4356-pcie.txt /lib/firmware/brcm/
   ```

1. Load the new kernel module:
   The built-in `brcmfmac` kernel module will load the stock firmware, whereas our modified kernel will load our custom firmware. You can load the custom module temporarily, in which case the original will be loaded on reboot, or install it permanently so your installation will always be Wii U-compatible. The custom module/firmware should still remain compatible with standard Wi-Fi connections, however there's a chance you will experience degraded network performance due to the lack of Switch-specific patches in our custom firmware.
   
   - Load custom kernel module temporarily:
     ```
     sudo rmmod brcmfmac
     sudo insmod brcmfmac.ko
     ```
   - Install and load custom kernel module permanently:
     ```
     sudo rmmod brcmfmac
     sudo cp brcmfmac.ko /lib/modules/$(uname -r)/kernel/drivers/net/wireless/broadcom/brcm80211/brcmfmac/
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
   apt install git libgmp3-dev gawk qpdf bison flex make autoconf libtool texinfo
   ```

   - On 32-bit systems:
     ```
     TODO
     ```
   - On 64-bit systems:
     ```
     dpkg --add-architecture armhf
     apt-get update
     apt-get install libc6:armhf libisl23:armhf libmpfr6:armhf libmpc3:armhf libstdc++6:armhf
     ln -s /usr/lib/arm-linux-gnueabihf/libisl.so.23 /usr/lib/arm-linux-gnueabihf/libisl.so.10
     ln -s /usr/lib/arm-linux-gnueabihf/libmpfr.so.6 /usr/lib/arm-linux-gnueabihf/libmpfr.so.4
     ```

1. Fix build scripts:

   Firstly, upgrade the system to ensure the L4T kernel headers are installed and up-to-date:

   ```
   apt upgrade
   ```

   Next, inexplicably, some of the build scripts have been compiled for x86 (probably to facilitate cross-compilation) and need to be recompiled to run on aarch64:

   ```
   cd /usr/src/linux-headers-$(uname -r)/scripts/basic
   make -B fixdep
   cd ../mod
   make modpost.o
   make file2alias.o
   make sumversion.o
   gcc modpost.o file2alias.o sumversion.o -o modpost
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

1. Compile and install the new firmware, and load the custom kernel module:

   ```
   make install-firmware
   ```

**NOTE:** This will permanently replace the custom firmware but only temporarily load the custom kernel module. Upon next boot, the original kernel module will be loaded and refuse to load the modified firmware. To remedy this, you should either restore the backup firmware made in step 7 or load/install the custom kernel module again (see Usage section for more details).

## For more information

This is merely a fork of Nexmon that adds patches for the Wii U. For more information about Nexmon, please [check the upstream repository](https://github.com/seemoo-lab/nexmon).
