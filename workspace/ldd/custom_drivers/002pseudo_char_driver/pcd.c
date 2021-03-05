#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/kernel.h>
#include <linux/module.h>

// Add function name before every print function
#undef pr_fmt
#define pr_fmt(fmt) "%s: " fmt, __func__

#define AUTHOR "Mateusz"
#define DESC "Pseudo Character Driver"

#define DEV_MEM_SIZE 512

/* Pseudo device's memory */
char device_buffer[DEV_MEM_SIZE];

// This holds device number
dev_t device_number;

// Cdev variable
struct cdev pcd_cdev;

loff_t pcd_llseek(struct file* filp, loff_t off, int whence)
{
    pr_info("lseek PSD\n");
    return 0;
}

ssize_t pcd_read(struct file* filp, char __user* buff, size_t count, loff_t* f_pos)
{
    pr_info("read PSD for %zu bytes\n", count);
    return 0;
}

ssize_t pcd_write(struct file* filp, const char __user* buff, size_t count, loff_t* f_pos)
{
    pr_info("write PSD for %zu bytes\n", count);
    return 0;
}

int pcd_open(struct inode* inode, struct file* filp)
{
    pr_info("open PSD\n");
    return 0;
}

int pcd_release(struct inode* inode, struct file* filp)
{
    pr_info("close PSD\n");
    return 0;
}

// file operations of the driver
struct file_operations pcd_fops = {
    .open = pcd_open,
    .release = pcd_release,
    .read = pcd_read,
    .write = pcd_write,
    .llseek = pcd_llseek,
    .owner = THIS_MODULE};

struct class* class_pcd;
struct device* device_pcd;

static int __init pcd_driver_init(void)
{
    // 1. Dynamically allocate a device number
    alloc_chrdev_region(&device_number, 0, 1, "pcd_devices");
    pr_info("PSD device number <major>:<minor> = %d:%d\n", MAJOR(device_number), MINOR(device_number));

    // 2. Initialize the cdev structure with fops
    cdev_init(&pcd_cdev, &pcd_fops);

    // 3. Register a device (cdev) structure with VFS
    pcd_cdev.owner = THIS_MODULE;
    cdev_add(&pcd_cdev, device_number, 1);

    // create device class under /sys/class/
    class_pcd = class_create(THIS_MODULE, "pcd_class");

    // populate the sysfs with device infrmation
    device_pcd = device_create(class_pcd, NULL, device_number, NULL, "pcd");
    pr_info("PSD init was successful\n");
    return 0;
}

static void __exit pcd_driver_cleanup(void)
{
    device_destroy(class_pcd, device_number);
    class_destroy(class_pcd);
    cdev_del(&pcd_cdev);
    unregister_chrdev_region(device_number, 1);
    pr_info("Cleanup PSD\n");
}

module_init(pcd_driver_init);
module_exit(pcd_driver_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);