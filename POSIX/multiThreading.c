#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <pthread.h>

int avg, max, min;

struct Parameters {
    int* arr;
    int size;
};


void *calculateAvg(void *var){
    struct Parameters* data = (struct Parameters* )var;
    int sum = 0;
    for(int i = 0; i< data->size; i++){
        sum = sum + data->arr[i];
    }
    avg = sum/data->size;
}

void *calculateMax(void *var){
    struct Parameters* data = (struct Parameters* )var;
    int max_temp = data->arr[0];
    for(int i = 1; i< data->size; i++){
        if(data->arr[i] >= max_temp){
            max_temp = data->arr[i];
        }
    }
    max = max_temp;
}

void *calculateMin(void *var){
    struct Parameters* data = (struct Parameters* )var;
    int min_temp = data->arr[0];
    for(int i = 1; i< data->size; i++){
        if(data->arr[i] <= min_temp){
            min_temp = data->arr[i];
        }
    }
    min = min_temp;
}

int main(int count, char** args){
    struct Parameters params;
    int arr[10];
    if(count == 1){
        printf("No arguments supplied\n");
        return 1;
    }
    for(int i = 0; i<count-1; i++){
        arr[i] = atoi(args[i+1]);
    };
    params.arr = arr;
    params.size = count-1;
    pthread_t id;
    pthread_create(&id, NULL, calculateAvg, (void*) &params);
    pthread_create(&id, NULL, calculateMin, (void*) &params);
    pthread_create(&id, NULL, calculateMax, (void*) &params);
    pthread_join(id, NULL);
    printf("The average is:- %d\n", avg);
    printf("The max is:- %d\n", max);
    printf("The min is:- %d\n", min);
    return 0;
}