#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Twoje Imię");
MODULE_DESCRIPTION("Test przepełnienia bufora: kmalloc, kcalloc, kmalloc_array");

static int __init test_buffer_overflow_init(void)
{
    char *kmalloc_buf;
    int *kcalloc_buf;
    int *kmalloc_array_buf;
    size_t size = 128;

    printk(KERN_INFO "Test przepełnienia bufora\n");

    // Test kmalloc
    kmalloc_buf = kmalloc(size, GFP_KERNEL);
    if (!kmalloc_buf) {
        printk(KERN_ERR "kmalloc failed\n");
        return -ENOMEM;
    }
    // Celowe wyjście poza przydzielony bufor
    kmalloc_buf[size + 10] = 'A';
    printk(KERN_INFO "Próba przepełnienia bufora kmalloc\n");
    kfree(kmalloc_buf);

    // Test kcalloc
    kcalloc_buf = kcalloc(size, sizeof(int), GFP_KERNEL);
    if (!kcalloc_buf) {
        printk(KERN_ERR "kcalloc failed\n");
        return -ENOMEM;
    }
    // Celowe wyjście poza przydzielony bufor
    kcalloc_buf[size + 10] = 42;
    printk(KERN_INFO "Próba przepełnienia bufora kcalloc\n");
    kfree(kcalloc_buf);

    // Test kmalloc_array
    kmalloc_array_buf = kmalloc_array(size, sizeof(int), GFP_KERNEL);
    if (!kmalloc_array_buf) {
        printk(KERN_ERR "kmalloc_array failed\n");
        return -ENOMEM;
    }
    // Celowe wyjście poza przydzielony bufor
    kmalloc_array_buf[size + 10] = 42;
    printk(KERN_INFO "Próba przepełnienia bufora kmalloc_array\n");
    kfree(kmalloc_array_buf);

    return 0;
}

static void __exit test_buffer_overflow_exit(void)
{
    printk(KERN_INFO "Test przepełnienia bufora zakończony\n");
}

module_init(test_buffer_overflow_init);
module_exit(test_buffer_overflow_exit);
