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
#include <math.h>
#include <time.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>


using namespace std;

int main()
{
    FILE *in1;
    int i = 0;
    int index = 3;
    int pressIndex = 0;
    int pressureCount = 0;
    int pressures[47];
    char buff[1024];
    char tmp[1024];
    char pressurePoint[3];
    char accelX_msb[3];
    char accelX_lsb[3];
    char accelY_msb[3];
    char accelY_lsb[3];
    char accelZ_msb[3];
    char accelZ_lsb[3];
    char gyrX_msb[3];
    char gyrX_lsb[3];
    char gyrY_msb[3];
    char gyrY_lsb[3];
    char gyrZ_msb[3];
    char gyrZ_lsb[3];
    char magX_msb[3];
    char magX_lsb[3];
    char magY_msb[3];
    char magY_lsb[3];
    char magZ_msb[3];
    char magZ_lsb[3];
    char unknown[3];
    float accX = 0.0, accY = 0.0, accZ = 0.0, gyrX = 0.0, gyrY = 0.0, gyrZ = 0.0, magX = 0.0, magY = 0.0, magZ = 0.0, unknownx = 0.0;
    int timeStamp;
    char rawPressures[47];
    int lineCount = 1;

    // Socket to send data to Unity through Virtual Machine/Linux Platform
     int sockfd, n;
     int portno = 6000;
     struct sockaddr_in serv_addr;
     struct hostent *server;

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     server = gethostbyname("192.168.56.1");
   //server = gethostbyname("127.0.0.1");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;

     bcopy((char *)server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length);
     serv_addr.sin_port = htons(portno);

     n = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
     if(n < 0) {
       cout << "Cannot connect to server." << endl;
       exit(0);
     }

    //Initial Connect to bind transfer
    //Uncomment next set of lines to test Left Insole
    //Right Insole
    system("hcitool lecc B4:99:4C:67:B7:B4");
    sleep(2);
    //Left
    //system("hcitool lecc B4:99:4C:6C:15:51");
    //sleep(2);
    //Writing for gatt protocol to have registers transmit data
    //Change --value= 11 for Pressure, 12 for IMU, 13 for Pressure + IMU
    //Change MAC ID to B4:99:4C:6C:15:51 for Left Insole
    if(!(in1 = popen("gatttool -b B4:99:4C:67:B7:B4 --char-write-req --handle 0x0025 --value=13 --listen", "r")))
    {
        return -1;
    }
    int lasttime;
    lasttime=time(NULL);
    float downsample;
    downsample=0;
    int altYaw;
    altYaw=0;
    int gyrTest;
    gyrTest=0;
    int pressurePointArr[48];
    
    int j =0;
    int p=0;
    while(fgets(buff, sizeof(buff), in1)!=NULL)
    {
        //Deleting Unnecessary components of
        string str(buff);
        str.erase (0,36);
        
        //You can access each character by tmp[i], i being the index of the character array.
        strcpy(tmp, str.c_str());
               
        index = 3;
   
        //Checking line sequences to parse Pressure Data
        if(tmp[1] == '0' || tmp[1] == '1')
        {
           cout<<"Pressure Points: ";
           while(index < 60)
           {
            
            memcpy(pressurePoint, &tmp[index], 2);
            pressurePoint[2] = '\0';
            index = index + 3;
            p=(255 - (((unsigned int)strtol(pressurePoint, NULL, 16))));
            pressurePointArr[j]=p;
            j++;
            cout<<j<<" ";
           }  
        }
        //Parsing part of line for partial Pressure Data
        else if(tmp[1] == '2')
        {
            cout<<"Pressure Points: ";
            while(index < 33)
            {
                memcpy(pressurePoint, &tmp[index], 2);
                pressurePoint[2] = '\0';
                index = index + 3;
                p=(255 - (((unsigned int)strtol(pressurePoint, NULL, 16))));
                pressurePointArr[j]=p;
                j++;
            
            }
            
            j=0; 
        }

        //Parsing Line for IMU Data
        else if(tmp[1] == '3')
        {
            
            memcpy(accelX_msb, &tmp[3], 2);
            accelX_msb[2] = '\0';
            memcpy(accelX_lsb, &tmp[6], 2);
            accelX_lsb[2] = '\0';
            memcpy(accelY_msb, &tmp[9], 2);
            accelY_msb[2] = '\0';
            memcpy(accelY_lsb, &tmp[12], 2);
            accelY_lsb[2] = '\0';
            memcpy(accelZ_msb, &tmp[15], 2);
            accelZ_msb[2] = '\0';
            memcpy(accelZ_lsb, &tmp[18], 2);
            accelZ_lsb[2] = '\0';
            memcpy(gyrX_msb, &tmp[21], 2);
            gyrX_msb[2] = '\0';
            memcpy(gyrX_lsb, &tmp[24], 2);
            gyrX_lsb[2] = '\0';
            memcpy(gyrY_msb, &tmp[27], 2);
            gyrY_msb[2] = '\0';
            memcpy(gyrY_lsb, &tmp[30], 2);
            gyrY_lsb[2] = '\0';
            memcpy(gyrZ_msb, &tmp[33], 2);
            gyrZ_msb[2] = '\0';
            memcpy(gyrZ_lsb, &tmp[36], 2);
            gyrZ_lsb[2] = '\0';
            memcpy(magX_msb, &tmp[39], 2);
            magX_msb[2] = '\0';
            memcpy(magX_lsb, &tmp[42], 2);
            magX_lsb[2] = '\0';
            memcpy(magY_msb, &tmp[45], 2);
            magY_msb[2] = '\0';
            memcpy(magY_lsb, &tmp[48], 2);
            magY_lsb[2] = '\0';
            memcpy(magZ_msb, &tmp[51], 2);
            magZ_msb[2] = '\0';
            memcpy(magZ_lsb, &tmp[54], 2);
            magZ_lsb[2] = '\0';
            
            //Combining MSB LSB 

            accX = ((((int)strtol(accelX_msb,NULL,16)) << 8 | ((int)strtol(accelX_lsb,NULL,16))) ) ;
            accY = ((((int)strtol(accelY_msb,NULL,16)) << 8 | ((int)strtol(accelY_lsb,NULL,16))) ) ;
            accZ = ((((int)strtol(accelZ_msb,NULL,16)) << 8 | ((int)strtol(accelZ_lsb,NULL,16))) ) ;

            //Computing for signed bit for Acceleration Data

            if(accX > 32767)
                accX = (-1 * (65536 - accX))/16056.0f;
            else
                accX = accX/16056.0f;
            if(accY > 32767)
                accY = (-1 * (65536 - accY))/16056.0f;
            else
                accY = accY/16056.0f;
            if(accZ > 32767)
                accZ = (-1 * (65536 - accZ))/16056.0f;
            else
                accZ = accZ/6056.0f;
           
            //Combining MSB LSB for Gyro Data

            gyrX = (((int)strtol(gyrX_msb,NULL,16)) << 8 | ((int)strtol(gyrX_lsb,NULL,16))) ;
            gyrY = (((int)strtol(gyrY_msb,NULL,16)) << 8 | ((int)strtol(gyrY_lsb,NULL,16))) ;
            gyrZ = (((int)strtol(gyrZ_msb,NULL,16)) << 8 | ((int)strtol(gyrZ_lsb,NULL,16))) ;

            //Computing for signed bit for Gyro Data

            if(gyrX > 32767)
                gyrX = (-1 * (65536 - gyrX))/262.0f;
            else
                gyrX = gyrX/262.0f;
            if(gyrY > 32767)
                gyrY = (-1 * (65536 - gyrY))/262.0f;
            else
                gyrY = gyrY/262.0f;
            if(gyrZ > 32767)
                gyrZ = (-1 * (65536 - gyrZ))/262.0f;
            else
                gyrZ = gyrZ/262.0f;

            //Combining MSB LSB for Magnetometer Data

            magX = (((unsigned int)strtol(magX_msb,NULL,16)) << 8 | ((unsigned int)strtol(magX_lsb,NULL,16)) );
            magY = (((unsigned int)strtol(magY_msb,NULL,16)) << 8 | ((unsigned int)strtol(magY_lsb,NULL,16)) );
            magZ = (((unsigned int)strtol(magZ_msb,NULL,16)) << 8 | ((unsigned int)strtol(magZ_lsb,NULL,16)) );

            //Computing for signed bit for Magnetometer Data

            if(magX > 32767)
                magX = -1 * (65536 - magX);
            if(magY > 32767)
                magY = -1 * (65536 - magY);
            if(magZ > 32767)
                magZ = -1 * (65536 - magZ);


            //Bob code begins here
            int pitchAcc;
            pitchAcc=atan(accY/(sqrt(accX*accX+accZ*accZ)))*180/3.14;

            int pitchGyro;
            int timer;
            int dt;
           

            timer=time(NULL);
            dt=timer-lasttime;
            pitchGyro=pitchAcc+gyrX*(dt);
            lasttime=timer;

            int pitchComplement;
            pitchComplement=0.9*pitchGyro+0.1*pitchAcc;

            int rollAcc;
            rollAcc=atan(-accX/accZ)*180/3.14;

            int yaw;
            //yaw = atan (accZ/sqrt(accX*accX + accZ*accZ))*180/3.14;
            int mag_norm;
            mag_norm=sqrt(magX*magX+magY*magY+magZ*magZ);
            magX=magX/mag_norm;
            magY=magY/mag_norm;
            magZ=magZ/mag_norm;

            // yaw=atan2(-magY*cos(rollAcc)+magZ*sin(rollAcc),magX*cos(pitchComplement)+magY*sin(pitchComplement)*sin(rollAcc)+
            // magZ*sin(pitchComplement)*cos(rollAcc))*180/3.14;
            if(abs(gyrZ)>1.75 ){
                altYaw+=gyrZ*3;
                
            }
            else if(abs(gyrZ)>0.25){
                altYaw+=(gyrZ*6.4);
            }
           
            if(downsample==0){
                
                // yaw = 180 * atan (accZ/sqrt(accX*accX + accZ*accZ))/3.14159;
                yaw=(magX+magY)*180/3.14*2;
                downsample=3;
            }
            else{
                downsample--;
            }
            //Tuning pitch to work correctly
            // pitchComplement=-0.021614*(pitchComplement)*pitchComplement+2.83964*pitchComplement+4.82555;
            int op1=0;
            if(pitchComplement<4){
                op1=pitchComplement/0.4+33.3;
            }
            else if(28.9796*log(pitchComplement)<33){
                op1=33.3;
            }
            else{
                op1=28.9796*log(pitchComplement);
            }
            pitchComplement=op1-33.2165;
            

            //Now to analyze the pressure sensors to determine color
            int color;
            color=0;

            //Determine the number of sensors over 75 and over 125
            int count75=0;
            int count125=0;

            for(int i=0;i<48;i++){
                if(pressurePointArr[i]>75){
                    count75++;
                }
                if(pressurePointArr[i]>125){
                    count125++;
                }
            }

            if(count125>5){
                color=2; //red
            }
            else if(count75>5){
                color=1; //orange
            }
            else{
                color=0; //white
            }
        
        //Printing final Roll, Pitch, Yaw and Color based on Pressure activity
        cout<<"Roll: "<<rollAcc<<" Pitch: "<<pitchComplement<<" Yaw: "<<int(altYaw)<<" Color Based On Pressure: "<<color<<endl;
   
        gyrTest=gyrTest+gyrY*dt;                  
        char message [500];
        //Sending Data to Socket for functioning in Unity
        sprintf(message, "%d %d %d %d %f %f %f\n", rollAcc,pitchComplement,altYaw, color, accX, accY, accZ);
        cout << "Acceleration X: "<< accX<< " Acceleration Y: "<< accY<< " Acceleration Z: "<< accZ <<endl;
        write(sockfd, message, strlen(message));
    }
    cout<<endl;
    index = 0;
    }
    close(sockfd);
    pclose(in1);
    return 0;
}