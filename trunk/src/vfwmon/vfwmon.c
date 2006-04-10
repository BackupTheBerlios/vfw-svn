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

/*
 * struct module
 * THIS_MODULE
 * MODULE_DESCRIPTION()
 * MODULE_LICENSE()
 * MODULE_AUTHOR()
 */
#include <linux/module.h>

/*
 * module_init()
 * module_exit()
 * __init
 * __initdata
 * __exit
 * __exitdata
 */
#include <linux/init.h>

/*
 * pid_t
 * dev_t
 */
#include <linux/types.h>

/*
 * printk()
 * container_of()
 * KERN_ALERT
 */
#include <linux/kernel.h>

/*
 * set_bit()
 * clear_bit()
 */
#include <asm/bitops.h>

/*
 * access_ok()
 * copy_from_user()
 * copy_to_user()
 * VERIFY_READ
 * VERIFY_WRITE
 */
#include <asm/uaccess.h>

/*
 * POLL_IN
 */
#include <asm-generic/siginfo.h>

/*
 * SIGIO
 */
#include <asm/signal.h>

/*
 * HZ
 */
#include <asm/param.h>

/*
 * jiffies
 * time_after_eq()
 */
#include <linux/jiffies.h>

/*
 * struct task_struct
 * struct task_struct current
 */
#include <linux/sched.h>

/*
 * kmalloc()
 * kfree()
 */
#include <linux/slab.h>

/*
 * spinlock_t
 */
#include <linux/spinlock_types.h>

/*
 * spin_lock_init()
 * spin_lock()
 * spin_unlock()
 */
#include <linux/spinlock.h>

/*
 * struct workqueue_struct
 * struct work_struct
 * create_singlethread_workqueue()
 * queue_delayed_work()
 * cancel_delayed_work()
 * flush_workqueue()
 * destroy_workqueue()
 * INIT_WORK()
 */
#include <linux/workqueue.h>

/*
 * _IO()
 * _IOR()
 * _IOW()
 * _IOC_DIR()
 * _IOC_TYPE()
 * _IOC_NR()
 * _IOC_SIZE()
 * _IOC_READ
 * _IOC_WRITE
 */
#include <asm/ioctl.h>

/*
 * MAJOR()
 * MINOR()
 * MKDEV()
 */
#include <linux/kdev_t.h>

/*
 * fasync_struct
 * struct inode
 * struct file
 * struct file_operations
 * fasync_helper()
 * kill_fasync()
 * alloc_chrdev_region()
 * unregister_chrdev_region()
 */
#include <linux/fs.h>

/*
 * struct cdev
 * cdev_init()
 * cdev_add()
 * cdev_del()
 */
#include <linux/cdev.h>

/*
 * PF_INET
 */
#include <linux/socket.h>

/*
 * struct sk_buff
 */
#include <linux/skbuff.h>

/*
 * IPPROTO_TCP
 */
#include <linux/in.h>

/*
 * struct iphdr
 */
#include <linux/ip.h>

/*
 * struct tcphdr
 */
#include <linux/tcp.h>

/*
 * struct nf_hook_ops
 * nf_register_hook()
 * nf_unregister_hook()
 * NF_DROP
 * NF_ACCEPT
 */
#include <linux/netfilter.h>

/*
 * NF_IP_LOCAL_OUT
 * NF_IP_PRI_FIRST
 */
#include <linux/netfilter_ipv4.h>

/*
 * memset()
 */
#include <linux/string.h>

/*
 * struct list_head
 * list_for_each_entry()
 * list_for_each_entry_safe()
 * list_add_tail()
 * list_del()
 * INIT_LIST_HEAD()
 */
#include <linux/list.h>

#include "vfwmon.h"

struct file_operations vfwmon_fops = {
	.owner = THIS_MODULE,
	.ioctl = vfwmon_ioctl,
	.open = vfwmon_open,
	.release = vfwmon_release,
	.fasync = vfwmon_fasync,
};

struct nf_hook_ops vfwmon_hook_ops = {
	.hook = vfwmon_hook_func,
	.pf = PF_INET,
	.hooknum = NF_IP_LOCAL_OUT,
	.priority = NF_IP_PRI_FIRST,
};

int vfwmon_major = 0;
int vfwmon_minor = 0;
int ok = 0;
int print_debug = 1;

struct vfwmon_dev *vfwmon_device;

int vfwmon_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct vfwmon_dev *dev = filp->private_data;
	struct vfwmon_rule *rule, *tmprule;
	struct conn_info tmpconn;
	unsigned int tmp;
	int err = 0;

	if (_IOC_TYPE(cmd) != VFWMON_IOC_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(cmd) > VFWMON_IOC_MAXNR)
		return -ENOTTY;

	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
	if (err)
		return -EFAULT;

	switch (cmd) {
		case VFWMON_IOC_GETMODE:
			vfwmon_mode_get(&tmp);
			err = copy_to_user((unsigned int __user *)arg, &tmp,
					   sizeof(unsigned int));
			if (err)
				err = -EFAULT;
			break;

		case VFWMON_IOC_SETMODE:
			err = copy_from_user(&tmp, (unsigned int __user *)arg,
					     sizeof(unsigned int));
			if (err) {
				err = -EFAULT;
				break;
			}
			err = vfwmon_mode_set(tmp);
			break;

		case VFWMON_IOC_GET:
			vfwmon_core_lock();
			list_for_each_entry(rule, &dev->core.pending_list, NODE) {
				if (rule->status == RULE_INIT) {
					err = copy_to_user((struct conn_info __user *)arg,
							   &rule->conn, sizeof(struct conn_info));
					if (err) {
						err = -EFAULT;
						break;
					}
					rule->status = RULE_GOT;
					break;
				}
			}
			vfwmon_core_unlock();
			break;

		case VFWMON_IOC_SUBMIT:
			err = copy_from_user(&tmpconn, (struct conn_info __user *)arg,
					     sizeof(struct conn_info));
			if (err) {
				err = -EFAULT;
				break;
			}
			vfwmon_rule_submit(rule, tmprule,
					   tmpconn.action, RULE_SUBMITTED,
					   rule->conn.timeout == tmpconn.timeout);
			break;

		case VFWMON_IOC_SUBMIT_SAVE:
			err = copy_from_user(&tmpconn, (struct conn_info __user *)arg,
					     sizeof(struct conn_info));
			if (err) {
				err = -EFAULT;
				break;
			}
			vfwmon_rule_submit(rule, tmprule,
					   tmpconn.action, RULE_SUBMITTED_SAVED,
					   rule->conn.timeout == tmpconn.timeout);
			break;

		default:
			err = -ENOTTY;
	}

	return err;
}

int vfwmon_open(struct inode *inode, struct file *filp)
{
	struct vfwmon_dev *dev;
	int inused = 0;

	vfwmon_core_lock();
	inused = vfwmon_device->core.inused;
	vfwmon_core_unlock();
	
	if (inused)
		return -EBUSY;

	vfwmon_core_lock();
	vfwmon_device->core.inused = 1;
	vfwmon_core_unlock();

	dev = container_of(inode->i_cdev, struct vfwmon_dev, cdev);
	filp->private_data = dev;

	return 0;
}

int vfwmon_release(struct inode *inode, struct file *filp)
{
	vfwmon_mode_set(MODE_NOTIFIER_OFF);
	
	vfwmon_core_lock();
	vfwmon_device->core.inused = 0; 
	vfwmon_core_unlock();

	vfwmon_fasync(-1, filp, 0);

	return 0;
}

int vfwmon_fasync(int fd, struct file *filp, int mode)
{
	struct vfwmon_dev *dev = filp->private_data;
	int ret;

	vfwmon_core_lock();
	ret = fasync_helper(fd, filp, mode, &dev->async_queue);
	vfwmon_core_unlock();

	return ret;
}

int conn_match(struct conn_info *conn1, struct conn_info *conn2)
{
	return (conn1->daddr == conn2->daddr &&
		conn1->dest == conn2->dest);
}

int list_rule_add(struct conn_info *conn, struct list_head *head) 
{
	struct vfwmon_rule *rule;

	rule = (struct vfwmon_rule *)kmalloc(sizeof(struct vfwmon_rule), GFP_KERNEL);
	if (!rule) {
		vfwmon_debug("error: cannot allocate rule memory\n");
		return 0;
	}
	memset(rule, 0, sizeof(struct vfwmon_rule));

	rule->conn.pid = conn->pid;
	rule->conn.daddr = conn->daddr;
	rule->conn.dest = conn->dest;
	rule->conn.action = NF_DROP;
	rule->conn.timeout = jiffies + VFWMON_TIMEOUT * HZ;
	rule->status = RULE_INIT;

	vfwmon_core_lock();
	list_add_tail(&rule->NODE, head);
	vfwmon_device->core.pending_count++;
	vfwmon_core_unlock();

	return 1;
}

void list_rule_del(struct vfwmon_rule *rule)
{
	list_del(&rule->NODE);
	kfree(rule);
}

void list_free(struct list_head *head)
{
	struct vfwmon_rule *rule, *tmprule;

	vfwmon_core_lock();
	list_for_each_entry_safe(rule, tmprule, head, NODE)
		list_rule_del(rule);
	vfwmon_core_unlock();
}

void list_free_all(void)
{
	list_free(&vfwmon_pending_list);
	list_free(&vfwmon_rule_list);
}

unsigned int vfwmon_hook_func(unsigned int hooknum,
			      struct sk_buff **skb,
			      const struct net_device *in,
			      const struct net_device *out,
			      int (*okfn)(struct sk_buff *))
{
	struct sk_buff *sb = NULL;
	struct iphdr *iph = NULL;
	struct tcphdr *tcph = NULL;
	unsigned char protocol;
	struct conn_info conn;
	struct vfwmon_rule *rule, *tmprule;
	int ret = NF_ACCEPT, newconn = 0, found = 0, count;

	if (!vfwmon_mode_is_monitoring())
		return ret;

	sb = *skb;
	if (!sb)
		return ret;

	iph = sb->nh.iph;
	if (!iph)
		return ret;

	protocol = iph->protocol;
	switch (protocol) {
		case IPPROTO_TCP:
			tcph = (struct tcphdr *)((unsigned char *)iph + iph->ihl * 4);
			if (tcph->syn &&
			    !tcph->ack &&
			    !tcph->fin &&
			    !tcph->rst &&
			    !tcph->psh)
				newconn = 1;
			break;
		default:
			return ret;
	}

	if (!newconn)
		return ret;

	conn.pid = current->pid;
	conn.daddr = iph->daddr;
	conn.dest = tcph->dest;

	vfwmon_core_lock();
	list_for_each_entry_safe(rule, tmprule, &vfwmon_rule_list, NODE)
		if (conn_match(&rule->conn, &conn)) {
			ret = rule->conn.action;
			found = 1;
			if (rule->status == RULE_SUBMITTED) {
				list_rule_del(rule);
				vfwmon_debug("one-time rule removed from rule_list\n");
			}
			break;
		}
	vfwmon_core_unlock();

	if (!vfwmon_mode_is_notifying())
		return NF_DROP;

	vfwmon_core_lock();
	list_for_each_entry(rule, &vfwmon_pending_list, NODE)
		if (conn_match(&rule->conn, &conn)) {
			ret = rule->conn.action;
			found = 1;
			break;
		}
	vfwmon_core_unlock();

	if (found)
		return ret;

	vfwmon_core_lock();
	count = vfwmon_device->core.pending_count;
	vfwmon_core_unlock();
	if (count >= VFWMON_MAX)
	       return NF_DROP;

	ret = list_rule_add(&conn, &vfwmon_pending_list);
	if (!ret)
		return NF_DROP;
	vfwmon_debug("new rule added to pending_list\n");

	if (vfwmon_device->async_queue)
		kill_fasync(&vfwmon_device->async_queue, SIGIO, POLL_IN);

	return NF_DROP;
}

int vfwmon_mode_bit_test(unsigned int mode)
{
	int ret = 0;

	vfwmon_core_lock();
	ret = test_bit(mode, (unsigned long *)&vfwmon_device->core.mode);
	vfwmon_core_unlock();

	return ret;
}

int vfwmon_mode_bit_map(unsigned int mode)
{
	int mode_bit = 0;

	switch (mode) {
		case MODE_MONITOR_ON:
		case MODE_MONITOR_OFF:
			mode_bit = MODE_MONITOR;
			break;
		case MODE_NOTIFIER_ON:
		case MODE_NOTIFIER_OFF:
			mode_bit = MODE_NOTIFIER;
			break;
		case MODE_LOGGER_ON:
		case MODE_LOGGER_OFF:
			mode_bit = MODE_LOGGER;
			break;
		default:
			mode_bit = sizeof(unsigned int) - 1;
	}

	return mode_bit;
}

void vfwmon_mode_get(unsigned int *mode)
{
	vfwmon_core_lock();
	*mode = vfwmon_device->core.mode;
	vfwmon_core_unlock();
}

int vfwmon_mode_set(unsigned int mode)
{
	int ret = 0, mode_bit = 0;

	mode_bit = vfwmon_mode_bit_map(mode);
	if (vfwmon_mode_bit_test(mode_bit))
		return ret;

	switch (mode) {
		case MODE_MONITOR_ON:
		case MODE_NOTIFIER_ON:
			vfwmon_check_cancel();
			vfwmon_mode_bit_set(mode_bit);
			vfwmon_check_start();
			break;

		case MODE_MONITOR_OFF:
		case MODE_NOTIFIER_OFF:
			vfwmon_check_cancel();
			vfwmon_mode_bit_clear(mode_bit);
			list_free(&vfwmon_pending_list);
			break;

		case MODE_LOGGER_ON:
			vfwmon_mode_bit_set(mode_bit);
			break;

		case MODE_LOGGER_OFF:
			vfwmon_mode_bit_clear(mode_bit);
			break;

		case MODE_RESET:
			vfwmon_check_cancel();
			vfwmon_core_lock();
			vfwmon_device->core.mode = 0;
			vfwmon_device->core.pending_count = 0;
			vfwmon_core_unlock();
			list_free_all();
			break;

		default:
			ret = -ENOTTY;
	}

	return ret;
}

void vfwmon_check(void)
{
	struct vfwmon_rule *rule, *tmprule;

	if ((!vfwmon_mode_is_notifying()) || (!vfwmon_mode_is_monitoring()))
		return;

	vfwmon_core_lock();
	list_for_each_entry_safe(rule, tmprule, &vfwmon_pending_list, NODE)
		if (time_after_eq(jiffies, rule->conn.timeout)) {
			list_rule_del(rule);
			vfwmon_device->core.pending_count--;
			vfwmon_debug("pending rule removed from pending_list\n");
		}
	vfwmon_core_unlock();

	vfwmon_check_start();
}

void vfwmon_check_start(void)
{
	int ret = 0, retry = VFWMON_RETRY;

	while (retry) {
		vfwmon_core_lock();
		ret = queue_delayed_work(vfwmon_device->core.task_list,
					 &vfwmon_device->core.task, VFWMON_DELAY * HZ);
		vfwmon_core_unlock();

		if (ret)
			return;

		vfwmon_debug("error: queue_delayed_work() failed\n");
		retry--;
	}

	vfwmon_mode_set(MODE_NOTIFIER_OFF);
}

void vfwmon_check_cancel(void)
{
	vfwmon_core_lock();
	cancel_delayed_work(&vfwmon_device->core.task);
	flush_workqueue(vfwmon_device->core.task_list);
	vfwmon_core_unlock();
}

int vfwmon_init_core(void)
{
	dev_t devno = 0;
	int ret = 0;

	/* register device number */
	ret = alloc_chrdev_region(&devno, vfwmon_minor, 1, MOD_NAME);
	if (ret < 0) {
		vfwmon_debug("error: alloc_chrdev_region() failed\n");
		ret = -EFAULT;
		goto fail;
	}
	vfwmon_major = MAJOR(devno);
	vfwmon_minor = MINOR(devno);
	ok++;

	/* allocate and initialize device memory */
	vfwmon_device = kmalloc(sizeof(struct vfwmon_dev), GFP_KERNEL);
	if (!vfwmon_device) {
		vfwmon_debug("error: cannot allocate device memory\n");
		ret = -EFAULT;
		goto fail;
	}
	memset(vfwmon_device, 0, sizeof(struct vfwmon_dev));
	ok++;

	/* initialize device access lock */
	vfwmon_device->core.inused = 0;

	/* initialize device spinlock */
	spin_lock_init(&vfwmon_device->core.core_lock);

	/* create workqueue */
	vfwmon_device->core.task_list = create_singlethread_workqueue(MOD_NAME);
	if (!vfwmon_device->core.task_list) {
		vfwmon_debug("error: create_singlethread_workqueue() failed\n");
		ret = -EFAULT;
		goto fail;
	}
	ok++;

	/* initialize work */
	INIT_WORK(&vfwmon_device->core.task, (void *)vfwmon_check, NULL);

	/* initialize rule lists */
	INIT_LIST_HEAD(&vfwmon_pending_list);
	INIT_LIST_HEAD(&vfwmon_rule_list);

	/* initialize and add device */
	cdev_init(&vfwmon_device->cdev, &vfwmon_fops);
	vfwmon_device->cdev.owner = THIS_MODULE;
	vfwmon_device->cdev.ops = &vfwmon_fops;
	ret = cdev_add(&vfwmon_device->cdev, devno, 1);
	if (ret < 0) {
		vfwmon_debug("error: cdev_add() failed\n");
		ret = -EFAULT;
		goto fail;
	}
	ok++;

	/* reset vfwmon mode */
	vfwmon_mode_set(MODE_RESET);

fail:
	return ret;
}

static int vfwmon_init(void)
{
	int ret = 0;

	ret = vfwmon_init_core();
	if (ret < 0)
		goto fail;

	/* register Netfilter hook */
	nf_register_hook(&vfwmon_hook_ops);
	ok++;

	vfwmon_debug("initialized\n");

	return 0;

fail:
	vfwmon_exit();
	return ret;
}

static void vfwmon_exit(void)
{
	dev_t devno;

	vfwmon_mode_set(MODE_RESET);

	switch (ok) {
		case 5:
			nf_unregister_hook(&vfwmon_hook_ops);
		case 4:
			cdev_del(&vfwmon_device->cdev);
		case 3:
			destroy_workqueue(vfwmon_device->core.task_list);
		case 2:
			kfree(vfwmon_device);
		case 1:
			devno = MKDEV(vfwmon_major, vfwmon_minor);
			unregister_chrdev_region(devno, 1);
		default:
			break;
	}

	vfwmon_debug("exited\n");
}

module_init(vfwmon_init);
module_exit(vfwmon_exit);

MODULE_DESCRIPTION("Visual Firewall Monitor");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nguyen Minh Nhat <ngmnhat@gmail.com>");

