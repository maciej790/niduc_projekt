#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

MODULE_DESCRIPTION("Test nieinicjalizowanej pamięci: kmalloc, kcalloc, kmalloc_array");

#define ALLOC_SIZE 1024

static void test_kmalloc(void)
{
    char *kmalloc_buf;

    printk(KERN_INFO "Test kmalloc bez inicjalizacji\n");

    kmalloc_buf = kmalloc(ALLOC_SIZE, GFP_KERNEL);
    if (!kmalloc_buf) {
        printk(KERN_ERR "kmalloc failed\n");
        return;
    }

    // Próba odczytu z niezainicjalizowanej pamięci
    printk(KERN_INFO "Niezainicjalizowana pamięć (kmalloc): %s\n", kmalloc_buf);

    // Zwalnianie pamięci
    kfree(kmalloc_buf);
}

static void test_kcalloc(void)
{
    int *kcalloc_buf;

    printk(KERN_INFO "Test kcalloc bez inicjalizacji\n");

    kcalloc_buf = kcalloc(ALLOC_SIZE / sizeof(int), sizeof(int), GFP_KERNEL);
    if (!kcalloc_buf) {
        printk(KERN_ERR "kcalloc failed\n");
        return;
    }

    // Próba odczytu z niezainicjalizowanej pamięci
    printk(KERN_INFO "Niezainicjalizowana pamięć (kcalloc): %d\n", kcalloc_buf[0]);

    // Zwalnianie pamięci
    kfree(kcalloc_buf);
}

static void test_kmalloc_array(void)
{
    int *kmalloc_array_buf;

    printk(KERN_INFO "Test kmalloc_array bez inicjalizacji\n");

    kmalloc_array_buf = kmalloc_array(ALLOC_SIZE / sizeof(int), sizeof(int), GFP_KERNEL);
    if (!kmalloc_array_buf) {
        printk(KERN_ERR "kmalloc_array failed\n");
        return;
    }

    // Próba odczytu z niezainicjalizowanej pamięci
    printk(KERN_INFO "Niezainicjalizowana pamięć (kmalloc_array): %d\n", kmalloc_array_buf[0]);

    // Zwalnianie pamięci
    kfree(kmalloc_array_buf);
}

static int __init test_uninitialized_memory_init(void)
{
    test_kmalloc();
    test_kcalloc();
    test_kmalloc_array();
    return 0;
}

static void __exit test_uninitialized_memory_exit(void)
{
    printk(KERN_INFO "Test nieinicjalizowanej pamięci zakończony\n");
}

module_init(test_uninitialized_memory_init);
module_exit(test_uninitialized_memory_exit);
