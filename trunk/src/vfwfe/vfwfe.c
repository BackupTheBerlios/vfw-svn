#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "sha1.h"
#include "vfwfe.h"

void vfwfe_mode_set(unsigned int mode_num);
struct conn_info * vfwfe_conn_get(void);
void vfwfe_path_get(pid_t pid, unsigned char *path);
void vfwfe_checksum_calc(struct conn_info *conn);
void vfwfe_checksum_print(const unsigned char *pcsum, unsigned char *result);
void new_connection(void);

int fd;

void vfwfe_mode_set(unsigned int mode_num)
{
	unsigned int mode;
	int err;

	mode = mode_num;
	err = ioctl(fd, VFWMON_IOC_SETMODE, &mode);
	if (err)
		fprintf(stderr, "cannot set mode\n");
}

struct conn_info * vfwfe_conn_get(void)
{
	struct conn_info *conn;

	conn = (struct conn_info *)malloc(sizeof(struct conn_info));
	if (!conn)
		return NULL;
	memset(conn, 0, (sizeof conn_info));

	err = ioctl(fd, VFWMON_IOC_GET, conn);
	if (err) {
		fprintf(stderr, "cannot get connection\n");
		free(conn);
		return NULL;
	}

	return conn;
}

void vfwfe_path_get(pid_t pid, unsigned char *path)
{
	unsigned char proc_path[PATH_MAX];

	fprintf(proc_path, "/proc/%d/exe", pid);
	realpath(proc_path, path);
}

void vfwfe_checksum_calc(unsigned char *pcsum, const unsigned char *path)
{
	FILE *stream;

	stream = fopen(path, "r");
	if (!stream) {
		fprintf(stderr, "cannot open program file\n");
		return;
	}
	sha1_stream(stream, pcsum);
}

void vfwfe_checksum_print(const unsigned char *pcsum, unsigned char *result)
{
	unsigned char tmp[3];
	int i;

	*result = '\0';
	for (i = 0; i < SHA1_DIGEST_SIZE; i++) {
		snprintf(tmp, sizeof(tmp), "%02x", pcsum + i);
		strncat(result, tmp, sizeof(tmp));
	}
}

void new_connection(void)
{
	GtkWidget *vfwfe_alert_out;
	GtkWidget *vfwfe_entry_pid;
	GtkWidget *vfwfe_entry_path;
	GtkWidget *vfwfe_entry_checksum;
	GtkWidget *vfwfe_entry_dest_ip;
	GtkWidget *vfwfe_entry_dest_port;

	struct conn_info *conn;
	unsigned char pid[10];
	unsigned char path[PATH_MAX]; 
	unsigned char checksum[50];
	unsigned char daddr[20];
	unsigned char dest[10];
	struct in_addr tmp;

	conn = vfwfe_conn_get();
	if (!conn)
		return;

	memset(pid, 0, sizeof(pid));
	memset(path, 0, PATH_MAX);
	memset(checksum, 0, sizeof(checksum));
	memset(daddr, 0, sizeof(daddr));
	memset(dest, 0, sizeof(dest));

	snprintf(pid, sizeof(pid), "%d", conn->pid);

	vfwfe_path_get(conn->pid, path);

	vfwfe_checksum_calc(conn->pcsum, path);
	vfwfe_checksum_print(conn->pcsum, checksum);

	tmp.s_addr = conn->daddr;
	snprintf(daddr, sizeof(daddr), "%s", inet_addr(tmp));
	snprintf(dest, sizeof(dest), "%d", ntohs(conn->dest));

	vfwfe_alert_out = create_vfwfe_alert_out();

	vfwfe_entry_pid = lookup_widget(GTK_WIDGET(vfwfe_alert_out), "vfwfe_entry_pid");
	vfwfe_entry_path = lookup_widget(GTK_WIDGET(vfwfe_alert_out), "vfwfe_entry_path");
	vfwfe_entry_checksum = lookup_widget(GTK_WIDGET(vfwfe_alert_out), "vfwfe_entry_checksum");
	vfwfe_entry_dest_ip = lookup_widget(GTK_WIDGET(vfwfe_alert_out), "vfwfe_entry_dest_ip");
	vfwfe_entry_dest_port = lookup_widget(GTK_WIDGET(vfwfe_alert_out), "vfwfe_entry_dest_port");

	gtk_entry_set_text(GTK_ENTRY(vfwfe_entry_pid), pid);
	gtk_entry_set_text(GTK_ENTRY(vfwfe_entry_path), path);
	gtk_entry_set_text(GTK_ENTRY(vfwfe_entry_checksum), checksum);
	gtk_entry_set_text(GTK_ENTRY(vfwfe_entry_dest_ip), daddr);
	gtk_entry_set_text(GTK_ENTRY(vfwfe_entry_dest_port), dest);
}

int main(void)
{
	unsigned int mode;
	struct sigaction vfwfe_sigaction;

	memset(&vfwfe_sigaction, 0, sizeof(struct sigaction));
	vfwfe_sigaction.sa_handler = new_connection;
	vfwfe_sigaction.sa_flags = 0;
	sigaction(SIGIO, &vfwfe_sigaction, NULL);

	fd = open("/dev/vfwmon", O_RDONLY);
	fcntl(fd, F_SETOWN, getpid());
	fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | FASYNC);
}

