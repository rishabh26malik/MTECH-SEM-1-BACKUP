#include<bits/stdc++.h>
using namespace std;

void merge(int arr[], int low, int high, int mid){
    //cout<<"in merge\n";
    int len1, len2, i ,j, k;
    len1= mid-low+1;
    len2=high-mid;
    int left[len1], right[len2];
    for(i=0; i<len1; i++){
        left[i]=arr[low+i];
    }
    for(i=0; i<len2; i++){
        right[i]=arr[mid+1+i];
    }
    i=j=0;
    k=low;
    while(i<len1 && j<len2){
        if(left[i] <= right[j]){
            arr[k]=left[i];
            i++;
        }
        else{
            arr[k]=right[j];
            j++;
        }
        k++;
    }
    while(i < len1){
        arr[k]=left[i];
        i++;
        k++;
    }
    while(j < len2){
        arr[k]=right[j];
        j++;
        k++;
    }
}


void mergeSort(int arr[], int low, int high){
    if(low<high){
        int mid=low+(high-low)/2;
        mergeSort(arr,low, mid);
        mergeSort(arr, mid+1, high);
        merge(arr,low, high, mid);
    }
}

void solve(int partitions, int size){
    FILE* in = fopen("input.txt", "r"); 
    string filename;
    int arr[size];
    int i, j, k=0;
    char outFile[100];
    while(k< partitions){
        for (i = 0; i < size; i++){
                if (fscanf(in, "%d,", &arr[i]) != 1)
                    break;
        } 
        //for(i=0;i<size;i++)
        //    cout<<arr[i]<<" ";
        cout<<"\n---------------------------------\n";
        
        //cout<<"2323\n";
        mergeSort(arr,0,size-1);
        //cout<<"aftre merge  "<<k<<endl;;
        //sort(arr,arr+100);
        filename=to_string(k)+".txt";
        strcpy(outFile, filename.c_str());
        FILE* out=fopen(outFile, "w");
        for(j=0;j<size;j++){
            cout<<arr[j]<<" ";
            fprintf(out, "%d,", arr[j]);    
        }
        fclose(out);
        k++;
    }
}


int main()
{
    int partitions, size;
    cin>>partitions>>size;
    solve(partitions, size);

    /*
    string filename;
    FILE* out[2]; 
    FILE* in = fopen("input.txt", "r"); 
    int arr[1000];
    for (int i = 0; i < 1000; i++){
            if (fscanf(in, "%d,", &arr[i]) != 1)
                break;
    } 
    sort(arr,arr+1000);
    mergeSort(arr,0,1000);
    for (int i = 0; i < 1000; i++){
        cout<<arr[i]<<" ";
      } 
    out[0]=fopen("0.txt", "w"); 
        
    for ( i = 0; i < 500; i++){ 
        //cout<<arr[i]<<" ";
        fprintf(out[0], "%d,", arr[i]);
    }
    fclose(out[0]);
    //k++;
    out[1]=fopen("1.txt", "w"); 
        
    for (; i < 1000; i++){ 
        fprintf(out[1], "%d,", arr[i]);   
        //cout<<arr[i]<<" ";
    }
    fclose(out[1]);*/
 	return 1;
}
