#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/fs.h>

#define DEVICE_NAME "richard_dev"
#define DEVICE_PATH "/dev/richard_dev"

static int major_no;

static int int_gpioTest_probe(struct platform_device *pdev) 
{
    struct device *dev = &pdev->dev;
    printk("%s enter.\n", __func__);
    return 0;
}

static int int_gpioTest_remove(struct platform_device *pdev) 
{
    printk("%s enter.\n", __func__);
    return 0;
}

static int device_open(struct inode* inode, struct file* file)
{
    printk(KERN_EMERG "pid=%d, Node Opened\n", current->pid);
    gpio_request(60, "richard_gpio");
    gpio_direction_output(60, 0);
    return 0;
}

static int device_release(struct inode* inode, struct file* file)
{
    printk(KERN_EMERG "Module Released \n");
    
    return 0;
}

ssize_t device_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    printk("Read count:%d\n", count);
    return 0;
}

ssize_t device_write(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    printk("Write char:%d\n", count);
    return 0;
}

int device_ioctl(struct file* filp, unsigned int cmd, unsigned long args)
{
    int ret = 0;
    printk("device_ioctl cmd:%d\n", cmd);
    return ret;
}

static struct file_operations fops = {
    .open = device_open,
    .release = device_release,
    .unlocked_ioctl = device_ioctl,
    .read = device_read,
    .write = device_write
};

static const struct of_device_id int_gpioTest_dt_ids[] = 
{
    { .compatible = "Richard,gpioTest", },
    {},
};

MODULE_DEVICE_TABLE(of, int_gpioTest_dt_ids);

static struct platform_driver int_gpioTest_driver = 
{
    .driver          = 
    {
    .name            = "gpioTest",
    .owner           = THIS_MODULE,
    .of_match_table  = of_match_ptr(int_gpioTest_dt_ids),
    },
    .probe           = int_gpioTest_probe,
    .remove          = int_gpioTest_remove,
};

static struct class* my_class;

static int __init int_gpioTest_init(void)
{
    int ret;

    major_no = register_chrdev(0, DEVICE_NAME, &fops);
    printk(KERN_EMERG "Module Major No : %d\n", major_no);

    my_class = class_create(THIS_MODULE, DEVICE_NAME);
    device_create(my_class, NULL, MKDEV(major_no, 0), NULL, DEVICE_NAME);
    printk(KERN_EMERG "Module loaded in kernel\n");

    ret = platform_driver_register(&int_gpioTest_driver);
    if (ret)
        printk(KERN_ERR "int gpioTest: probe failed: %d\n", ret);

    return ret;
}
module_init(int_gpioTest_init);

static void __exit int_gpioTest_exit(void)
{
    platform_driver_unregister(&int_gpioTest_driver);

    device_destroy(my_class, MKDEV(major_no, 0));
    class_unregister(my_class);
    class_destroy(my_class);
    unregister_chrdev(major_no, DEVICE_NAME);
    
    gpio_set_value(60, 0);
    gpio_free(60);

    printk(KERN_EMERG "gpioTest Module remove\n");
}
module_exit(int_gpioTest_exit);

MODULE_LICENSE("GPL");
