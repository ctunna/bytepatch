#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/mmu_context.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/pid.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int pid = 1;
static int val = 0;
static unsigned long addr;

module_param(pid, int, 0);
module_param(val, int, 0);
module_param(addr, ulong, 0);

static int __init start(void){
  int (*access_process_vm)(struct task_struct*, unsigned long, void*, int, int);
  int num[1];
  unsigned long access_process_addr = 0xc0504570;

  struct task_struct *ts;
  ts = pid_task(find_vpid((pid_t)pid), PIDTYPE_PID);
  num[0] = val;

  printk(KERN_INFO "Loading bytepatch..\n");
  printk(KERN_INFO "Target PID: %d\n", pid);
  printk(KERN_INFO "Target addr: %lx\n", addr);

  down_read(&(ts->mm->mmap_sem));
  access_process_vm = (void*)access_process_addr;
  access_process_vm(ts, addr, &num[0], sizeof(int), 1);
  up_read(&(ts->mm->mmap_sem));

  return 0;
}

static void __exit end(void){
  printk(KERN_INFO "Goodbye world. \n");
}

module_init(start);
module_exit(end);

