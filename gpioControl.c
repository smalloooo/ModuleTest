#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>

static int int_gpioTest_probe(struct platform_device *pdev) {
    struct device *dev = &pdev->dev;
    printk("%s enter.\n", __func__);
    return 0;
}

static int int_gpioTest_remove(struct platform_device *pdev) {

    printk("%s enter.\n", __func__);

    return 0;
}

static const struct of_device_id int_gpioTest_dt_ids[] = {
    { .compatible = "Richard,gpioTest", },
    {},
};

MODULE_DEVICE_TABLE(of, int_gpioTest_dt_ids);

static struct platform_driver int_gpioTest_driver = {
    .driver          = {
    .name            = "gpioTest",
    .owner           = THIS_MODULE,
    .of_match_table  = of_match_ptr(int_gpioTest_dt_ids),
    },
    .probe           = int_gpioTest_probe,
    .remove          = int_gpioTest_remove,
};

static int __init int_gpioTest_init(void)
{
    int ret;

    ret = platform_driver_register(&int_gpioTest_driver);
    if (ret)
        printk(KERN_ERR "int gpioTest: probe failed: %d\n", ret);

    return ret;
}
module_init(int_gpioTest_init);

static void __exit int_gpioTest_exit(void)
{
    platform_driver_unregister(&int_gpioTest_driver);
}
module_exit(int_gpioTest_exit);

MODULE_LICENSE("GPL");
