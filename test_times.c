#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/time.h>

#define NUM_ALLOCS 1000 // Liczba alokacji
#define BLOCK_SIZE 256  // Rozmiar bloków w bajtach

static void test_kcalloc(void)
{
    int i;
    int *buf[NUM_ALLOCS];
    ktime_t start, end;
    s64 total_time_alloc = 0, total_time_free = 0;

    printk(KERN_INFO "Rozpoczęcie testu wydajnościowego alokacji pamięci: kcalloc\n");

    start = ktime_get();
    for (i = 0; i < NUM_ALLOCS; i++)
    {
        buf[i] = kcalloc(BLOCK_SIZE / sizeof(int), sizeof(int), GFP_KERNEL);
        if (!buf[i])
        {
            printk(KERN_ERR "Alokacja pamięci nie powiodła się na iteracji %d za pomocą kcalloc\n", i);
            while (i--)
            {
                kfree(buf[i]);
            }
            return;
        }
    }
    end = ktime_get();
    total_time_alloc = ktime_to_ns(ktime_sub(end, start));
    printk(KERN_INFO "Czas alokacji %d bloków za pomocą kcalloc: %lld ns\n", NUM_ALLOCS, total_time_alloc);

    start = ktime_get();
    for (i = 0; i < NUM_ALLOCS; i++)
    {
        kfree(buf[i]);
    }
    end = ktime_get();
    total_time_free = ktime_to_ns(ktime_sub(end, start));
    printk(KERN_INFO "Czas zwalniania %d bloków za pomocą kcalloc: %lld ns\n", NUM_ALLOCS, total_time_free);

    printk(KERN_INFO "Zakończenie testu wydajnościowego alokacji pamięci: kcalloc\n");
}

static void test_kmalloc_array(void)
{
    int i;
    int *buf[NUM_ALLOCS];
    ktime_t start, end;
    s64 total_time_alloc = 0, total_time_free = 0;

    printk(KERN_INFO "Rozpoczęcie testu wydajnościowego alokacji pamięci: kmalloc_array\n");

    start = ktime_get();
    for (i = 0; i < NUM_ALLOCS; i++)
    {
        buf[i] = kmalloc_array(BLOCK_SIZE / sizeof(int), sizeof(int), GFP_KERNEL);
        if (!buf[i])
        {
            printk(KERN_ERR "Alokacja pamięci nie powiodła się na iteracji %d za pomocą kmalloc_array\n", i);
            while (i--)
            {
                kfree(buf[i]);
            }
            return;
        }
    }
    end = ktime_get();
    total_time_alloc = ktime_to_ns(ktime_sub(end, start));
    printk(KERN_INFO "Czas alokacji %d bloków za pomocą kmalloc_array: %lld ns\n", NUM_ALLOCS, total_time_alloc);

    start = ktime_get();
    for (i = 0; i < NUM_ALLOCS; i++)
    {
        kfree(buf[i]);
    }
    end = ktime_get();
    total_time_free = ktime_to_ns(ktime_sub(end, start));
    printk(KERN_INFO "Czas zwalniania %d bloków za pomocą kmalloc_array: %lld ns\n", NUM_ALLOCS, total_time_free);

    printk(KERN_INFO "Zakończenie testu wydajnościowego alokacji pamięci: kmalloc_array\n");
}

static int __init performance_test_init(void)
{
    printk(KERN_INFO "Rozpoczęcie testu wydajnościowego alokacji pamięci\n");

    test_kcalloc();
    test_kmalloc_array();

    printk(KERN_INFO "Zakończenie testu wydajnościowego alokacji pamięci\n");

    return 0;
}

static void __exit performance_test_exit(void)
{
    printk(KERN_INFO "Moduł testowy wydajnościowy został usunięty\n");
}

module_init(performance_test_init);
module_exit(performance_test_exit);
