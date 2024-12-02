# 一、目录

- [一、目录](#一目录)
- [二、前言](#二前言)
- [三、主要文件](#三主要文件)
- [四、任务目录](#四任务目录)
- [五、任务对应添加或者修改的文件](#五任务对应添加或者修改的文件)
- [六、StarHistory](#六starhistory)

# 二、前言

该仓库为**哈尔滨工程大学**计算机科学与技术学院2024~2025学年秋季课程——**操作系统**配套实验代码，配套平台为北京杰创永恒科技有限公司旗下的[云端课程体系建设平台](http://www.bj-jc.com.cn/)。该项目作者[only9464](https://github.com/only9464)精力和能力都有限，只整理对应的任务所要修改的文件及其对应的行数的代码，同时上传了实验教程、实验报告模板以及各个实验的要求，各位同志可以作为参考来完成自己的实验操作。若有谬误，请多多指教，欢迎提交issue或者发送邮件至**sky9464@qq.com**以[联系作者](mailto:sky9464@qq.com)。仅供参考，请勿抄袭()。

**注意：README.md中修改或者添加的代码均为最后提交的版本，中间版本暂时不予提供**

**问题反馈：README.md中的代码总结可能不完善或者存在谬误，若你在参考的过程中坐牢了，可以看一下仓库中对应的文件的源代码，欢迎纠错与补充！**

- 感谢 [@MadLongTom](https://github.com/MadLongTom) 对 **实验8地址映射和内存共享-任务1 --> kernel/system_call.s** 的纠错（[#1](https://github.com/only9464/Operating-System-Experiment/pull/1)）
- 感谢 [@Erwwyh](https://github.com/Erwwyh)     对  **实验8地址映射和内存共享-任务1 --> include/linux/sys.h** 的补充（[#2](https://github.com/only9464/Operating-System-Experiment/issues/2)）
- 感谢 [@Erwwyh](https://github.com/Erwwyh)     对  **实验8地址映射和内存共享-任务2 --> newapp/loop.c** 的纠错（[#3](https://github.com/only9464/Operating-System-Experiment/issues/3)）

# 三、主要文件
 - [README.md](./README.md): 包含本仓库说明、最终修改的文件代码位置等
 - [Linux内核实验教程_4.10.pdf](./Linux内核实验教程_4.10.pdf): 实验教程
 - [学生包.zip](./学生包.zip): 部分实验所需要的写好的库文件 **ps:[点击下载](https://share.weiyun.com/25rA49QB)**
 - `实验软件安装包` : [点击下载](https://share.weiyun.com/4acfD58r)
 - `实验文档` : [点击下载](https://share.weiyun.com/Thn0GykT)
 - `Linux操作系统实验介绍.mp4` : [点击下载](https://share.weiyun.com/zZraA1Pl)
# 四、任务目录

- [1. 实验1实验环境的使用-任务1](#1-实验1实验环境的使用-任务1)
- [2. 实验1实验环境的使用-任务2](#2-实验1实验环境的使用-任务2)
- [3. 实验2操作系统的启动](#3-实验2操作系统的启动)
- [4. 实验5进程的创建-任务1](#4-实验5进程的创建-任务1)
- [5. 实验5进程的创建-任务2](#5-实验5进程的创建-任务2)
- [6. 实验8地址映射和内存共享-任务1](#6-实验8地址映射和内存共享-任务1)
- [7. 实验8地址映射和内存共享-任务2](#7-实验8地址映射和内存共享-任务2)
- [8. 实验11proc文件系统的实现](#8-实验11proc文件系统的实现)

# 五、任务对应添加或者修改的文件

## 1. 实验1实验环境的使用-任务1

### ①修改文件：init/main.c

第234行添加：

```C
    printf("Hello Linux!\n\r");
```

## 2. 实验1实验环境的使用-任务2

### ①修改文件：linuxapp.c

第10行添加：

```C
    /* 新增代码,输出内容任意即可 */
	printf("Github: https://github.com/only9464\n");
```

### ②新增文件：newapp/add.c

```C
int add(int x,int y){
return x+y;
}
```

### ③新增文件：newapp/main.c

```C
#include<stdio.h>
int add(int x,int y);
int main(){
int a;
int b;
int sum;
printf("Please input two number:\n");
scanf("%d %d",&a,&b);
sum=add(a,b);
printf("The result is:%d\n",sum);
return 0;
}
```

### ④新增文件：newapp/add.h

```makefile
CC = gcc
CFLAGS = -Wall -g
SRC = add.c main.c
OBJ = $(SRC:.c=.o)
TARGET = app
all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)
.PHONY: all clean
```
 
## 3. 实验2操作系统的启动

### ①修改文件：boot/setup.asm

第116行之前添加：

```assembly
    mov ax, cs            ; 将当前代码段加载到AX
    mov ds, ax            ; 设置DS为AX值，以确保数据段正确
    mov si, message       ; SI指向字符串开始位置
    mov ah, 0x0e          ; 设置BIOS teletype功能
print_message:
    lodsb                 ; 将[SI]中的字符加载到AL，并自动递增SI
    cmp al, 0             ; 检查AL是否为0（字符串结束符）
    je done_message       ; 如果为0，跳转到done_message
    int 0x10              ; 显示字符
    jmp print_message     ; 循环回去显示下一个字符

done_message:
    ; 恢复寄存器和控制流
    ; mov ds, INITSEG     ; 如果需要，恢复ds等寄存器
    jmp next_step         ; 显式跳转到下一步（例如进入保护模式的代码）

message db 'Enter protected mode ...', 0 ; 以0结束的字符串

next_step:
```

### ②修改文件：kernel/blk_drv/hd.c

第203行改为：

```C
	printk("\n\n\nPartition table%s ok.\n\r",(NR_HD>1)?"s":"");
```
 
## 4. 实验5进程的创建-任务1

### ①新增文件：main.c

```C
#define _LIBRARY_
#include <stdio.h>
#include <unistd.h>
int main(){
 int pid;
 printf("PID:%D parent process start.\n",getpid());
 pid = fork();
 if(pid != 0 )
 {
  wait(NULL);
  printf("PID:%d parent process continue.\n",getpid());
 }
 else
 {
  printf("PID:%d child process  start.\n",getpid());
  printf("PID:%d child process exit.\n",getpid());
  return 0;
 }
 printf("PID:%d parent process exit.\n",getpid());
 return 0;
}
```
 
## 5. 实验5进程的创建-任务2

### ①新增文件：new.c

```C
#define __LIBRARY__ 
#include <stdio.h> 
#include <unistd.h> 
int main( int argc, char * argv[] ) 
{ 
printf("PID:%d new process.\n", getpid()); 
return 0; 
} 
```

### ②新增文件：old.c

```C
#define __LIBRARY__ 
#include <stdio.h> 
#include <unistd.h> 
int main( int argc, char * argv[] ) 
{ 
printf("PID:%d old process start.\n", getpid()); 
execve("new", NULL, NULL ); 
printf("PID:%d old process exit.\n", getpid()); 
return 0; 
} 
```
 
## 6. 实验8地址映射和内存共享-任务1

### ①修改文件：include/linux/kernel.h

第22行添加：

```C
int physical_mem();
```

### ②修改文件：/include/linux/sys.h

第87行后添加：

```C
extern int dump_physical_mem();
```

第177行(sys_uselib所在行)改为：

```C
sys_uselib,			//86 
dump_physical_mem  //87
```

### ③修改文件：include/unistd.h

第162行添加：

```C
#define __NR_dump_physical_mem 87
```

### ④修改文件：kernel/sys.c

第353行添加：

```C
int dump_physical_mem(){
  physical_mem();
  return 0;
}

```

### ⑤修改文件：kernel/system_call.s

第73行改为：

```assembly
nr_system_calls = 88	# Linux 0.11 版内核中的系统调用总数。
```

### ⑥修改文件：mm/memory.c

第817行添加：

```C
int physical_mem()
{
	int i, free=0;	/* free表示空闲页的总数 */

	__asm("cli");

	/* PAGING_PAGES 是在本文件第 137 行处定义，表示分页后的物理内存页数。*/
	/* mem_map[] 是在第 152 行定义的内存映射字节图(1 字节代表 1 页内存)，
		每个页面对应的字节用于标志页面当前被引用（占用）次数。*/
	for(i=0 ; i<PAGING_PAGES ; i++)
	{
		if (0 == mem_map[i])
		{
			free++;
		}
	}

	printk("Page Count : %d\n", PAGING_PAGES);
	printk("Memory Count : %d * 4096 = %d Byte\n\n", PAGING_PAGES, PAGING_PAGES * 4096);

	printk("Free Page Count : %d\n", free);
	printk("Used Page Count : %d\n", PAGING_PAGES - free);

    // 分配一个空闲物理页
    int allocated_page = get_free_page();
    if (allocated_page != -1) {
        // 计算分配的物理页地址
        void *allocated_address = (void *)(allocated_page * 4096);
        printk("**********After Allocated One Page**********\n");
        printk("Allocated One Page : %p\n", allocated_address);

        // 更新空闲页的数量
        free--; // 分配后空闲页数减少
        printk("Free Page Count : %d\n", free);
        printk("Used Page Count : %d\n", PAGING_PAGES - free);
    } else {
        printk("Failed to allocate a page\n");
    }

    // 回收刚刚分配的物理页
    if (allocated_page != -1) {
        free_page(allocated_page);
        printk("**********After Freed One Page**********\n");
        // 计算释放的物理页地址
        void *freed_address = (void *)(allocated_page * 4096);
        free++; // 回收后空闲页数增加
        printk("Freed One Page : %p\n", freed_address);
        printk("Free Page Count : %d\n", free);
        printk("Used Page Count  : %d\n", PAGING_PAGES - free);
    }

	__asm("sti");

	return 0;
}
```

### ⑦新增文件： newapp/main.c

```C
#define __LIBRARY__ 
#include <unistd.h> 
#define __NR_dump_physical_mem 87 
_syscall0(int, dump_physical_mem) 
int main() 
{ 
dump_physical_mem(); 
return 0; 
} 

```
 
## 7. 实验8地址映射和内存共享-任务2

### ①新增文件：newapp/loop.c

```C
#include <stdio.h>
int i = 0x12345678;
int main(void)
{
printf("The logical/virtual address of i is 0x%08x\n", &i);
fflush(stdout);
while(i)
;
return 0;
}
```
 
## 8. 实验11proc文件系统的实现

### ①修改文件：fs/namei.c

第647行改为：

```C
	if (S_ISBLK(mode) || S_ISCHR(mode) || S_ISPROC(mode))
```

### ②新增文件：fs/procfs.c

```C
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
```

### ③修改文件：fs/read_write.c

第32行添加：

```C
// psread函数. fs/proc.c
extern int psread (int dev, char * buf, int count, off_t * f_pos); 
```

第113行(printk调用)前添加：

```C
	if(S_ISPROC(inode->i_mode)) 
		return psread(inode->i_zone[0], buf, count, &file->f_pos); 
```

### ④修改文件：include/sys/stat.h

第26行添加：

```C
#define S_IFPROC 0050000 	// 新文件类型宏定义
```

第38行添加:

```C
#define S_ISPROC(m) (((m)& S_IFMT) == S_IFPROC) // 为新文件类型添加相应的测试宏
```

### ⑤修改文件：init/main.c

第13行添加：

```C
#include<sys/stat.h> 
```

第43行添加：

```C
_syscall2(int,mkdir,const char*,name,mode_t,mode) 
_syscall3(int,mknod,const char*,filename,mode_t,mode,dev_t,dev) 
```

第235行添加：

```C
	mkdir("/proc",0755); 
	mknod("/proc/psinfo",S_IFPROC|0444,0); 
```
 
# 六、StarHistory
[![Star History Chart](https://api.star-history.com/svg?repos=only9464/Operating-System-Experiment&type=Date)](https://star-history.com/#only9464/Operating-System-Experiment&Date)
