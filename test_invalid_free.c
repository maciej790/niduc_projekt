#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

static int __init test_invalid_free_init(void)
{
    char *kmalloc_buf;
    int *kcalloc_buf;
    int *kmalloc_array_buf;
    size_t size = 128;

    printk(KERN_INFO "Test nieprawidłowego zwalniania pamięci\n");

    // Test kmalloc
    kmalloc_buf = kmalloc(size, GFP_KERNEL);
    if (!kmalloc_buf) {
        printk(KERN_ERR "kmalloc failed\n");
        return -ENOMEM;
    }

    // Zwalnianie wskaźnika NULL
    kfree(NULL);
    printk(KERN_INFO "Zwalnianie wskaźnika NULL (kmalloc)\n");

    // Zwalnianie wskaźnika
    kfree(kmalloc_buf);
    printk(KERN_INFO "Zwalnianie wskaźnika (kmalloc)\n");

    // Test kcalloc
    kcalloc_buf = kcalloc(size, sizeof(int), GFP_KERNEL);
    if (!kcalloc_buf) {
        printk(KERN_ERR "kcalloc failed\n");
        return -ENOMEM;
    }

    // Zwalnianie wskaźnika NULL
    kfree(NULL);
    printk(KERN_INFO "Zwalnianie wskaźnika NULL (kcalloc)\n");

    // Zwalnianie wskaźnika
    kfree(kcalloc_buf);
    printk(KERN_INFO "Zwalnianie wskaźnika (kcalloc)\n");

    // Test kmalloc_array
    kmalloc_array_buf = kmalloc_array(size, sizeof(int), GFP_KERNEL);
    if (!kmalloc_array_buf) {
        printk(KERN_ERR "kmalloc_array failed\n");
        return -ENOMEM;
    }

    // Zwalnianie wskaźnika NULL
    kfree(NULL);
    printk(KERN_INFO "Zwalnianie wskaźnika NULL (kmalloc_array)\n");

    // Zwalnianie wskaźnika
    kfree(kmalloc_array_buf);
    printk(KERN_INFO "Zwalnianie wskaźnika (kmalloc_array)\n");

    return 0;
}

static void __exit test_invalid_free_exit(void)
{
    printk(KERN_INFO "Test nieprawidłowego zwalniania pamięci zakończony\n");
}

module_init(test_invalid_free_init);
module_exit(test_invalid_free_exit);
