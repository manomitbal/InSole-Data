# InSole-Data
Extraction of Data Sets for Pressure and IMU from Smart Insoles

For Linux Users:

1) Install bluez library for linux which contains hcitools and gatttools

2) git clone https://github.com/manomitbal/InSole-Data

3) cd InSole-Data

4) make

5) Switch on both Insoles

6) Run with command: ./blue

Issues:

After running the program, successful binding of the bluetooth connection will be evidenced by the statements
"Connection Handle #" for each Sole. Sometimes, there is a Input Output error which can usually be reset by turning the devices on 
and off again, and running "hcitool lescan"

This should scan for the two devices after which run ./blue again.

-Manomit 
