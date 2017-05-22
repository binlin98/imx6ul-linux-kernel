#include <linux/err.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/irqdomain.h>
#include <linux/irqchip/chained_irq.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/basic_mmio_gpio.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/module.h>
#include <asm-generic/bug.h>


#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <asm/mach-types.h>
#include <linux/gpio.h>
#include <linux/io.h>
#include <linux/of_gpio.h>

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/rtc.h>
#include <linux/unistd.h>
#include <linux/interrupt.h>

static int customize_gpio_probe(struct platform_device *pdev)
{
	int rst,ret;
	int LCD_PWREN,DISP0_BLEN;
	int RTP_RST;
	struct device_node* np = pdev->dev.of_node;
	
	printk("ben: customize_gpio_probe \n");

	//s607 gpio
   	rst = of_get_named_gpio(np, "ENET_PWREN", 0);
    if (!gpio_is_valid(rst)){
        printk("can not find ENET_PWREN gpio pins\n");
        return -1;
    }
    ret = gpio_request(rst, "ENET_PWREN");
    if(ret){
        printk("request gpio ENET_PWREN failed\n");
        return;
    }
    gpio_direction_output(rst, 1);


    rst = of_get_named_gpio(np, "AUD_PWREN", 0);
    if (!gpio_is_valid(rst)){
        printk("can not find AUD_PWREN gpio pins\n");
        return -1;
    }
    ret = gpio_request(rst, "AUD_PWREN");
    if(ret){
        printk("request gpio AUD_PWREN failed\n");
        return;
    }
    gpio_direction_output(rst, 1);

    rst = of_get_named_gpio(np, "LCD_BLEN", 0);
    if (!gpio_is_valid(rst)){
        printk("can not find LCD_BLEN gpio pins\n");
        return -1;
    }
    ret = gpio_request(rst, "LCD_BLEN");
    if(ret){
        printk("request gpio LCD_BLEN failed\n");
        return;
    }
    gpio_direction_output(rst, 1);
	
	#if 0	
	//111e lan pwren/reset
	rst = of_get_named_gpio(np, "LAN_PWREN", 0);
	if (!gpio_is_valid(rst)){
    	printk("can not find LAN_PWREN gpio pins\n");
        return -1;
	}
    ret = gpio_request(rst, "LAN_PWREN");
    if(ret){
    	printk("request gpio LAN_PWREN failed\n");
        return;
  	}
	gpio_direction_output(rst, 1);
	
	rst = of_get_named_gpio(np, "LAN_RESET", 0);
	if (!gpio_is_valid(rst)){
    	printk("can not find LAN_RESET gpio pins\n");
        return -1;
	}
    ret = gpio_request(rst, "LAN_RESET");
    if(ret){
    	printk("request gpio LAN_RESET failed\n");
        return;
  	}
    gpio_direction_output(rst, 0);
	mdelay(200);
	gpio_direction_output(rst, 1);
	#endif
	
	#if 0
	//HUB_reset
    rst = of_get_named_gpio(np, "HUB_reset", 0);
    if (!gpio_is_valid(rst)){
		printk("can not find HUB_reset gpio pins\n");
        return -1;
    }
    ret = gpio_request(rst, "HUB_reset");
    if(ret){
        printk("request gpio HUB_reset failed\n");
        return;
    }

    gpio_direction_output(rst, 0);
	mdelay(200);
	gpio_direction_output(rst, 1);
	#endif
	//
	
	return 0;
}

static int customize_gpio_remove(struct platform_device *pdev)
{
#if 0
         __novo_gpio_remove(pdev);                                     
         sysfs_remove_group(&pdev->dev.kobj, &novo_gpio_attr_group);
#endif
         return 0;
}

static const struct of_device_id gpio_dt_ids[] = {
    { .compatible = "customize,gpio", },
    { /* sentinel */ }
};

static struct platform_driver customize_gpio_driver = {
	.probe		= customize_gpio_probe,               
   	.remove     = customize_gpio_remove,
	.driver =
    {
        .name = "customize-gpio",
        .owner = THIS_MODULE,
        .of_match_table = gpio_dt_ids,
    }
};

static int __init customize_gpio_init(void)
{
	int ret;

    printk("customize gpio driver \n");

   	ret = platform_driver_register(&customize_gpio_driver);            
    if(ret)
    	printk("failed to register customize gpio driver \n");
         

	return ret;
}

static void customize_gpio_exit(void)
{
	platform_driver_unregister(&customize_gpio_driver);
}

module_init(customize_gpio_init);
module_exit(customize_gpio_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ben");
MODULE_DESCRIPTION("hio novo gpio driver");

