#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define BUF_SIZE 100

static struct proc_dir_entry *ent;
char buf[BUF_SIZE];
int32_t ELDD_num;

// echo "10" > /proc/ELDD_dev 
static ssize_t ELDD_write(struct file *file, const char __user *ubuf, size_t count, loff_t *ppos) 
{
	pr_info("%s() | Copy data from user space\n", __func__);
	if(copy_from_user(buf, ubuf, count))
		return -EFAULT;
	sscanf(buf,"%d",&ELDD_num);
	return -1;
}
 
static ssize_t ELDD_read(struct file *file, char __user *ubuf,size_t count, loff_t *ppos) 
{
	int len = 0;
	pr_info("%s() | Copy data to user space\n", __func__);
	
	len = sprintf(buf,"ELDD_data : %d", ELDD_num);
	
	if(copy_to_user(ubuf, buf, count))
		return -EFAULT;
	return len;
}
 
static struct file_operations ELDD_ops = 
{
	.owner = THIS_MODULE,
	.read = ELDD_read,
	.write = ELDD_write,
};
 
static int proc_init(void)
{
	ent = proc_create("ELDD_dev", 0660, NULL, &ELDD_ops);
	if(ent == NULL) {
		pr_err("%s() | Failed to create proc entry\n", __func__);
		return -1;
	}
	pr_info("%s() | Now you can accress proc entry\n", __func__); 
	return 0;
}
 
static void proc_exit(void)
{
	proc_remove(ent);
	pr_info("%s() | Yes! You done with your ProcFS experiment\n", __func__); 
}
 
module_init(proc_init);
module_exit(proc_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jeet Parikh <jeetparikh616@gmail.com>");
