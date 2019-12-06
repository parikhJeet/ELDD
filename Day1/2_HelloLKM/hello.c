#include <linux/kernel.h>
#include <linux/module.h>

int __init hello_init(void) {
	pr_info("%s() | Yeah, I Started Kernel Hacking..\n", __func__);
	return 0;
}

void __exit hello_exit(void) {
	pr_info("%s() | I will hack more soon!!\n", __func__);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jeet Parikh <jeetparikh616@gmail.com>");
