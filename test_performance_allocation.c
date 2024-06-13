#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/jiffies.h>

#define NUM_ALLOC 1000000
#define ALLOC_SIZE 32

static int __init test_performance_allocation_init(void)
{
    char *kmalloc_buf;
    int *kcalloc_buf;
    int *kmalloc_array_buf;
    unsigned long start, end;
    int i;

    printk(KERN_INFO "Test wydajności alokacji pamięci\n");

    // Test kmalloc
    start = jiffies;
    for (i = 0; i < NUM_ALLOC; i++) {
        kmalloc_buf = kmalloc(ALLOC_SIZE, GFP_KERNEL);
        kfree(kmalloc_buf);
    }
    end = jiffies;
    printk(KERN_INFO "kmalloc: %u jiffies\n", (unsigned int)(end - start));

    // Test kcalloc
    start = jiffies;
    for (i = 0; i < NUM_ALLOC; i++) {
        kcalloc_buf = kcalloc(ALLOC_SIZE, sizeof(int), GFP_KERNEL);
        kfree(kcalloc_buf);
    }
    end = jiffies;
    printk(KERN_INFO "kcalloc: %u jiffies\n", (unsigned int)(end - start));

    // Test kmalloc_array
    start = jiffies;
    for (i = 0; i < NUM_ALLOC; i++) {
        kmalloc_array_buf = kmalloc_array(ALLOC_SIZE, sizeof(int), GFP_KERNEL);
        kfree(kmalloc_array_buf);
    }
    end = jiffies;
    printk(KERN_INFO "kmalloc_array: %u jiffies\n", (unsigned int)(end - start));

    return 0;
}

static void __exit test_performance_allocation_exit(void)
{
    printk(KERN_INFO "Test wydajności zakończony\n");
}

module_init(test_performance_allocation_init);
module_exit(test_performance_allocation_exit);
