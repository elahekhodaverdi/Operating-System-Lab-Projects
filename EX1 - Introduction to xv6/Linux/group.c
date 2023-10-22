#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int init_module(void)
{
  printk(KERN_INFO "Group 29:\n- Ferehshte Bagheri : 810100089\n- Elahe Khodaverdi : 810100132\n- Atefe Mirzakhani : 810100220\n");
  return 0;
}

void cleanup_module(void) {}