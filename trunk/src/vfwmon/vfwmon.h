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

#define MOD_NAME "vfwmon"
#define LOG_LEVEL KERN_ALERT
#define LOG_PREFIX "[" MOD_NAME "] "
#define NODE node
#define VFWMON_DELAY 1
#define VFWMON_TIMEOUT 15
#define VFWMON_RETRY 10
#define VFWMON_MAX 10
#define SHA1_DIGEST_SIZE 20

struct conn_info {
	pid_t pid;
	unsigned char pcsum[SHA1_DIGEST_SIZE];
	unsigned int daddr;
	unsigned short dest;
	unsigned int action;
	unsigned long timeout;
};

struct vfwmon_rule {
	struct conn_info conn;
	unsigned int status;
	struct list_head NODE;
};

struct vfwmon_core {
	unsigned char inused;
	spinlock_t core_lock;
	unsigned int mode;
	struct workqueue_struct *task_list;
	struct work_struct task;
	struct list_head pending_list;
	struct list_head rule_list;
	unsigned int pending_count;
};

struct vfwmon_dev {
	struct cdev cdev;
	struct fasync_struct *async_queue;
	struct vfwmon_core core;
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

enum {
	RULE_INIT = 0,
	RULE_GOT,
	RULE_SUBMITTED,
	RULE_SUBMITTED_SAVED
};

int vfwmon_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg);
int vfwmon_open(struct inode *inode, struct file *filp);
int vfwmon_release(struct inode *inode, struct file *filp);
int vfwmon_fasync(int fd, struct file *filp, int mode);
int conn_match(struct conn_info *conn1, struct conn_info *conn2);
int list_rule_add(struct conn_info *conn, struct list_head *head);
void list_rule_del(struct vfwmon_rule *rule);
void list_free(struct list_head *head);
void list_free_all(void);
unsigned int vfwmon_hook_func(unsigned int hooknum,
			      struct sk_buff **skb,
			      const struct net_device *in,
			      const struct net_device *out,
			      int (*okfn)(struct sk_buff *));
int vfwmon_mode_bit_test(unsigned int mode);
int vfwmon_mode_bit_map(unsigned int mode);
void vfwmon_mode_get(unsigned int *mode);
int vfwmon_mode_set(unsigned int mode);
void vfwmon_check(void);
void vfwmon_check_start(void);
void vfwmon_check_cancel(void);
int vfwmon_init_core(void);
static int vfwmon_init(void);
static void vfwmon_exit(void);

#define VFWMON_IOC_MAGIC 0x44
#define VFWMON_IOC_GETMODE _IOR(VFWMON_IOC_MAGIC, 0, unsigned int)
#define VFWMON_IOC_SETMODE _IOW(VFWMON_IOC_MAGIC, 1, unsigned int)
#define VFWMON_IOC_GET _IOR(VFWMON_IOC_MAGIC, 2, struct conn_info)
#define VFWMON_IOC_SUBMIT _IOW(VFWMON_IOC_MAGIC, 3, struct conn_info)
#define VFWMON_IOC_SUBMIT_SAVE _IOW(VFWMON_IOC_MAGIC, 4, struct conn_info)
#define VFWMON_IOC_ADD _IOW(VFWMON_IOC_MAGIC, 5, struct conn_info)
#define VFWMON_IOC_DELETE _IOW(VFWMON_IOC_MAGIC, 6, struct conn_info)
#define VFWMON_IOC_MAXNR 8

#define vfwmon_pending_list (vfwmon_device->core.pending_list)
#define vfwmon_rule_list (vfwmon_device->core.rule_list)

#define vfwmon_debug(...) \
	do { \
		if (print_debug) \
			printk(LOG_LEVEL LOG_PREFIX __VA_ARGS__); \
	} while (0)

#define vfwmon_core_lock() spin_lock(&vfwmon_device->core.core_lock)
#define vfwmon_core_unlock() spin_unlock(&vfwmon_device->core.core_lock)

#define vfwmon_mode_bit_set(nr) \
	do { \
		vfwmon_core_lock(); \
		set_bit((nr), (unsigned long *)&vfwmon_device->core.mode); \
		vfwmon_core_unlock(); \
	} while (0)
#define vfwmon_mode_bit_clear(nr) \
	do { \
		vfwmon_core_lock(); \
		clear_bit((nr), (unsigned long *)&vfwmon_device->core.mode); \
		vfwmon_core_unlock(); \
	} while (0)
#define vfwmon_mode_is_monitoring() vfwmon_mode_bit_test(MODE_MONITOR)
#define vfwmon_mode_is_notifying() vfwmon_mode_bit_test(MODE_NOTIFIER)
#define vfwmon_mode_is_logging() vfwmon_mode_bit_test(MODE_LOGGER)

#define vfwmon_rule_submit(r, t, a, s, c) \
	do { \
		vfwmon_core_lock(); \
		list_for_each_entry_safe((r), (t), &vfwmon_pending_list, NODE) { \
			if ((c)) { \
				list_del(&(r)->NODE); \
				list_add_tail(&(r)->NODE, &vfwmon_rule_list); \
				(r)->conn.action = (a); \
				(r)->status = (s); \
				vfwmon_device->core.pending_count--; \
				vfwmon_debug("action submitted. rule removed from pending_list, added to rule_list\n"); \
				break; \
			} \
		} \
		vfwmon_core_unlock(); \
	} while (0)

