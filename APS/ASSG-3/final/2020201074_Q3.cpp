#include<bits/stdc++.h>
using namespace std;

struct Heap
{
	long long int *arr;
	long long int count;
	long long int capacity, heap_type;
	long long int *fileIdx;
};
typedef Heap heap;

heap* createHeap(long long int size, long long int type)
{
	heap *h=(heap*)malloc(sizeof(heap));
	if(h==NULL)
	{
		cout<<"memory error"<<endl;
		return NULL;
	}	
	h->heap_type=type;
	h->count=0;
	h->capacity=size;
	h->arr=(long long int*)malloc(sizeof(long long int) * h->capacity);
	if(h->arr == NULL)
	{
		cout<<"memory error"<<endl;
		return NULL;
	}
	h->fileIdx=(long long int*)malloc(sizeof(long long int) * h->capacity);
	if(h->fileIdx == NULL)
	{
		cout<<"memory error"<<endl;
		return NULL;
	}
	return h;
}

int parent(heap *h, long long int i)
{
	if(i<=0 || i>=h->count)
		return -1;
	return (i-1)/2;
}

int leftChild(heap *h, long long int i)
{
	long long int left=2*i+1;
	if(left>=h->count)
		return -1;
	return left;
}

int rightChild(heap *h, long long int i)
{
	long long int right=2*i+2;
	if(right>=h->count)
		return -1;
	return right;
}

void percolateDown(heap *h, long long int i)
{
	long long int left,right,tmp,max1;
	left=leftChild( h, i);
	right=rightChild( h, i);
	if(left != -1 && h->arr[left] < h->arr[i])
		max1=left;
	else
		max1=i;
	if(right!=-1 && h->arr[right] < h->arr[max1])  	// replace > with <  sign
		max1=right;
	if(max1 != i)
	{
		tmp=h->arr[i];
		h->arr[i]=h->arr[max1];
		h->arr[max1]=tmp;

		tmp=h->fileIdx[i];
		h->fileIdx[i]=h->fileIdx[max1];
		h->fileIdx[max1]=tmp;	
		
		percolateDown(h,max1);
	}
}

void buildHeap(heap *h, long long int a[], long long int n, long long int idx[])
{
	long long int i;
	if(h==NULL)
		return;
	for(i=0;i<n;i++){
		h->arr[i] = a[i];
		h->fileIdx[i] = idx[i];
	}
	h->count = n;
	for(i = (n-1)/2; i >= 0; i--)
		percolateDown(h, i);
}

int deleteMIn(heap *h)
{
	long long int data;
	if(h->count == 0)
		return -1;
	data=h->arr[0];
	h->arr[0]=h->arr[(h->count)-1];
	h->fileIdx[0]=h->fileIdx[(h->count)-1];
	h->count--;
	percolateDown(h,0);
	return data;
}

void merge(long long int arr[], long long int low, long long int high, long long int mid){
    long long int len1, len2, i ,j, k;
    len1= mid-low+1;
    len2=high-mid;
    long long int left[len1], right[len2];
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


void mergeSort(long long int arr[], long long int low, long long int high){
    if(low<high){
        long long int mid=low+(high-low)/2;
        mergeSort(arr,low, mid);
        mergeSort(arr, mid+1, high);
        merge(arr,low, high, mid);
    }
}

void solve(int partitions, int size, char input_file[]){
    //FILE* in = fopen("input.txt", "r"); 
    FILE* in = fopen(input_file, "r");
    string filename;
    long long int arr[size];
    long long int i, j, k=0;
    char outFile[100];
    while(k< partitions){
        for (i = 0; i < size; i++){
                if (fscanf(in, "%lld,", &arr[i]) != 1)
                    break;
        } 
        
        mergeSort(arr,0,size-1);
        filename=to_string(k)+".txt";
        strcpy(outFile, filename.c_str());
        FILE* out=fopen(outFile, "w");
        for(j=0;j<size;j++){
            fprintf(out, "%lld,", arr[j]);    
        }
        fclose(out);
        k++;
    }
}

void mergeFiles(long long int partitions, long long int size, char output_file[]){
	FILE *out[partitions], *output;
	string filename;
	char file[200];
	long long int i;
	for(i=0;i<partitions;i++){
		filename=to_string(i)+".txt";
		strcpy(file, filename.c_str());
		out[i]=fopen(file, "r");
	}
	//output=fopen("output.txt","w");
	output=fopen(output_file,"w");
	heap *heap;
	heap = createHeap(size,0);
	long long int arr[size], index[size];
	for(i=0;i<partitions;i++){
		if (fscanf(out[i], "%lld,", &arr[i]) != 1) 
            break;
        index[i]=i;
	}
	buildHeap(heap, arr, partitions, index);
	/*for(i=0;i<partitions;i++)
		cout<<heap->arr[i]<<","<<heap->fileIdx[i]<<"  ";
	cout<<endl;*/
	long long int tmp=partitions;
	long long int j=0;
	while(j<size*partitions){
		fprintf(output, "%lld,", heap->arr[0]);
		long long int idx=heap->fileIdx[0];
		if (fscanf(out[heap->fileIdx[0]], "%lld,", 
                   &heap->arr[0]) != 1) { 
            heap->arr[0] = INT_MAX;
            heap->fileIdx[0] = INT_MAX; 
            //partitions--; 
        } 
        else{
        	heap->fileIdx[0]=idx;
        }
        percolateDown(heap,0);
        /*for(i=0;i<tmp;i++)
			cout<<heap->arr[i]<<","<<heap->fileIdx[i]<<"  ";
		cout<<endl;*/
		//cout<<partitions<<endl;
		j++;
	}
	for(i=0;i<tmp;i++)
		fclose(out[i]);
	fclose(output);
}

int main(int argc, char *argv[])
{
    long long int partitions, size;
    cin>>partitions>>size;
    //time_t start, end;
    //time(&start);
    solve(partitions, size, argv[1]);
    mergeFiles(partitions, size, argv[2]);
    /*time(&end); 
    double time_taken = double(end - start); 
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5); 
    cout << " sec " << endl;*/
 	return 1;
}
