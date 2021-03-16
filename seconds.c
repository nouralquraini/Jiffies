
/**
 * hello.c
 *
 * Kernel module that communicates with /proc file system.
 * 
 * The makefile must be modified to compile this program.
 * Change the line "simple.o" to "hello.o"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018

 */


#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <linux/jiffies.h>
#include <linux/time.h>

#define BUFFER_SIZE 128
#define PROC_NAME "seconds"
#define MESSAGE "Seconds\n"
/**
 * Function prototypes
 */


ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos);

static struct file_operations proc_ops = {
        .owner = THIS_MODULE,
        .read = proc_read,

};

/* This function is called when the module is loaded. */
int proc_init(void) {
        // int tm_sec=0;
         int i;
        // creates the /proc/hello entry
        // the following function call is a wrapper for
        // proc_create_data() passing NULL as the last argument
        proc_create(PROC_NAME, 0, NULL, &proc_ops);
        printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
        printk(KERN_INFO "In proc_init(), Jiffies is: %lu and HZ is: %d\n", jiffies, HZ);

  
  while(i<5)
  {
      //I USED AN ONLINE SOURCE TO KNOW HOW TO CONVERT TO SECONDS WHICH IS TO DIVIDE JIFFIES BY HZ
       printk(KERN_INFO "In proc_init(), seconds is: %lu\n", (jiffies/HZ));
       i++;
   }
  
        ////printk(KERN_INFO "In proc_init(), seconds is: %d\n", tm_sec);
     

	return 0;

}
/* This function is called when the module is removed. */

void proc_exit(void) {
        // removes the /proc/jiffies entry
        printk("IPv6: enp0s3: IPv6 duplicate address 2603:8000:d602:ff31:a00:27ff:fed1:835d detected!");
        printk(KERN_INFO "In jiffies/proc/read, jiffies is: %lu\n", jiffies);
       
        printk( KERN_INFO "/proc/%s removed\n", PROC_NAME);

}

/**

 * This function is called each time the /proc/jiffies is read,
 * and is called repeatedly until it returns 0, so
 * there must be logic that ensures it ultimately returns 0
 * once it has collected the data that is to go into the 
 * corresponding /proc file.
 * params:
 * file:
 * buf: buffer in user space
 * count:
 * pos:

 */
ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos) {
         int tm_sec;
        int rv = 0;
        char buffer[BUFFER_SIZE];
        static int completed = 0;
        if (completed) {
                completed = 0;
                return 0;

        }
        completed = 1;
        for (int tm_sec=1; i<5; i++)
        {
        rv = sprintf(buffer, "In proc_read(), seconds is: %d\n", tm_sec);
       tm_sec++;
        }
        // copies the contents of buffer to userspace usr_buf
        copy_to_user(usr_buf, buffer, rv);
        return rv;
}
/* Macros for registering module entry and exit points. */
module_init( proc_init );
module_exit( proc_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Seconds Module");
MODULE_AUTHOR("SGG");
