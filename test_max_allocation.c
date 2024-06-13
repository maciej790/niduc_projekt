#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

static int __init test_max_allocation_init(void)
{
    char *kmalloc_buf;
    int *kcalloc_buf;
    int *kmalloc_array_buf;
    size_t max_size = SIZE_MAX;

    printk(KERN_INFO "Test maksymalnej alokacji pamięci\n");

    // Test kmalloc
    kmalloc_buf = kmalloc(max_size, GFP_KERNEL);
    if (!kmalloc_buf) {
        printk(KERN_ERR "kmalloc failed for max size\n");
    } else {
        printk(KERN_INFO "kmalloc succeeded for max size\n");
        kfree(kmalloc_buf);
    }

    // Test kcalloc
    kcalloc_buf = kcalloc(max_size, sizeof(int), GFP_KERNEL);
    if (!kcalloc_buf) {
        printk(KERN_ERR "kcalloc failed for max size\n");
    } else {
        printk(KERN_INFO "kcalloc succeeded for max size\n");
        kfree(kcalloc_buf);
    }

    // Test kmalloc_array
    kmalloc_array_buf = kmalloc_array(max_size, sizeof(int), GFP_KERNEL);
    if (!kmalloc_array_buf) {
        printk(KERN_ERR "kmalloc_array failed for max size\n");
    } else {
        printk(KERN_INFO "kmalloc_array succeeded for max size\n");
        kfree(kmalloc_array_buf);
    }

    return 0;
}

static void __exit test_max_allocation_exit(void)
{
    printk(KERN_INFO "Test maksymalnej alokacji zakończony\n");
}

module_init(test_max_allocation_init);
module_exit(test_max_allocation_exit);
