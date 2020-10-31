#include<bits/stdc++.h>
using namespace std;

int main()
{
	/*ofstream stream;
	stream.open("saveName.js");
	if( !stream ){
        cout << "Opening file failed" << endl;
        exit(0);
    }*/

	ifstream myFile;
	myFile.open("Script.js");
    int i=0, n=15;
    char A[20];
    while(n--){
		myFile.seekg(i); //, ios::beg
		i+=20; 
		myFile.read(A, 20);
		string str(A);
		cout << A << endl;
		//stream << A;
		cout<<"----------\n";
	}     
    myFile.close();


	/*FILE *fp; 
    fp = fopen("Script.js", "r"); 
    unsigned char input[20];
    // Moving pointer to end 
    fseek(fp, 20, SEEK_SET); 
    seekg(20, fp);
    cout<<input<<endl;
    // Printing position of pointer 
    printf("%ld", ftell(fp)); 	*/
	return 0;
}