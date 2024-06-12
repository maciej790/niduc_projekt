#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Twoje Imię");
MODULE_DESCRIPTION("Test zerowej alokacji: kmalloc, kcalloc, kmalloc_array");

static int __init test_zero_allocation_init(void)
{
    char *kmalloc_buf;
    int *kcalloc_buf;
    int *kmalloc_array_buf;

    printk(KERN_INFO "Test zerowej alokacji\n");

    // Test kmalloc
    kmalloc_buf = kmalloc(0, GFP_KERNEL);
    if (!kmalloc_buf)
    {
        printk(KERN_INFO "kmalloc(0) returned NULL as expected\n");
    }
    else
    {
        printk(KERN_WARNING "kmalloc(0) did not return NULL\n");
        kfree(kmalloc_buf);
    }

    // Test kcalloc
    kcalloc_buf = kcalloc(0, sizeof(int), GFP_KERNEL);
    if (!kcalloc_buf)
    {
        printk(KERN_INFO "kcalloc(0, size) returned NULL as expected\n");
    }
    else
    {
        printk(KERN_WARNING "kcalloc(0, size) did not return NULL\n");
        kfree(kcalloc_buf);
    }

    // Test kmalloc_array
    kmalloc_array_buf = kmalloc_array(0, sizeof(int), GFP_KERNEL);
    if (!kmalloc_array_buf)
    {
        printk(KERN_INFO "kmalloc_array(0, size) returned NULL as expected\n");
    }
    else
    {
        printk(KERN_WARNING "kmalloc_array(0, size) did not return NULL\n");
        kfree(kmalloc_array_buf);
    }

    return 0;
}

static void __exit test_zero_allocation_exit(void)
{
    printk(KERN_INFO "Test zerowej alokacji zakończony\n");
}

module_init(test_zero_allocation_init);
module_exit(test_zero_allocation_exit);
