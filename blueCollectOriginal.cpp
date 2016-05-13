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
    FILE *in2;
	int i = 0;
    int index_Right = 3;
    int index_Left = 3;
    int pressIndex = 0;
    int pressureCount = 0;
    int pressures[47];
    char buff_Right[1024];
    char buff_Left[1024];
    char tmp_Right[1024];
    char tmp_Left[1024];
    char pressurePoint_Right[3];
    char pressurePoint_Left[3];
    char accelX_msb_Right[3];
    char accelX_lsb_Right[3];
    char accelY_msb_Right[3];
    char accelY_lsb_Right[3];
    char accelZ_msb_Right[3];
    char accelZ_lsb_Right[3];
    char gyrX_msb_Right[3];
    char gyrX_lsb_Right[3];
    char gyrY_msb_Right[3];
    char gyrY_lsb_Right[3];
    char gyrZ_msb_Right[3];
    char gyrZ_lsb_Right[3];
    char magX_msb_Right[3];
    char magX_lsb_Right[3];
    char magY_msb_Right[3];
    char magY_lsb_Right[3];
    char magZ_msb_Right[3];
    char magZ_lsb_Right[3];
    char accelX_msb_Left[3];
    char accelX_lsb_Left[3];
    char accelY_msb_Left[3];
    char accelY_lsb_Left[3];
    char accelZ_msb_Left[3];
    char accelZ_lsb_Left[3];
    char gyrX_msb_Left[3];
    char gyrX_lsb_Left[3];
    char gyrY_msb_Left[3];
    char gyrY_lsb_Left[3];
    char gyrZ_msb_Left[3];
    char gyrZ_lsb_Left[3];
    char magX_msb_Left[3];
    char magX_lsb_Left[3];
    char magY_msb_Left[3];
    char magY_lsb_Left[3];
    char magZ_msb_Left[3];
    char magZ_lsb_Left[3];
    float accX_Right = 0.0, accY_Right = 0.0, accZ_Right = 0.0, gyrX_Right = 0.0, gyrY_Right = 0.0, gyrZ_Right = 0.0, magX_Right = 0.0, magY_Right = 0.0, magZ_Right = 0.0;
    float accX_Left = 0.0, accY_Left = 0.0, accZ_Left = 0.0, gyrX_Left = 0.0, gyrY_Left = 0.0, gyrZ_Left = 0.0, magX_Left = 0.0, magY_Left = 0.0, magZ_Left = 0.0;
    int timeStamp;
    
	//Initial Connect to bind transfer
	//Right Sole
    system("hcitool lecc B4:99:4C:67:B7:B4");
	sleep(2);
    //Left Sole
    system("hcitool lecc B4:99:4C:6C:15:51");
    sleep(2); 
	
    //Writing for gatt protocol to have registers transmit data
	//Change --value= 11 for Pressure, 12 for IMU, 13 for Pressure + IMU
	
    //Right Sole
    if(!(in1 = popen("gatttool -b B4:99:4C:67:B7:B4 --char-write-req --handle 0x0025 --value=13 --listen", "r")))
    {
        return -1;
    }
    
    //Left Sole
    if(!(in2 = popen("gatttool -b B4:99:4C:6C:15:51 --char-write-req --handle 0x0025 --value=13 --listen", "r")))
    {
        return -1;
    }
    
    while(fgets(buff_Right, sizeof(buff_Right), in1)!=NULL && fgets(buff_Left, sizeof(buff_Left), in2)!=NULL)
    {
        //Deleting Unnecessary components of 
        string str_Right(buff_Right);
        str_Right.erase (0,36);

        string str_Left(buff_Left);
        str_Left.erase (0,36);
        //Uncomment the following lines if you just want pure HEX characters to be printed out.
        //You can access each character by tmp[i], i being the index of the character array.
        strcpy(tmp_Right, str_Right.c_str());
        strcpy(tmp_Left, str_Left.c_str());
        //cout<<tmp_Right<<" "<<tmp_Left;
        
        index_Right = 3;
        index_Left = 3;

        if((tmp_Right[1] == '0' || tmp_Right[1] == '1') && (tmp_Left[1] == '0' || tmp_Left[1] == '1'))
        {
           cout<<"Pressure Points: ";
           while(index_Right < 60)
           {
            memcpy(pressurePoint_Right, &tmp_Right[index_Right], 2);
            pressurePoint_Right[2] = '\0';
            index_Right = index_Right + 3;
            cout<<"Right: "<<(255 - (((unsigned int)strtol(pressurePoint_Right, NULL, 16))))<<" ";
            memcpy(pressurePoint_Left, &tmp_Left[index_Left], 2);
            pressurePoint_Left[2] = '\0';
            index_Left = index_Left + 3;
            cout<<"Left: "<<(255 - (((unsigned int)strtol(pressurePoint_Left, NULL, 16))))<<" ";

           }   
        }

        else if(tmp_Right[1] == '2' && tmp_Left[1] == '2')
        {
            cout<<"Pressure Points: ";
            while(index_Right < 33)
            {
                memcpy(pressurePoint_Right, &tmp_Right[index_Right], 2);
                pressurePoint_Right[2] = '\0';
                index_Right = index_Right + 3;
                cout<<"Right: "<<(255 - (((unsigned int)strtol(pressurePoint_Right, NULL, 16))))<<" ";
                memcpy(pressurePoint_Left, &tmp_Left[index_Left], 2);
                pressurePoint_Left[2] = '\0';
                index_Left = index_Left + 3;
                cout<<"Left: "<<(255 - (((unsigned int)strtol(pressurePoint_Left, NULL, 16))))<<" ";
            }   
        }

        else if(tmp_Right[1] == '3' && tmp_Left[1] == '3')
        {
            
            //Right Sole IMU Configurations

            memcpy(accelX_msb_Right, &tmp_Right[3], 2);
            accelX_msb_Right[2] = '\0';
            memcpy(accelX_lsb_Right, &tmp_Right[6], 2);
            accelX_lsb_Right[2] = '\0';
            memcpy(accelY_msb_Right, &tmp_Right[9], 2);
            accelY_msb_Right[2] = '\0';
            memcpy(accelY_lsb_Right, &tmp_Right[12], 2);
            accelY_lsb_Right[2] = '\0';
            memcpy(accelZ_msb_Right, &tmp_Right[15], 2);
            accelZ_msb_Right[2] = '\0';
            memcpy(accelZ_lsb_Right, &tmp_Right[18], 2);
            accelZ_lsb_Right[2] = '\0';
            memcpy(gyrX_msb_Right, &tmp_Right[21], 2);
            gyrX_msb_Right[2] = '\0';
            memcpy(gyrX_lsb_Right, &tmp_Right[24], 2);
            gyrX_lsb_Right[2] = '\0';
            memcpy(gyrY_msb_Right, &tmp_Right[27], 2);
            gyrY_msb_Right[2] = '\0';
            memcpy(gyrY_lsb_Right, &tmp_Right[30], 2);
            gyrY_lsb_Right[2] = '\0';
            memcpy(gyrZ_msb_Right, &tmp_Right[33], 2);
            gyrZ_msb_Right[2] = '\0';
            memcpy(gyrZ_lsb_Right, &tmp_Right[36], 2);
            gyrZ_lsb_Right[2] = '\0';
            memcpy(magX_msb_Right, &tmp_Right[39], 2);
            magX_msb_Right[2] = '\0';
            memcpy(magX_lsb_Right, &tmp_Right[42], 2);
            magX_lsb_Right[2] = '\0';
            memcpy(magY_msb_Right, &tmp_Right[45], 2);
            magY_msb_Right[2] = '\0';
            memcpy(magY_lsb_Right, &tmp_Right[48], 2);
            magY_lsb_Right[2] = '\0';
            memcpy(magZ_msb_Right, &tmp_Right[51], 2);
            magZ_msb_Right[2] = '\0';
            memcpy(magZ_lsb_Right, &tmp_Right[54], 2);
            magZ_lsb_Right[2] = '\0';

            //Left Sole IMU Configurations

            memcpy(accelX_msb_Left, &tmp_Left[3], 2);
            accelX_msb_Left[2] = '\0';
            memcpy(accelX_lsb_Left, &tmp_Left[6], 2);
            accelX_lsb_Left[2] = '\0';
            memcpy(accelY_msb_Left, &tmp_Left[9], 2);
            accelY_msb_Left[2] = '\0';
            memcpy(accelY_lsb_Left, &tmp_Left[12], 2);
            accelY_lsb_Left[2] = '\0';
            memcpy(accelZ_msb_Left, &tmp_Left[15], 2);
            accelZ_msb_Left[2] = '\0';
            memcpy(accelZ_lsb_Left, &tmp_Left[18], 2);
            accelZ_lsb_Left[2] = '\0';
            memcpy(gyrX_msb_Left, &tmp_Left[21], 2);
            gyrX_msb_Left[2] = '\0';
            memcpy(gyrX_lsb_Left, &tmp_Left[24], 2);
            gyrX_lsb_Left[2] = '\0';
            memcpy(gyrY_msb_Left, &tmp_Left[27], 2);
            gyrY_msb_Left[2] = '\0';
            memcpy(gyrY_lsb_Left, &tmp_Left[30], 2);
            gyrY_lsb_Left[2] = '\0';
            memcpy(gyrZ_msb_Left, &tmp_Left[33], 2);
            gyrZ_msb_Left[2] = '\0';
            memcpy(gyrZ_lsb_Left, &tmp_Left[36], 2);
            gyrZ_lsb_Left[2] = '\0';
            memcpy(magX_msb_Left, &tmp_Left[39], 2);
            magX_msb_Left[2] = '\0';
            memcpy(magX_lsb_Left, &tmp_Left[42], 2);
            magX_lsb_Left[2] = '\0';
            memcpy(magY_msb_Left, &tmp_Left[45], 2);
            magY_msb_Left[2] = '\0';
            memcpy(magY_lsb_Left, &tmp_Left[48], 2);
            magY_lsb_Left[2] = '\0';
            memcpy(magZ_msb_Left, &tmp_Left[51], 2);
            magZ_msb_Left[2] = '\0';
            memcpy(magZ_lsb_Left, &tmp_Left[54], 2);
            magZ_lsb_Left[2] = '\0';

            // accX = (((int)strtol(accelX_msb,NULL,16)) << 8 | ((int)strtol(accelX_lsb,NULL,16) ))/16056.0f;
            // accY = (((int)strtol(accelY_msb,NULL,16)) << 8 | ((int)strtol(accelY_lsb,NULL,16) ))/16056.0f;
            // accZ = (((int)strtol(accelZ_msb,NULL,16)) << 8 | ((int)strtol(accelZ_lsb,NULL,16) ))/16056.0f;

            // First Right Sole

            accX_Right = ((((int)strtol(accelX_msb_Right,NULL,16)) << 8 | ((int)strtol(accelX_lsb_Right,NULL,16))) ) ;
            accY_Right = ((((int)strtol(accelY_msb_Right,NULL,16)) << 8 | ((int)strtol(accelY_lsb_Right,NULL,16))) ) ;
            accZ_Right = ((((int)strtol(accelZ_msb_Right,NULL,16)) << 8 | ((int)strtol(accelZ_lsb_Right,NULL,16))) ) ;

            if(accX_Right > 32767)
                accX_Right= (-1 * (65536 - accX_Right))/16056.0f;
            else
                accX_Right = accX_Right/16056.0f;
            if(accY_Right > 32767)
                accY_Right = (-1 * (65536 - accY_Right))/16056.0f;
            else
                accY_Right = accY_Right/16056.0f;
            if(accZ_Right > 32767)
                accZ_Right = (-1 * (65536 - accZ_Right))/16056.0f;
            else
                accZ_Right = accZ_Right/6056.0f;
            

            gyrX_Right = (((int)strtol(gyrX_msb_Right,NULL,16)) << 8 | ((int)strtol(gyrX_lsb_Right,NULL,16))) ;
            gyrY_Right = (((int)strtol(gyrY_msb_Right,NULL,16)) << 8 | ((int)strtol(gyrY_lsb_Right,NULL,16))) ;
            gyrZ_Right = (((int)strtol(gyrZ_msb_Right,NULL,16)) << 8 | ((int)strtol(gyrZ_lsb_Right,NULL,16))) ;

            if(gyrX_Right > 32767)
                gyrX_Right = (-1 * (65536 - gyrX_Right))/262.0f;
            else
                gyrX_Right = gyrX_Right/262.0f;
            if(gyrY_Right > 32767)
                gyrY_Right = (-1 * (65536 - gyrY_Right))/262.0f;
            else
                gyrY_Right = gyrY_Right/262.0f;
            if(gyrZ_Right > 32767)
                gyrZ_Right = (-1 * (65536 - gyrZ_Right))/262.0f;
            else
                gyrZ_Right = gyrZ_Right/262.0f;

            magX_Right = (((unsigned int)strtol(magX_msb_Right,NULL,16)) << 8 | ((unsigned int)strtol(magX_lsb_Right,NULL,16)) );
            magY_Right = (((unsigned int)strtol(magY_msb_Right,NULL,16)) << 8 | ((unsigned int)strtol(magY_lsb_Right,NULL,16)) );
            magZ_Right = (((unsigned int)strtol(magZ_msb_Right,NULL,16)) << 8 | ((unsigned int)strtol(magZ_lsb_Right,NULL,16)) );

            if(magX_Right > 32767)
                magX_Right = -1 * (65536 - magX_Right);
            if(magY_Right > 32767)
                magY_Right = -1 * (65536 - magY_Right);
            if(magZ_Right > 32767)
                magZ_Right = -1 * (65536 - magZ_Right);

            // Second Left Sole 

            accX_Left = ((((int)strtol(accelX_msb_Left,NULL,16)) << 8 | ((int)strtol(accelX_lsb_Left,NULL,16))) ) ;
            accY_Left = ((((int)strtol(accelY_msb_Left,NULL,16)) << 8 | ((int)strtol(accelY_lsb_Left,NULL,16))) ) ;
            accZ_Left = ((((int)strtol(accelZ_msb_Left,NULL,16)) << 8 | ((int)strtol(accelZ_lsb_Left,NULL,16))) ) ;

            if(accX_Left > 32767)
                accX_Left = (-1 * (65536 - accX_Left))/16056.0f;
            else
                accX_Left = accX_Left/16056.0f;
            if(accY_Left > 32767)
                accY_Left = (-1 * (65536 - accY_Left))/16056.0f;
            else
                accY_Left = accY_Left/16056.0f;
            if(accZ_Left > 32767)
                accZ_Left = (-1 * (65536 - accZ_Left))/16056.0f;
            else
                accZ_Left = accZ_Left/6056.0f;
            

            gyrX_Left = (((int)strtol(gyrX_msb_Left,NULL,16)) << 8 | ((int)strtol(gyrX_lsb_Left,NULL,16))) ;
            gyrY_Left = (((int)strtol(gyrY_msb_Left,NULL,16)) << 8 | ((int)strtol(gyrY_lsb_Left,NULL,16))) ;
            gyrZ_Left = (((int)strtol(gyrZ_msb_Left,NULL,16)) << 8 | ((int)strtol(gyrZ_lsb_Left,NULL,16))) ;

            if(gyrX_Left > 32767)
                gyrX_Left = (-1 * (65536 - gyrX_Left))/262.0f;
            else
                gyrX_Left = gyrX_Left/262.0f;
            if(gyrY_Left > 32767)
                gyrY_Left = (-1 * (65536 - gyrY_Left))/262.0f;
            else
                gyrY_Left = gyrY_Left/262.0f;
            if(gyrZ_Left > 32767)
                gyrZ_Left = (-1 * (65536 - gyrZ_Left))/262.0f;
            else
                gyrZ_Left = gyrZ_Left/262.0f;

            magX_Left = (((unsigned int)strtol(magX_msb_Left,NULL,16)) << 8 | ((unsigned int)strtol(magX_lsb_Left,NULL,16)) );
            magY_Left = (((unsigned int)strtol(magY_msb_Left,NULL,16)) << 8 | ((unsigned int)strtol(magY_lsb_Left,NULL,16)) );
            magZ_Left = (((unsigned int)strtol(magZ_msb_Left,NULL,16)) << 8 | ((unsigned int)strtol(magZ_lsb_Left,NULL,16)) );

            if(magX_Left > 32767)
                magX_Left = -1 * (65536 - magX_Left);
            if(magY_Left > 32767)
                magY_Left = -1 * (65536 - magY_Left);
            if(magZ_Left > 32767)
                magZ_Left = -1 * (65536 - magZ_Left);

            cout<<"Right Sole: "<<endl;
            cout<<"AccX: "<<accX_Right<<" AccY: "<<accY_Right<<" AccZ: "<<accZ_Right<<endl;
            cout<<"GyrX: "<<gyrX_Right<<" GyrY: "<<gyrY_Right<<" GyrZ: "<<gyrZ_Right<<endl;
            cout<<"MagX: "<<magX_Right/1000<<" MagY: "<<magY_Right/1000<<" MagZ: "<<magZ_Right/1000<<endl;
            cout<<"Left Sole: "<<endl;
            cout<<"AccX: "<<accX_Left<<" AccY: "<<accY_Left<<" AccZ: "<<accZ_Left<<endl;
            cout<<"GyrX: "<<gyrX_Left<<" GyrY: "<<gyrY_Left<<" GyrZ: "<<gyrZ_Left<<endl;
            cout<<"MagX: "<<magX_Left/1000<<" MagY: "<<magY_Left/1000<<" MagZ: "<<magZ_Left/1000<<endl;
             
        }
		cout<<endl;
    index_Right = 0;
    index_Left = 0;
    }
    pclose(in1);
    pclose(in2);
	return 0;
}
