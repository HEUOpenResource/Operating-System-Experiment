#include <asm/segment.h>
#include <linux/sched.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>

#define SIZE 1024        // 缓冲区大小
#define BUFFER_SIZE 1024
char psbuffer[SIZE];    // 定义缓冲区来存放结点信息

// sprintf 和 vsprintf 的实现
static int vsprintf(char *buf, const char *fmt, va_list args) {
    char *p;
    int len = 0;

    for (p = (char *)fmt; *p != '\0'; p++) {
        if (*p != '%') {
            if (len < BUFFER_SIZE - 1) {
                buf[len++] = *p;
            }
            continue;
        }
        p++; // Skip '%'
        switch (*p) {
            case 'd': { // Integer
                int num = va_arg(args, int);
                char tmp[12]; // Sufficient for 32-bit int
                int i = 0;
                if (num < 0) {
                    buf[len++] = '-';
                    num = -num;
                }
                do {
                    tmp[i++] = (num % 10) + '0';
                    num /= 10;
                } while (num && i < sizeof(tmp));
                while (i > 0) {
                    buf[len++] = tmp[--i];
                }
                break;
            }
            case 's': { // String
                char *str = va_arg(args, char *);
                while (*str && len < BUFFER_SIZE - 1) {
                    buf[len++] = *str++;
                }
                break;
            }
            default:
                buf[len++] = *p;
                break;
        }
    }
    buf[len] = '\0'; // Null-terminate the buffer
    return len;
}

int sprintf(char *buf, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int len = vsprintf(buf, fmt, args);
    va_end(args);
    return len;
}

/* 读取系统中的信息放到 psbuffer 数组中, 并再读取 psbuffer 中的数据写入到用户空间的 buf 中 */
int psread(int dev, char *buf, int count, off_t *f_pos) {
    struct task_struct *p;
    int i, j = 0;    // 变量 j 为在 psbuffer 中写数据的位置偏移量

    // 如果是第一次读取，将 psbuffer 进行初始化和赋值
    if (!(*f_pos)) {
        memset(psbuffer, 0, SIZE);    // 将 psbuffer 数组初始化为 0

        // 使用 sprintf 添加标题
        sprintf(psbuffer, "pid\tstate\tfather\tcounter\tstart_time\n");
        j = strlen(psbuffer);    // 更新偏移量

        // 遍历当前的进程，为 psinfo 节点赋值
        for (i = 0; i < NR_TASKS; i++) {
            p = task[i];
            if (p == NULL) continue;

            // 使用 sprintf 进行数据拼接
            j += sprintf(psbuffer + j, "%d\t%d\t%d\t%d\t%d\n",
                         p->pid, p->state, p->father, p->counter, p->start_time);
        }
    }

    // 将数组 psbuffer 中的信息读取到用户空间的 buf 位置处
    for (i = 0; i < count; i++, (*f_pos)++) {
        if (psbuffer[*f_pos] == '\0')
            break;
        // put_fs_byte 函数是将一字节存放在 fs 段中指定内存地址处
        put_fs_byte(psbuffer[*f_pos], &buf[i]);
    }

    return i;
}
