// Parallel dot product implementation, example of race condition and use of an atomic type
#include <iostream>
#include <thread>
#include <vector>

//Split "mem" into "parts", e.g. if mem = 10 and parts = 4 you will have: 0,2,4,6,10
//if possible the function will split mem into equal chuncks, if not 
//the last chunck will be slightly larger


#include <atomic>

std::vector<int> bounds(int parts, int mem) {
	std::vector<int>bnd;
	int delta = mem / parts;
	int reminder = mem % parts;
	int N1 = 0, N2 = 0;
	bnd.push_back(N1);
	for (int i = 0; i < parts; ++i) {
		N2 = N1 + delta;
		if (i == parts - 1)
			N2 += reminder;
		bnd.push_back(N2);
		N1 = N2;
	}
	return bnd;
}

void dot_product(const std::vector<int> &v1, const std::vector<int> &v2, std::atomic<int> &result, int L, int R){
	int partial_sum = 0;
	for (int i = L; i < R; ++i){
		partial_sum += v1[i] * v2[i];
	}
	result += partial_sum;
}

int main(){
	int nr_elements = 100000;
	int nr_threads = 4;
	std::atomic<int> result(0);
	std::vector<std::thread> threads;

	//Fill two vectors with some values 
	std::vector<int> v1(nr_elements, 1), v2(nr_elements, 2);

	//Split nr_elements into nr_threads parts
	std::vector<int> limits = bounds(nr_threads, nr_elements);

	//Launch nr_threads threads:
	for (int i = 0; i < nr_threads; ++i) {
		threads.push_back(std::thread(dot_product, std::ref(v1), std::ref(v2), std::ref(result), limits[i], limits[i + 1]));
	}


	//Join the threads with the main thread
	for (auto &t : threads){
		t.join();
	}

	//Print the result
	std::cout << result << std::endl;

	return 0;
}

/*
#include <mutex>

static std::mutex barrier;
static const int num_threads = 10;

void call_from_thread() {
	printf("Hello, World!");
}

void call_from_thread_param(int tid) {
	printf("Thread %u says, 'Hello, World!'\n", tid);
	std::lock_guard<std::mutex> block_threads_until_finish_this_job(barrier);
}

int main() {
	char single_thread;
	char simulate;
	do {
		char simulate;
		printf("Simulate a single thread? (y/n)\n");
		scanf("%c", &single_thread);

		if (single_thread ='y'){
			std::thread t1(call_from_thread);

			t1.join();
		} else {
			std::thread t[num_threads];

			for (int i = 0; i < num_threads; ++i)
			{
				t[i] = std::thread(call_from_thread_param, i);
			}

			printf("Thread main says, 'Hello, World'\n");

			for (int i = 0; i < num_threads; ++i)
			{
				t[i].join();
			}
		}

		printf("Would you like to simulate again? (y/n)\n");
		scanf("%c", &simulate);
	} while (simulate == 'y');

	return 0;
}*/