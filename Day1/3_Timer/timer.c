/*
 *
 * HZ number indicated number of jiffies per second 
 *
 */
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/jiffies.h>

#include <linux/sched.h> // schedule_timeout()

#include <linux/delay.h> // mdelay(), udelay(), ndelay()

#define TIME_OUT 	3
#define MILI_TIMEOUT 	1000
#define MICRO_TIMEOUT	1000
#define NANO_TIMEOUT	1000

struct timer_list ELDD_timer;

static void ELDD_timer_func(unsigned long data) {
	pr_info("%s() | Timer function got called with data '%lu'\n", __func__, data);
	
	/* ELDD_timer_func can be called repeatadly 
	 * + Pass with diffrent configuration
	 *	// -- Initialize the timer
	 *	init_timer(&ELDD_timer);
	 *	ELDD_timer.expires = jiffies + (TIME_OUT * HZ);
	 *	ELDD_timer.function = ELDD_timer_func;
	 *	ELDD_timer.data = 20;
	 *	// -- Timer Start
	 *	add_timer(&ELDD_timer);
	 * 
	 * + Modefiy only timeout period 
	 * 	 mod_timer(&ELDD_timer, jiffies + HZ / 2);
	 */
}

int __init timer_init(void) {
	unsigned long timeout;	

	pr_info("%s() | Yeah, I Started Kernel Hacking..\n", __func__);


	/****************************** 
	 * 
	 *	Long Delay 
	 *
	 *****************************/
	timeout = jiffies + (TIME_OUT * HZ);
	while(time_before(jiffies, timeout));/* Type A : Do something for TIME_OUT seconds */	
	pr_info("%s() | We have done dummy things for %d seconds\n", __func__, TIME_OUT);

		
	timeout = jiffies + (TIME_OUT * HZ);
	while(1) { /* Type B : Wait for TIME_OUT second to meet desired condition */
		if (time_after(jiffies, timeout)) {
			pr_info("%s() | %d seconds completed\n", __func__, TIME_OUT);
			break;
		}
	}	
	timeout = jiffies + (TIME_OUT * HZ);
	/* Type C : Sleep for TIME_OUT seconds and allow other part of the Kernel to Run */
	schedule_timeout(timeout);
	pr_info("%s() | Wakeup process after %d seconds\n", __func__, TIME_OUT);
	
	/* Type D : Timeout Function */
	// -- Initialize the timer
	init_timer(&ELDD_timer);
	ELDD_timer.expires = jiffies + (TIME_OUT * HZ);
	ELDD_timer.function = ELDD_timer_func;
	ELDD_timer.data = 10;
	// -- Timer Start
	add_timer(&ELDD_timer);

	/****************************** 
	 * 
	 *	Short Delay 
	 *
	 *****************************/
	pr_info("%s() | Short delay START\n", __func__);
	mdelay(MILI_TIMEOUT); 	/* Type E : MILI_TIMEOUT Seconds delay */
	pr_info("%s() | mdelay Timeout after %d milli seconds\n", __func__, MILI_TIMEOUT);
	udelay(MICRO_TIMEOUT);	/* Type F : MICRO_TIMEOUT Seconds delay */
	pr_info("%s() | udelay Timeout after %d micro seconds\n", __func__, MICRO_TIMEOUT);
	ndelay(NANO_TIMEOUT);	/* Type G : NANO_TIMEOUT Seconds delay */
	pr_info("%s() | ndelay Timeout after %d nano seconds\n", __func__, NANO_TIMEOUT);

	pr_info("Yeah! Everything looks fine..\n");
	return 0;
}

void __exit timer_exit(void) {
	del_timer(&ELDD_timer);
	pr_info("%s() | I will hack more soon!!\n", __func__);
}

module_init(timer_init);
module_exit(timer_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jeet Parikh <jeetparikh616@gmail.com>");
