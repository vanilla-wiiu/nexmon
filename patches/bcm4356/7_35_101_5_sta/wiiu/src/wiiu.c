#pragma NEXMON targetregion "patch"

#include <local_wrapper.h>
#include <patcher.h>
#include <wrapper.h>

__attribute__((at(0x1b3c10, "", CHIP_VER_BCM4356, FW_VER_7_35_101_5_sta)))
GenericPatch4(remove_bad_check, 0xbf00bf00)
