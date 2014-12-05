/*
 * Copyright (C) 2014, The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#define LOG_NDEBUG 0

#define LOG_TAG "wcnss_w7"

#include <cutils/log.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int wcnss_init_qmi(void)
{
    /* empty */
    return 0;
}

int wcnss_qmi_get_wlan_address(unsigned char *pBdAddr)
{
	int fd1, fd2, fd3;
	unsigned char macbyte;

	int i;

	fd1 = open("/dev/block/platform/msm_sdcc.1/by-name/misc",O_RDONLY);

	for (i = 0; i < 6; i++) {
		lseek(fd1,0x3000+i,SEEK_SET);
		lseek(fd3,0,SEEK_END);
		read(fd1,&pBdAddr[i],1);
	}
  	ALOGI("Found MAC address: %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx\n",
            pBdAddr[0],
            pBdAddr[1],
            pBdAddr[2],
            pBdAddr[3],
            pBdAddr[4],
            pBdAddr[5]);
	close(fd1);
	return 0;
}

void wcnss_qmi_deinit(void)
{
    /* empty */
}
