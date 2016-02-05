#include <stdio.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/minmax.hpp>
#include <boost/tuple/tuple.hpp>

#define ALLOWEDBYTES 200000000 //hey how much did they say you could download||limited download size...set it there

using namespace std;
using namespace boost::algorithm;
using namespace boost::tuples;



void download(int parts,int arr[],int endarr[],string url);
void breaker(string url);
int checkfile();

FILE *in;
string url;
char buff[512]; 


int main(int argc , char *argv[])
{
	printf("Enter download url :");
	cin >> url;
	checkfile();	
}

int checkfile()
{
	
    string cmd("curl -Is \"");
	cmd += url;
	cmd += "\" | egrep \"HTTP|Content-Length\"";
		
	//int result = system(cmd.c_str());
	if(!(in = popen(cmd.c_str(),"r"))){
		return 1;	
	}

	while(fgets(buff,sizeof(buff),in) != NULL){
	bool check1 = contains(buff,"200");
	bool check2 = contains(buff,"Content-Length");
	if (check2 == true )/*check for 200 ok then moves on*/
	{
		cout<<" Correct URL \n";
		breaker(url);

	}
	else if(check1 ==false)
	{
		
		cout << buff; /*Print out error why couldnt connect*/
		exit(0);
	}
	
	}
   
	pclose(in);
	
   
}

void breaker(string url)
{
	string str(buff);
   	boost::regex re("[*0-9*]");
	boost::sregex_iterator m1(str.begin(), str.end(),re);
	boost::sregex_iterator m2;
	std::stringstream      ss;

	while (m1 != m2)
	{
      ss << *m1++;
	}
	int num = -1;
	ss >> num;

	cout << "Size = " << num << endl;

	int remainingbytes = num % ALLOWEDBYTES;
	cout << remainingbytes << "\n";
	int bytesofinterest = num - remainingbytes;
	int test = 0;
	int byte = ALLOWEDBYTES - 1;
	int arraysize = bytesofinterest / ALLOWEDBYTES;
	int arr[arraysize - 1];
	int endarr[arraysize-1];
	//arr[0]= 0;/*make first array element zero for curl --range start with 0"*/
	int a,b;
	a = -1;
	/*lol from here its algorithm..yh thats my explanation */
	for(int i = 0 ; i < arraysize;i++)
	{
		b = a + 1;
		arr[i] = b ;
		a = b + byte;
		endarr[i] = a;
		
	}
	for(int i = 0 ; i < arraysize;i++)
	{
		cout <<arr[i] << "\n";		
	   
	}

	for(int i = 0 ; i < arraysize;i++)
	{
		cout <<endarr[i] << "\n";		
	   
	}

	download(arraysize,arr,endarr,url);
}


void download(int parts,int arr[],int endarr[],string url)
{
	string cmd = "curl --range ";
	string append = " & ";
	string cmd2 = " -o ";
	string name;
	cout<<"Name for your file[No Spaces Please] :";
	cin >> name;
	string nameparts[parts],lastname[1];
	string completebuiltcommand;
	for (int i= 0;i<parts;i++)
	{
		
		nameparts[i]=name+".part"+boost::lexical_cast<string>(i+1);
		if(i == parts -1)
		{
			lastname[0] = name+".part"+boost::lexical_cast<string>(parts+1);
		}
	}
	cout<<"File will be in part names like  ::";
	for (int i= 0;i<parts;i++)
	{
		cout<<nameparts[i]<<" ";
	}
	for (int i = 0 ;i < parts ; i++)
	{
		completebuiltcommand += cmd+boost::lexical_cast<string>(arr[i])+"-"+boost::lexical_cast<string>(endarr[i])+cmd2+boost::lexical_cast<string>(nameparts[i])+" "+url+append;
	}

	int c = parts -1;
	int b = endarr[c];
	int a = b + 1; //sets value so u can download from last bytes to end.
	int e = sizeof(nameparts);
	string desiredname;
	

	
	string run = completebuiltcommand+cmd+boost::lexical_cast<string>(a)+ "-"+cmd2+boost::lexical_cast<string>(lastname[0])+" "+url;
	
	cout<<"Here we go :) you could copy and paste for later :) " +run;
	cout<<"\n\n\n\nWhat will you like to be filename at the end[again no spaces]:: ";
	cin>>desiredname;
	string concatenate = "cat "+name+".part? >"+desiredname; 

	FILE *stream,*stream2;
	
	char buffer[512],buffer2[512];//modify if you think u dont waste memory
	if(!(stream = popen(run.c_str(),"r"))){
			
	}
	while(fgets(buffer,sizeof(buff),in) != NULL){
		cout<<buffer;	
	}
	
	pclose(stream);
	if(!(stream2 = popen(concatenate.c_str(),"r"))){
			
	}
	while(fgets(buffer2,sizeof(buff),in) != NULL){
		cout<<buffer2;	
	}
	pclose(stream2);
	cout<<"Done...See..File limit Set by proxy servers like squid and etc sucks....rules sucks";
    cout<<"Wait till you dont see any curl progress in term";
	
}
