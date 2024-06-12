#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Twoje Imię");
MODULE_DESCRIPTION("Testy alokacji pamięci: kmalloc, kcalloc, kmalloc_array");

static int __init my_module_init(void)
{
    void *ptr;

    printk(KERN_INFO "Inicjalizacja modułu testowego\n");

    // Test kmalloc
    ptr = kmalloc(0, GFP_KERNEL);
    if (!ptr || ptr == ZERO_SIZE_PTR) {
        printk(KERN_INFO "kmalloc(0) returned NULL or ZERO_SIZE_PTR\n");
    } else {
        printk(KERN_ERR "kmalloc(0) did not return NULL\n");
    }

    // Test kcalloc
    ptr = kcalloc(0, sizeof(int), GFP_KERNEL);
    if (!ptr || ptr == ZERO_SIZE_PTR) {
        printk(KERN_INFO "kcalloc(0, size) returned NULL or ZERO_SIZE_PTR\n");
    } else {
        printk(KERN_ERR "kcalloc(0, size) did not return NULL\n");
    }

    // Test kmalloc_array
    ptr = kmalloc_array(0, sizeof(int), GFP_KERNEL);
    if (!ptr || ptr == ZERO_SIZE_PTR) {
        printk(KERN_INFO "kmalloc_array(0, size) returned NULL or ZERO_SIZE_PTR\n");
    } else {
        printk(KERN_ERR "kmalloc_array(0, size) did not return NULL\n");
    }

    return 0;
}

static void __exit my_module_exit(void)
{
    printk(KERN_INFO "Moduł testowy został usunięty\n");
}

module_init(my_module_init);
module_exit(my_module_exit);
