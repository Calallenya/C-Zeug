#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
 * MADE FOR LINUX
 */

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}


long long int selection_sort(int *array, int size){
    int n, numbers_compared = 0, smallest_index = 0;

    for(int i = 0;i < size;i++){
        smallest_index = i;


        for(n = 1 + i;n < size ;n++) {
            if (array[n] < array[smallest_index]) {
                smallest_index = n;
            }
			numbers_compared += 1;
        }
        swap(&array[smallest_index], &array[i]);
    }
	return numbers_compared;
}


//Function to check if list is sorted from low to high 
int check(int *array, int size){
    int temp = array[0];
    for(int i = 1;i < size;i++){
        if(temp > array[i]){
            return 0;
        }
        temp = array[i];
    }
    return 1;
}


void print_list(int *array, int size){
	for(int i = 0;i < size;i++){
		printf("%d\n", array[i]);
	}
}


int main(){

	struct timeval tm;
	long long int x;

	//Size of array input
	int size;
	printf("Enter the amount of numbers to be generated\n");
	scanf("%d", &size);
	while(getchar() != '\n');
    int number_array[size];
	
	//Range of numbers to be generated input 
	int range;
	printf("\nEnter the range of numbers to be generated\n");
	scanf("%d", &range);	

    //Create random Seed
    time_t t = time(NULL);
    srand((unsigned int) t);

    //Fill array with random numbers
    for(int i = 0;i < size;i++){
        number_array[i] = (rand() % range) + 1;
    }


	printf("\nUnsorted list:\n");
	print_list(number_array, size);

	//Time function (LINUX)
	gettimeofday(&tm, NULL);
	double start = (double) (tm.tv_sec) + ((double) (tm.tv_usec))/1.0e6;

    x = selection_sort(number_array, size);
	
	gettimeofday(&tm, NULL);
	double duration = (double) (tm.tv_sec) + ((double) (tm.tv_usec))/1.0e6 - start;

	printf("\n\nSorted list:\n");
	print_list(number_array, size);

	printf("\nNumbers compared: %d", x);


    if (check(number_array, size) == 1){
		printf("\n\nList sorted correctly in %f Seconds\n", duration);
	} else{
		printf("\n\nList not sorted correctly in %f Seconds\n", duration);
	}
	
    return 0;
}
