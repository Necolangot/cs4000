#include <iostream>
#include <omp.h>
void Test(){
	#pragma omp critical 
	{
		int id = omp_get_thread_num();
		int total = omp_get_num_threads();
		std::cout<<"Hello from thread "<< id <<std::endl;
		std::cout<<"This is Daniel Lubuguin's first parallel program"<<std::endl;
		std::cout<<"There are currently " << total << " threads" <<std::endl<<std::endl;
	}
}

int main(){
#pragma omp parallel
{
	Test();
}
}

