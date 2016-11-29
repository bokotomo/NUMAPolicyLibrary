#include <stdio.h>
#include <numa.h>
#include <numaif.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"

int main(void)
{
	int nd;
	unsigned long nodemask;
	struct bitmask *mask;
	
	test();
	
  if(numa_available() == 0){
    puts("numaが使用できます。");
  }else{
    puts("numaは使用できません。");
    exit(0);
  }
  
  numa_set_bind_policy(2);
  
  printf("使用できるコア数は%d\n", numa_num_task_cpus());
  printf("ノード数は%d\n", numa_num_task_nodes());

  printf("numa_max_possible_node is %d\n", numa_max_possible_node());
  printf("numa_num_possible_nodes is %d\n", numa_num_possible_nodes());
  printf("numa_max_node is %d\n", numa_max_node());
  printf("numa_num_configured_nodes is %d\n", numa_num_configured_nodes());
  printf("numa_num_configured_cpus is %d\n", numa_num_configured_cpus());
  printf("numa_preferred is %d\n", numa_preferred());
  printf("numa_run_on_node is %d\n", numa_run_on_node(1));

  printf("numa_num_possible_cpus is %d\n", numa_num_possible_cpus());
  printf("numa_node_of_cpu is %d\n", numa_node_of_cpu(0));

	getMemoryNode();
	getCPUAllocate();
  getCPUDistance();
  
	return 0;
}