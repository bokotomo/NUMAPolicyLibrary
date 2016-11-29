
void test(){
  
}

void getMemoryNode(){
	char *man = numa_alloc(1000);
  *man = 0;
	if (get_mempolicy(&nd, NULL, 0, man, MPOL_F_NODE|MPOL_F_ADDR) < 0){
		perror("get_mempolicy");
	}else{
		printf("my memorynode %d\n", nd); 
	}
}

//CPUに割り振られたのコアの表示
void getCPUAllocate(){
  int i, k, w, ncpus;
	struct bitmask *cpus;
	int maxnode = numa_num_configured_nodes()-1;

  puts("CPUAllocate ------------");
	cpus = numa_allocate_cpumask();
	ncpus = cpus->size;

	for (i = 0; i <= maxnode ; i++) {
		if (numa_node_to_cpus(i, cpus) < 0) {
			printf("node %d failed to convert\n",i); 
		}		
		printf("%d: ", i); 
		w = 0;
		for (k = 0; k < ncpus; k++)
			if (numa_bitmask_isbitset(cpus, k))
				printf(" %s%d", w>0?",":"", k);
		putchar('\n');		
	}
}

//距離の表示
void getCPUDistance(){
	int numnodes, a, b;

  puts("CPUDistance ------------");
  numnodes = numa_num_configured_nodes();
	for (a = 0; a < numnodes; a++) { 
		printf("%d: ", a); 
		if (numa_distance(a, a) != 10) { 
			printf("%d: self distance is not 10 (%d)\n", 
			       a, numa_distance(a,a));
			exit(1);
		}
		for (b = 0; b < numnodes; b++) { 
			int d1 = numa_distance(a, b); 
			int d2 = numa_distance(b, a);
			printf("%02d ", d1);
			if (d1 != d2) {
				printf("\n(%d,%d)->(%d,%d) wrong!\n",a,b,d1,d2); 
				exit(1);
			}
		}
		printf("\n");
	} 
}