#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/gcd.h>
#include <linux/hash.h>

// struct birthday {
//    int day;
//    int month;
//    int year;
//    struct list_head listptrs;
// };
// static LIST_HEAD(birthday_list);   /*creates (empty) birthday list */

// void append_birthday(int day, int month, int year){
//     struct birthday* person = kmalloc(sizeof(*person),GFP_KERNEL);
//     person->day = day;
//     person->month = month;
//     person->year = year;
//     INIT_LIST_HEAD(&person->listptrs);
//     list_add_tail(&person->listptrs, &birthday_list);
// }
// /*-----------------------------------------------------------------------*/
// void print_birthday_list(void) {
//      struct birthday* ptr;
//      list_for_each_entry(ptr, &birthday_list, listptrs) {
//           printk(KERN_INFO "%02d/%02d/%04d", ptr->day, ptr->month, ptr->year);
//     }
//     printk(KERN_INFO "\n");
/*-----------------------------------------------------------------------*/
// void delete_birthday_list(void) {
//     struct birthday *ptr, *next;
//     list_for_each_entry_safe(ptr, next, &birthday_list, listptrs)  {
//        list_del(&ptr->listptrs);
//        kfree(ptr);
//     }
//     printk(KERN_INFO "Birthday list deleted successfully\n");
// }
/*------------------------------------------------------------------------*/
/*This function is called when the module is loaded */
int simple_init(void)
{     
       printk(KERN_INFO "Loading Module\n");
       printk(KERN_INFO "GOLDEN_RATIO_PRIME is: %lu\n", GOLDEN_RATIO_PRIME);
    //    printk(KERN_INFO "Creating birthday list\n");
    //    append_birthday(14,  2,  1000);
    //    append_birthday(25,  5,  500);
    //    append_birthday(4,  7,  1000);
    //    append_birthday(31,  10,  1776);
    //    append_birthday(25,  12,  1980);

    //    printk(KERN_INFO "Printing birthday list (dd/mm/yyyy)\n");
    //    print_birthday_list();
       return 0;
}
void simple_exit(void) {
       printk(KERN_INFO "Removing Module\n");
       printk(KERN_INFO "gcd(3,300, 24) is %lu\n", gcd(3300, 24));
    //    printk(KERN_INFO "Deleting birthday list\n");
    //    delete_birthday_list();
}
/*---------------------------------------------------------------------------*/
/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");


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

#define BUFFER_SIZE 128
#define PROC_NAME "jiffies"
#define MESSAGE "Jiffies\n"
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
        // creates the /proc/hello entry
        // the following function call is a wrapper for
        // proc_create_data() passing NULL as the last argument
        proc_create(PROC_NAME, 0, NULL, &proc_ops);
        printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
        printk(KERN_INFO "In proc_init(), Jiffies is: %lu and HZ is: %d\n", jiffies, HZ);
        
        //printk(KERN_INFO "In jiffies/proc/read, jiffies is: %lu\n", jiffies);
        
        //printk(KERN_INFO "In jiffies/proc/read, jiffies is: %lu\n", jiffies);
        //MISSING LINE
        //printk(KERN_INFO "In jiffies/proc/read, jiffies is: %lu\n", jiffies);
      

	return 0;

}
/* This function is called when the module is removed. */

void proc_exit(void) {
        // removes the /proc/jiffies entry
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

        int rv = 0;
        char buffer[BUFFER_SIZE];
        static int completed = 0;
        if (completed) {
                completed = 0;
                return 0;

        }
        completed = 1;
        rv = sprintf(buffer, "In jiffies/proc/read, jiffies is: %lu\n", jiffies);
       
        //rv = sprintf(buffer, "Hello Jiffies\n");

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
