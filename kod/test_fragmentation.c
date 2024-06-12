#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/random.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Twoje Imię");
MODULE_DESCRIPTION("Test fragmentacji pamięci: kmalloc, kcalloc, kmalloc_array");

#define NUM_BLOCKS 1000
#define MAX_BLOCK_SIZE 1024

static int __init test_fragmentation_init(void)
{
    void *blocks[NUM_BLOCKS];
    size_t sizes[NUM_BLOCKS];
    int i;

    printk(KERN_INFO "Test fragmentacji pamięci\n");

    // Alokacja pamięci z losowymi rozmiarami bloków
    for (i = 0; i < NUM_BLOCKS; i++) {
        sizes[i] = get_random_long() % MAX_BLOCK_SIZE + 1;
        blocks[i] = kmalloc(sizes[i], GFP_KERNEL);
        if (!blocks[i]) {
            printk(KERN_ERR "kmalloc failed at block %d\n", i);
            break;
        }
    }

    // Zwalnianie co drugiego bloku, aby zasymulować fragmentację
    for (i = 0; i < NUM_BLOCKS; i += 2) {
        if (blocks[i]) {
            kfree(blocks[i]);
        }
    }

    printk(KERN_INFO "Test fragmentacji zakończony\n");
    return 0;
}

static void __exit test_fragmentation_exit(void)
{
    printk(KERN_INFO "Moduł fragmentacji pamięci został usunięty\n");
}

module_init(test_fragmentation_init);
module_exit(test_fragmentation_exit);
