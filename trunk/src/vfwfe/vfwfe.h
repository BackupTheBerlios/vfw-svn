/*
 * Visual Firewall Monitor
 * Copyright (C) 2006 Nguyen Minh Nhat <ngmnhat@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */ 

#define SHA1_DIGEST_SIZE 20

struct conn_info {
	pid_t pid;
	unsigned char pcsum[SHA1_DIGEST_SIZE];
	unsigned int daddr;
	unsigned short dest;
	unsigned int action;
	unsigned long timeout;
};

enum {
	MODE_MONITOR = 0,
	MODE_NOTIFIER,
	MODE_LOGGER,
	MODE_MONITOR_ON,
	MODE_MONITOR_OFF,
	MODE_NOTIFIER_ON,
	MODE_NOTIFIER_OFF,
	MODE_LOGGER_ON,
	MODE_LOGGER_OFF,
	MODE_RESET
};

extern int fd;

void vfwfe_mode_set(unsigned int mode_num);
struct conn_info * vfwfe_conn_get(void);
void vfwfe_path_get(pid_t pid, unsigned char *path);
void vfwfe_checksum_calc(unsigned char *pcsum, const unsigned char *path);
void vfwfe_checksum_print(const unsigned char *pcsum, unsigned char *result);
void new_connection(void);

#define VFWMON_IOC_MAGIC 0x44
#define VFWMON_IOC_GETMODE _IOR(VFWMON_IOC_MAGIC, 0, unsigned int)
#define VFWMON_IOC_SETMODE _IOW(VFWMON_IOC_MAGIC, 1, unsigned int)
#define VFWMON_IOC_GET _IOR(VFWMON_IOC_MAGIC, 2, struct conn_info)
#define VFWMON_IOC_SUBMIT _IOW(VFWMON_IOC_MAGIC, 3, struct conn_info)
#define VFWMON_IOC_SUBMIT_SAVE _IOW(VFWMON_IOC_MAGIC, 4, struct conn_info)
#define VFWMON_IOC_ADD _IOW(VFWMON_IOC_MAGIC, 5, struct conn_info)
#define VFWMON_IOC_DELETE _IOW(VFWMON_IOC_MAGIC, 6, struct conn_info)
#define VFWMON_IOC_MAXNR 8

