#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
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

void vfwfe_checksum_calc(struct conn_info *conn, const unsigned char *path)
{
	FILE *stream;

	stream = fopen(path, "r");
	if (!stream) {
		fprintf(stderr, "cannot open program file\n");
		return;
	}
	sha1_stream(stream, conn->pcsum);
}

void vfwfe_checksum_print(const unsigned char *pcsum, unsigned char *result)
{
	unsigned char tmp[3];
	int i;

	*result = '\0';
	for (i = 0; i < SHA1_DIGEST_SIZE; i++) {
		fprintf(tmp, "%02x", pcsum + i);
		strncat(result, tmp, 3);
	}
}

void new_connection(void)
{
	struct conn_info *conn;
	unsigned char path[PATH_MAX]; 
	unsigned char checksum[50];

	conn = vfwfe_conn_get();
	if (!conn)
		return;

	memset(path, 0, PATH_MAX);
	vfwfe_path_get(conn->pid, path);

	memset(checksum, 0, 50);
	vfwfe_checksum_calc(conn, checksum);
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

