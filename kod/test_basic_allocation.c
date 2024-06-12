#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Twoje Imię");
MODULE_DESCRIPTION("Test podstawowy alokacji pamięci: kmalloc, kcalloc, kmalloc_array");

static int __init test_basic_allocation_init(void)
{
    char *kmalloc_buf;
    int *kcalloc_buf;
    int *kmalloc_array_buf;
    size_t size = 1024;

    printk(KERN_INFO "Test podstawowy alokacji pamięci\n");

    // Test kmalloc
    kmalloc_buf = kmalloc(size, GFP_KERNEL);
    if (!kmalloc_buf) {
        printk(KERN_ERR "kmalloc failed\n");
    } else {
        printk(KERN_INFO "kmalloc succeeded\n");
        kfree(kmalloc_buf);
    }

    // Test kcalloc
    kcalloc_buf = kcalloc(size, sizeof(int), GFP_KERNEL);
    if (!kcalloc_buf) {
        printk(KERN_ERR "kcalloc failed\n");
    } else {
        printk(KERN_INFO "kcalloc succeeded\n");
        kfree(kcalloc_buf);
    }

    // Test kmalloc_array
    kmalloc_array_buf = kmalloc_array(size, sizeof(int), GFP_KERNEL);
    if (!kmalloc_array_buf) {
        printk(KERN_ERR "kmalloc_array failed\n");
    } else {
        printk(KERN_INFO "kmalloc_array succeeded\n");
        kfree(kmalloc_array_buf);
    }

    return 0;
}

static void __exit test_basic_allocation_exit(void)
{
    printk(KERN_INFO "Test podstawowy zakończony\n");
}

module_init(test_basic_allocation_init);
module_exit(test_basic_allocation_exit);
