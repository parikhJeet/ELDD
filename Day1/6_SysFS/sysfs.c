#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/sysfs.h>
#include<linux/kobject.h>

volatile uint32_t ELDD_var;

ssize_t ELDD_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf) {
	pr_info("%s() | Return data to User Space\n", __func__);
	return sprintf(buf, "%d", ELDD_var);
}

ssize_t ELDD_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count) {
	pr_info("%s() | Get data from User Space\n", __func__);
        sscanf(buf,"%d", &ELDD_var);
        return count;
}

struct kobj_attribute ELDD_attr = __ATTR_RW(ELDD);

int __init sysfs_init(void) {
	uint32_t ret;
	pr_info("%s() | Start attacking on SysFS\n", __func__);

	/* Create sysfs file */
	ret = sysfs_create_file(NULL ,&ELDD_attr.attr);
	if(!ret){
		printk(KERN_INFO"Oopps..! We unable to create sysfs File\n");
                goto r_sysfs;
	}

        printk(KERN_INFO "Now we can use ELDD sysfs file in user space\n");
	return 0;	
r_sysfs:
	sysfs_remove_file(NULL, &ELDD_attr.attr);
	return -1;
}

void __exit sysfs_exit(void) {
	pr_info("%s() | Yeah! We explored SysFS\n", __func__);
}

module_init(sysfs_init);
module_exit(sysfs_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jeet Parikh <jeetparikh616@gmail.com>");
