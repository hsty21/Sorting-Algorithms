#include<iostream>
#include<limits>
//swap function
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
//display function
void display(int arr[],int size){
    for(int i=0;i<size ;i++){
        std::cout<< arr[i] << "\t";
    }
    std::cout<< std::endl;
}
//validation function
int valid(int num){
    while(true){
        std::cin>>num;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout<< "Invalid input! please try again"<<std::endl;
        }
        else{
            return num;
        }
    }
}
//1.bubble sort
void bubbleSort(int arr[],int size){
    for(int i=0;i<size;i++){
        bool check = false;
        for(int j=0;j<size - 1;j++){
            if(arr[j] > arr[j + 1]){
                swap(&arr[j],&arr[j + 1]);
                check = true;
            }
        }
        if(check == false ){
            return;
        }
    }
}
//2.selection sort
void selectionSort(int arr[],int size){
    for(int i=0;i<size;i++){
        int min = i;
        for(int j = i +1;j<size;j++){
            if(arr[j] < arr[min]){
                min = j;
            }
        }
        if(min != i){
            swap(&arr[i],&arr[min]);
        }
    }
}
//3.insertion sort
void insertionSort(int arr[],int size){
    for(int i=1;i<size;i++){
        int  j =i -1;
        while(j>=0 && arr[j]<arr[j - 1]){
            swap(&arr[j],&arr[j - 1]);
            j--;
        }
    }
}
//4.mege sort
void merge(int arr[],int I,int m,int r){
    int i=I,j=m + 1 ,k = 0;
    int temp[r + 1];
    while(i<=m && j<=r){
        if(arr[i]<arr[j]){
            temp[k] = arr[i];
            i++;
            k++;
        }
        else{
            temp[k] = arr[j];
            j++;
            k++;
        }
    }
    while(i<=m){
        temp[k] = arr[i];
        i++;
        k++;
    }
    while(j<=r){
        temp[k] = arr[j];
        j++;
        k++;
    }
    int c = 0;
    for(int p = I;p<=r;p++){
        arr[p] = temp[c];
        c++;
    }
}
void mergeSort(int arr[],int i,int r){
    if(i<r){
        int m = (r + i)/2;
        mergeSort(arr,i,m);
        mergeSort(arr, m + 1,r);
        merge(arr,i,m,r);
    }
}
//5.quick sort
int partition(int arr[],int i ,int r){
    int pivot = arr[r];
    int pIdx = i;
    for(int j = i;j<r;j++){
        if(arr[j]<=pivot){
            swap(&arr[j],&arr[pIdx]);
            pIdx++;
        }
    }
    swap(&arr[pIdx],&arr[r]);
    return pIdx;
}
void quickSort(int arr[],int i,int r){
    if(i<r){
        int p = partition(arr,i,r);
        quickSort(arr,i,p - 1);
        quickSort(arr,p + 1,r);
    }
}
//6.counting sort
void countingSort(int arr[],int size){
    int range= arr[0];
    for(int i=0;i<size;i++){
        if(arr[i]>range){
            range = arr[i];
        }
    }
    int countSize = range + 1;
    int count[countSize];
    for(int i=0;i<countSize;i++){
        count[i] = 0;
    }
    for(int i=0;i<size;i++){
        count[arr[i]]++;
    }
    //make sure that the index doesnt go out of bound 
    for(int i=1;i<countSize;i++){
        count[i] = count[i] + count[i - 1];
    }
    int output[size];
    for(int i= 0;i<size;i++){
        output[--count[arr[i]]] = arr[i];
    }
    for(int i=0;i<size;i++){
        arr[i] = output[i];
    }
}
//7.adaptive counting sort
void adaptiveCountingSort(int arr[],int size){
    int range = arr[0];
    for(int i=0;i<size;i++){
        if(arr[i]>range){
            range = arr[i];
        }
    }
    int count[range + 1];
    for(int i=0;i<range + 1;i++){
        count[i] = 0;
    }
    for(int i=0;i<size;i++){
        count[arr[i]]++;
    }
    int c =0;
    for(int i=0;i<range + 1;i++){
        while(count[i]>0){
            arr[c] = i;
            count[i]--;
            c++;
        }
    }
}
//8.radix sort
class Node{
    public:
        int data;
        Node* next;
        Node(){
            data = 0;
            next = nullptr;
        }
};
class queue{
    public:
        Node* head;
        queue(){
            head = nullptr;
        }
        bool isEmpty(){
            if(head == nullptr){
                return true;
            }
            return false;
        }
        void enqueue(Node* n){
            Node* temp = head;
            if(temp == nullptr){
                head = n;
                n->next = nullptr;
            }
            else{
                while(temp->next!=nullptr){
                    temp = temp->next;
                }
                temp->next = n;
                n->next = nullptr;
            }
        }
        int dequeue(){
            Node* temp = head;
            if(head == nullptr){
                return  -1;
            }
            else{
                head = head->next;
            }
            int data = temp->data;
            delete temp;
            return data;
        }
};
void radixSort(int arr[],int size){
    int max = arr[0];
    queue Q[10];
    for(int i=0;i<size;i++){
        if(max<arr[i]){
            max = arr[i];
        }
    }
    int count = 0;
    while(max>0){
        max = max /10;
        count++;
    }
    for(int i=1;i<=count;i++){
        for(int j =0;j<size;j++){
            int temp = arr[j];
            int remain;
            int k = i;
            while(k>0){
                remain = temp % 10;
                temp =  temp/10;
                k--;
            }
            Node* n = new Node();
            n->data = arr[j];
            Q[remain].enqueue(n);
        }
        int k =0;
        for(int j =0;j<10;j++){
            while(!Q[j].isEmpty()){
                arr[k] = Q[j].dequeue();
                k++;
            }
        }
    }
}
//9.shell sort
void shellSort(int arr[],int size){
    for(int gap = size/ 2;gap>0;gap = gap/2){
        for(int  j= gap;j<size;j++){
            int temp = arr[j];
            int i;
            for(i = j;i>=gap && arr[i-gap]>temp;i= i - gap){
                arr[i]=  arr[i - gap];
            }
            arr[i]=temp;
        }
    }
}
//10.adaptive shell sort
void adaptiveShellSort(int arr[],int size){
    int gap = size/2;
    int i = gap,j= i + gap,k = i - gap;
    while(gap>0){
        while(i<size){
            if(j>=0 && j<size){
                if(arr[i] > arr[j]){
                    swap(&arr[i],&arr[j]);
                }
            }
            if(k>=0 && k<size){
                if(arr[i]<arr[k]){
                    swap(&arr[i],&arr[k]);
                }
            }
            i++;
            k = i - gap;
            j = i + gap;
        }
        i = 0;
        gap = gap / 2;
        k = i - gap;
        j = i + gap;
    }
}
int main(){
    srand(time(NULL));
    const int size = 10;
    int arr[size];
    int op;
    bool leave = false;
    while(leave == false){
        for(int i=0;i<size;i++){
            arr[i] = rand()%100;
        }
        std::cout<< "1.Bubble sort\n2.Selection Sort\n3.Insertion Sort\n4.Merge Sort\n5.Quick Sort\n6.Counting Sort\n7.Adaptive Quick Sort\n8.Radix Sort\n9.Shell Sort\n10.Adaptive Shell Sort\n11.Exit"<<std::endl;
        std::cout<< "Enter the number of operation: ";
        op = valid(op);
        while(op>11 || op<1){
            std::cout<< "Invalid operation number! Please try again"<<std::endl;
            op = valid(op);
        }
        std::cout<< "Original Array:"<<std::endl;
        display(arr,size);
        std::cout<< "Oraganized Array:"<<std::endl;
        switch(op){
            case 1:
                bubbleSort(arr,size);
                display(arr,size);
                break;
            case 2:
                selectionSort(arr,size);
                display(arr,size);
                break;
            case 3:
                insertionSort(arr,size);
                display(arr,size);
                break;
            case 4:
                mergeSort(arr,0,size - 1);
                display(arr,size);
                break;
            case 5:
                quickSort(arr,0,size - 1);
                display(arr,size);
                break;
            case 6:
                countingSort(arr,size);
                display(arr,size);
                break;
            case 7:
                adaptiveCountingSort(arr,size);
                display(arr,size);
                break;
            case 8:
                radixSort(arr,size);
                display(arr,size);
                break;
            case 9:
                shellSort(arr,size);
                display(arr,size);
                break;
            case 10:
                adaptiveShellSort(arr,size);
                display(arr,size);
                break;
            case 11:
                leave = true;
                std::cout<< "Bye!"<<std::endl;
                break;
        }
    }
    return 0;
}
    
    