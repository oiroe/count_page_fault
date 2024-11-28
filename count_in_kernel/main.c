#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/pid.h>

static int	pid = -1;
module_param(pid, int, 0);
MODULE_PARM_DESC(pid, "Process ID to monitor page faults");

static struct task_struct	*task;

static int __init	pagefault_counter_init(void)
{
	if (pid <= 0)
	{
		pr_err("Invalid PID: %d\n", pid);
		return (-EINVAL);
	}

	task = pid_task(find_vpid(pid), PIDTYPE_PID);
	if (!task)
	{
		pr_err("No process found with PID %d\n", pid);
		return (-ESRCH);
	}
	pr_info("Monitoring process PID %d (%s)\n", pid, task->comm);
	pr_info("Initial minor faults: %lu\n", task->min_flt);
	pr_info("Initial major faults: %lu\n", task->maj_flt);
	pr_info("Overall page faults: %lu\n", task->min_flt + task->maj_flt);
	return (0);
}

static void __exit	pagefault_counter_exit(void)
{
	pr_info("Page fault counter module exited.\n");
}

MODULE_LICENSE("GPL");

module_init(pagefault_counter_init);
module_exit(pagefault_counter_exit);
