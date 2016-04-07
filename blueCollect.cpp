#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <iomanip>
#include <vector>

using namespace std;

int main()
{
	FILE *in1;
	int i = 0;
	char buff[1024];
	char tmp[1024];
	//Initial Connect to bind transfer
	system("hcitool lecc B4:99:4C:6C:15:51");
	sleep(3); 
	//Writing for gatt protocol to have registers transmit data
	//Change --value= 11 for Pressure, 12 for IMU, 13 for Pressure + IMU
	if(!(in1 = popen("gatttool -b B4:99:4C:6C:15:51 --char-write-req --handle 0x0025 --value=13 --listen", "r")))
    {
        return -1;
    }
    while(fgets(buff, sizeof(buff), in1)!=NULL)
    {
        //Deleting Unnecessary components of 
        string str(buff);
        str.erase (0,36);
        //Uncomment the following lines if you just want pure characters to be printed out.
        //You can access each character by tmp[i], i being the index of the character array.
   //   strcpy(tmp, str.c_str()); 
   //   cout << tmp ;
        istringstream hex_chars_stream(str);
   //   vector<unsigned char> bytes;
        unsigned int c;
	    while (hex_chars_stream >> hex >> c)
		{
   //   	//bytes.push_back(c);
		 	cout<<c<<" ";
		 	//TODO: Parse and Convert hex data set as per requirement.
		}
		cout<<"Transmission ends \n\n"<<endl;
    }
    pclose(in1);
	return 0;
}