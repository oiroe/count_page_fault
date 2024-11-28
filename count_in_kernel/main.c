#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/pid.h>

static int pid = -1; // Process ID to monitor
module_param(pid, int, 0);
MODULE_PARM_DESC(pid, "Process ID to monitor page faults");

static struct task_struct *task;

static int __init pagefault_counter_init(void)
{
    // Validate input PID
    if (pid <= 0) {
        pr_err("Invalid PID: %d\n", pid);
        return -EINVAL;
    }

    // Find the task_struct for the given PID
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (!task) {
        pr_err("No process found with PID %d\n", pid);
        return -ESRCH;
    }

    // Print initial page fault counts
    pr_info("Monitoring process PID %d (%s)\n", pid, task->comm);
    pr_info("Initial minor faults: %lu\n", task->min_flt);
    pr_info("Initial major faults: %lu\n", task->maj_flt);

    return 0;
}

static void __exit pagefault_counter_exit(void)
{
    if (task) {
        // Display the final page fault counts
        pr_info("Final minor faults for PID %d: %lu\n", pid, task->min_flt);
        pr_info("Final major faults for PID %d: %lu\n", pid, task->maj_flt);
    } else {
        pr_info("No valid process to monitor at exit.\n");
    }

    pr_info("Page fault counter module exited.\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel module to count page faults of a process");
MODULE_VERSION("1.0");

module_init(pagefault_counter_init);
module_exit(pagefault_counter_exit);
