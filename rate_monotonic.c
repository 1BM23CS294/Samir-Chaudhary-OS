#include<stdio.h>

typedef struct process{
    int id;
    int bT;
    int period;
    int remT;
    int arrT;
}p;


void insert(p* arr,int n){
    for(int i=0;i<n;i++){
        scanf("%d %d %d",&arr[i].id,&arr[i].bT,&arr[i].period);
    }
}

void sort(p* arr, int n){
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i].period>arr[j].period){
                p temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void rate_monotonic(p *arr, int n, int timel) {
    int time = 0;
    int completed =0; 

    for (int i = 0; i < n; i++) {
        arr[i].remT = arr[i].bT;       
        arr[i].arrT = 0;                   
    }

    printf("\nGantt Chart:\n|");
    
    while (time < timel) {
        int highest_priority = -1;  
        

        for (int i = 0; i < n; i++) {

            if (arr[i].remT > 0 && time >= arr[i].arrT) {
                if (highest_priority == -1 || 
                    arr[i].period < arr[highest_priority].period) {
                    highest_priority = i;
                }
            }
        }

        if (highest_priority != -1) {
            printf(" P%d ", arr[highest_priority].id);
            arr[highest_priority].remT--;
            
            if (arr[highest_priority].remT == 0) {
                completed++;

                arr[highest_priority].arrT += arr[highest_priority].period;

                arr[highest_priority].remT = arr[highest_priority].bT;
            }
        } else {
            printf(" Idle ");
        }
        time++;
    }
    printf("|\n");

    printf("\nProcess Completion Status:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: Completed %d \n", 
               arr[i].id);
    }
}
int main() {
    int n, timel;
    p *arr;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    arr[n];
    insert(arr, n);
    sort(arr, n);

    printf("Enter the simulation time: ");
    scanf("%d", &timel);

    rate_monotonic(arr, n, timel);
    free(arr);

    return 0;
}
