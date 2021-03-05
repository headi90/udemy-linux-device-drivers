#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define AUTHOR "Mateusz"
#define DESC "Pseudo Character Driver"

#define DEV_MEM_SIZE 512

/* Pseudo device's memory */

char device_buffer[DEV_MEM_SIZE];

// This holds device number
dev_t device_number;

static int __init pcd_driver_init(void)
{
    // Dynamically allocate a device number
    alloc_chrdev_region(&device_number, 0, 1, "pcd");
    pr_info("Hello PSD\n");
    return 0;
}

static void __exit pcd_driver_cleanup(void)
{
    pr_info("Goodbye PSD\n");
}

module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);