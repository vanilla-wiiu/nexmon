/***************************************************************************
 *                                                                         *
 *          ###########   ###########   ##########    ##########           *
 *         ############  ############  ############  ############          *
 *         ##            ##            ##   ##   ##  ##        ##          *
 *         ##            ##            ##   ##   ##  ##        ##          *
 *         ###########   ####  ######  ##   ##   ##  ##    ######          *
 *          ###########  ####  #       ##   ##   ##  ##    #    #          *
 *                   ##  ##    ######  ##   ##   ##  ##    #    #          *
 *                   ##  ##    #       ##   ##   ##  ##    #    #          *
 *         ############  ##### ######  ##   ##   ##  ##### ######          *
 *         ###########    ###########  ##   ##   ##   ##########           *
 *                                                                         *
 *            S E C U R E   M O B I L E   N E T W O R K I N G              *
 *                                                                         *
 * This file is part of NexMon.                                            *
 *                                                                         *
 * Copyright (c) 2024 NexMon Team                                          *
 *                                                                         *
 * NexMon is free software: you can redistribute it and/or modify          *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * NexMon is distributed in the hope that it will be useful,               *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with NexMon. If not, see <http://www.gnu.org/licenses/>.          *
 *                                                                         *
 **************************************************************************/

#pragma NEXMON targetregion "patch"

#include <firmware_version.h>
#include <patcher.h>

char version[] = "7.45.234 (4ca95bb CY nexmon.org: " GIT_VERSION "-" BUILD_NUMBER ")";
char date[] = __DATE__;
char time[] = __TIME__;

__attribute__((at(VERSION_PTR_1, "", CHIP_VER_BCM43455c0, FW_VER_7_45_234_4ca95bb_CY)))
GenericPatch4(version_patch_1, version);
__attribute__((at(VERSION_PTR_2, "", CHIP_VER_BCM43455c0, FW_VER_7_45_234_4ca95bb_CY)))
GenericPatch4(version_patch_2, version);
__attribute__((at(VERSION_PTR_3, "", CHIP_VER_BCM43455c0, FW_VER_7_45_234_4ca95bb_CY)))
GenericPatch4(version_patch_3, version);
__attribute__((at(VERSION_PTR_4, "", CHIP_VER_BCM43455c0, FW_VER_7_45_234_4ca95bb_CY)))
GenericPatch4(version_patch_4, version);

__attribute__((at(DATE_PTR, "", CHIP_VER_BCM43455c0, FW_VER_7_45_234_4ca95bb_CY)))
GenericPatch4(date_patch, date);

__attribute__((at(TIME_PTR, "", CHIP_VER_BCM43455c0, FW_VER_7_45_234_4ca95bb_CY)))
GenericPatch4(time_patch, time);
