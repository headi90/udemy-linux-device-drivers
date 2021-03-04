#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#define AUTHOR "Mateusz"
#define DESC "Hello World driver"

static int __init init(void)
{
    pr_info("Hello World\n");
    return 0;
}

static void __exit deinit(void)
{
    pr_info("Goodbye World\n");
}

module_init(init);
module_exit(deinit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);