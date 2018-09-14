// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " " 
	   << (*ipD)->val2 << " " 
	   << (*ipD)->val3 << " " 
	   << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }
    
  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

int size;
Data* output1[127][1000000];
Data* input[1100000];

bool compFirst(Data * &a, Data * &b);
bool val4Comp(Data *&, Data &);
void insertionSort(vector<Data *> &);
void insertionSort2(list<Data *> &l);
void whySortC(vector<Data *> &v);
void countSort(vector<Data *> &v, int e);
void countSortC(vector<Data *> &v);
void radixSort( vector<Data *> &v);
void betterWhySort(list<Data *> &l);
void stringSort( vector<Data *> &v);
void stringSort2( list<Data *> &l);
void col2Sort( list<Data *> &l);


//void insertionSort(list<Data *> &);

// You may add global variables, functions, and/or
// class defintions here if you wish.

void sortDataList(list<Data *> &l, int field) {
	size = l.size();	
	switch(field)
	{
		case 1:
		      //radixSort( v );
		      //insertionSort( v );
		      insertionSort2( l );
		      //l.sort(compFirst);
		      //insertionSort( l );
		      break;
		case 2:
			col2Sort( l );
		      break;
		case 3:
		      //whySortC( v );
		      betterWhySort( l );
		      break;
		case 4:
		      stringSort2( l );	
		      //stringSort( v );
		      break;

	}		
}
void insertionSort2(list<Data *> &l)
{
	list<Data *>::iterator it=l.begin();

	int i, j, k=0;
	do
	{
		input[k]=*it;
		it++;
		k++;
	}
	while(it!=l.end());
	
	Data *key;
	for(i = 1; i < size; i++)
	{
		key = input[i];
		j = i-1;
		
		while(j >= 0 && input[j]->val1>key->val1)
		{
			input[j+1] = input[j];
			j--;
		}
		input[j+1]=key;
	}
	
	it=l.begin();
	for(k =0; k<size; k++)
	{
		*it=input[k];
		it++;
	}
}

void insertionSort(vector<Data *> &v)
{
	int i, j;

	Data *key;
	for(i = 1; i < size; i++)
	{
		key = v[i];
		j = i-1;

		while(j >= 0 && v[j]->val1>key->val1)
		{
			v[j+1] = v[j];
			j--;
		}
		v[j+1]=key;
	}
}

void col2Sort( list<Data *> &l)
{
		
	int count[127]={0};
	list<Data *>::iterator it=l.begin();
/*
	while( it !=l.end())
	{
		int ic =(*it)->val4[2];
		output1[ic][count[ic]]=*it;
		count[ic]++;
		it++;
	}
*/
	int k=0;
	do
	{
		input[k]=*it;
		it++;
		k++;
	}
	while(it!=l.end());
/*

	int index = 0;

	for(int i=0; i < 127; i++)
	{	
		for(int j = 0; j < count[i]; j++)
		{
			input[index]=output1[i][j];
			index++;
		}
	}
	*/
	for( unsigned int e = 100000; e<=1000000000 ; e *= 10)
	{
		int count1[127]={0};
		for(int i=0; i<size; i++)
		{
			unsigned int ic = ((input[i]->val2)/e)%10;
			output1[ic][count1[ic]]=input[i];
			count1[ic]++;

		}

		int index1 = 0;
		for(int i=0; i< 127; i++)
		{
			for(int j = 0; j < count1[i]; j++)
			{
				input[index1]=output1[i][j];
				index1++;
			}
		}
	}

	
	int i, j;
	Data *key;
	for(i = 1; i < size; i++)
	{
		key = input[i];
		j = i-1;
		
		while(j >= 0 && input[j]->val2>key->val2)
		{
			input[j+1] = input[j];
			j--;
		}
		input[j+1]=key;	
	}

	
	it=l.begin();

	for(int i =0; i < size; i++)
	{
		*it=input[i];
		it++;
	}
}

void stringSort2( list<Data *> &l)
{
		
	int count[127]={0};
	list<Data *>::iterator it=l.begin();
/*
	while( it !=l.end())
	{
		int ic =(*it)->val4[2];
		output1[ic][count[ic]]=*it;
		count[ic]++;
		it++;
	}
*/
	int k=0;
	do
	{
		input[k]=*it;
		it++;
		k++;
	}
	while(it!=l.end());
/*

	int index = 0;

	for(int i=0; i < 127; i++)
	{	
		for(int j = 0; j < count[i]; j++)
		{
			input[index]=output1[i][j];
			index++;
		}
	}
*/	
	for(int pos=2;pos >=0; --pos)
	{
		int count1[127]={0};
		for(int i=0; i<size; i++)
		{
			int ic = input[i]->val4[pos];
			output1[ic][count1[ic]]=input[i];
			count1[ic]++;

		}

		int index1 = 0;
		for(int i=0; i< 127; i++)
		{
			for(int j = 0; j < count1[i]; j++)
			{
				input[index1]=output1[i][j];
				index1++;
			}
		}
	}

	
	int i, j;
	Data *key;
	for(i = 1; i < size; i++)
	{
		key = input[i];
		j = i-1;
		
		while(j >= 0 && input[j]->val4>key->val4)
		{
			input[j+1] = input[j];
			j--;
		}
		input[j+1]=key;	
	}

	
	it=l.begin();

	for(int i =0; i < size; i++)
	{
		*it=input[i];
		it++;
	}
}

bool val4Comp(Data * &a, Data * &b) { return a->val4 < b->val4; }
/*
void stringSort( vector<Data *> &v)
{
	vector<Data *> output(size);
	*for( int pos = 25-1; pos >= 0; --pos )
	{
		for(int i = 0; i < size; i++)
		{
			int ic = v[i]->val4[pos];
			b[ic].push_back(v[i]);
		}
		int index = 0;
		for(int i = 0; i < 257; i++)
			for(int j = 0; j < b[i].size(); j++)
				v[index++] = b[i][j];
	
	/

	vector<Data *> *in= &v;
	vector<Data *> *out = &output;

	for( int pos = 25-1; pos >= 0; --pos)
	{
		vector<int> count(257);

		for(int i = 0; i< size; ++i )
			++count[ (*in)[i]->val4[pos] + 1 ];

		for(int b = 1; b <= 256; ++b )
			count[ b ] += count[ b - 1 ];

		for( int i = 0; i < size; ++i )
			(*out)[ count[ (*in)[i]->val4[pos] ]++ ] = move( (*in)[i] );

		swap( in, out );
	}

	for( int i = 0; i < size; ++i )
		(*out)[i] = move( (*in)[i] );
}
*/
//ended here

void radixSort( vector<Data *> &v)
{
	int max = 1010010;
	cout<<size;
	for(int e = 1; max/e>0; e*=10)
		countSort(v,e);
}

void countSort(vector<Data *> &v, int e)
{

	int bucket[10]= {0};
		

	for(int i = 0; i < size; i++)
	{	
		bucket[(v[i]->val1 / e) % 10]++;
	}
	int index = size;
	for(int i=9; i>=0; i--)
	{
		index -= bucket[i];
		bucket[i] = index;
	}

	index = 0;
	vector<Data *> output(size);
	
	for(int i = 0; i < size; i++)
	{
		int digit = (v[i]->val1 / e) % 10;
		output[bucket[digit]] = v[i];
		bucket[digit]++;
	}

	for(int i=0; i<size; i++)
	{
		v[i]=output[i];
	}
	
}	




void betterWhySort(list<Data *> &l)
{
	int count[127]={0};
	list<Data *>::iterator it=l.begin();
	while( it !=l.end())
	{
		int ic =int((*it)->val3);
		output1[ic][count[ic]]=*it;
		count[ic]++;
		it++;
	}	
	
	it=l.begin();
	
	for(int i=0; i < 127; i++)
	{	
		for(int j = 0; j < count[i]; j++)
		{
			*it=output1[i][j];
			it++;
		}
	}
	
}



void whySortC(vector<Data *> &v)
{
	vector<vector<Data *> > b(127);
	for(int i = 0; i < size; i++)
	{
		int ic = v[i]->val3;
		b[ic].push_back(v[i]);
	}
	int index = 0;
	for(int i = 0; i < 127; i++)
		for(int j = 0; j < b[i].size(); j++)
			v[index++] = b[i][j];
}


void countSortC(vector<Data *> &v)
{

	int bucket[127]= {0};
	vector<Data *> output(size);

	for(int i = 0; i < size; i++)
	{
		int ic = v[i]->val3;	
		bucket[ic]++;
	}
	
	int index = size;
	for(int i=127; i>=0; i--)
	{
		index -= bucket[i];
		bucket[i] = index;
	}
	index = 0;
	
	cout<<"3";
	for(int i = 0; i < size; i++)
	{
		int ic = v[i]->val3;
		//output[bucket[ic]] = v[i];
		bucket[ic]++;
	}
/*
	for(int i=0; i<size; i++)
	{
		v[i]=output[i];
	}
	*/
}	


/*
void quickSort3( vector<Data *> &v, int low, int hi, int d)
{
	int i = low-1, j=hi,k,p=lo-1,q=hi,y=v[hi][d];
	if(hi <= low) 
		return;
	while(i<j)
	{
}}

void lsdR( vector<Data *> &v, int low, int high)
{
	int d;
	for(d = 25-1; d>=0; d--)
	{
	}
	vector<Data *> output;
	int count[257];

		for(int i = 0; i < 25;


void msdR( vector<Data *> &v, int low, int hi, int d)
{
	int i;
	int count[256+1] = {0};
	
	if(hi<=low)
		return;
	
	for(i=0; i<255;i++)
		msdR(v, low + count[i], low + count[i+1]-1, d+1);
}
*/


/*
void radixSortS( vector<Data *> &v)
{
	vector<vector<Data *>> words(26);
	vector<vector<string>> buckets(256);
	for( string s: z )
		words[ s.length() ].push_back(move(s));

	int id = 0;


void insertionSort(list<Data *> &l)
{
	int key;
	list<Data *>::iterator j=l.begin();
	for(list<Data *>::iterator it =l.begin(); it != l.end(); it++)
	{
		if(it==l.begin())
			continue;

		key = (*it)->val1;
		j = prev(it);
		do
		{
			(*(next(j)))->val1=(*j)->val1;
			j=prev(j);
		}
		while( j != l.begin() && (*j)->val1 > key);
		(*(next(j)))->val1=key;
	}
}
bool compFirst(Data * &a, Data * &b) { return a->val1 < b->val1; }

void radixSort(list<Data *> &l)
{
	int n = sizeof(l)/sizeof(Data);
	int m =4294967295;
       	
	for(int e =1; m/e > 0; e *= 10)
		countSort(l,n,e);
}

void countSort(list<Data *> &l, int n, int e)
{
	int output[n];
	int count[10] = {0};
	int bucket[10];

	for (list<Data *>::iterator it = l.begin(); it != l.end; it++)
	{
		count[ (((*it)->val2)/e)%10]++;
	}
	int index = l.size();
	
	for(int i=9; i>=0; i--)
	{
		index -+ bucket[i]
}

*/		
