#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/gfp.h> // GFP_* Flags
#include <linux/slab.h>


int __init hello_init(void) {
	uint32_t *k_data;
	uint32_t *z_data;
	int32_t *v_data;

	/* Type A : memory-allocation function that returns contiguous 
	 * 	    memory from ZONE_NORMAL
	 *	    Flags :
	 *	    	GFP_KERNEL : Used by process context code to allocate memory
	 *		GFP_ATOMIC : Used by interrupt context code to get hold of memory
	 *
	 * 	    The function returns kernel logical addresses
	 */
	k_data = kmalloc(sizeof(uint32_t), GFP_KERNEL);
	if(k_data == NULL) {
		pr_info("%s() | Unable to allocate memory via kmalloc()\n", __func__);
		return -1;
	}
	
	/* Type B : To get zeroed kmalloced memory */
	z_data = kzalloc(sizeof(uint32_t), GFP_KERNEL);
	if(z_data == NULL) {
		pr_info("%s() | Unable to allocate memory via kzalloc()\n", __func__);
		return -1;
	}
	
	/* Type C : If you need to allocate large memory buffers, and 
	 * 	    you don't require the memory to be physically contiguous, 
	 *	    use vmalloc() rather than kmalloc()
	 *
	 * 	    The function returns kernel virtual addresses
	 */
	v_data = vmalloc(sizeof(uint32_t));
	if(v_data == NULL) {
		pr_info("%s() | Unable to allocate memory via vmalloc()\n", __func__);
		return -1;
	}
	*k_data = 10;
	*z_data = 40;
	*v_data = -1;
	
	pr_info("%s() | k_data : %u, z_data : %u, v_data : %d\n", __func__, 
									*k_data, 
									*z_data,
									*v_data);
	kfree(k_data);
	kfree(z_data);
	vfree(v_data);
	pr_info("%s() | We have allocated memory in Linux Kernel succesfully!\n", __func__);
	return 0;
}

void __exit hello_exit(void) {
	pr_info("%s() | Have you excited to hack Linux Kernel further?\n", __func__);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jeet Parikh <jeetparikh616@gmail.com>");
