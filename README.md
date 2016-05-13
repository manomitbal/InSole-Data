# InSole-Data
Extraction of Data Sets for Pressure and IMU from Smart Insoles

For Linux Users:

1) Install bluez library for linux which contains hcitools and gatttools

2) git clone https://github.com/manomitbal/InSole-Data

3) cd InSole-Data

4) make

5) Switch on both Insoles

6) Run with command: ./originalSole for basic raw data from both soles, ./singleSole for sensor fusion data (roll, pitch, yaw) and unity connect for one sole and ./bothSoles for both working soles.

Issues:

After running the program, successful binding of the bluetooth connection will be evidenced by the statements
"Connection Handle #" for each Sole. Sometimes, there is an Input Output error which can usually be reset by turning the devices on 
and off again, and running "hcitool lescan"

This should scan for the two devices after which run the specific executable again.

Data Format:

Pressures 1-48 Left and Right Alternating.
Right Sole IMU data
Left Sole IMU data

Unity Code gets parsed data in format (roll left sole, pitch left sole, yaw left sole, pressure color threshold, acc x left, acc y left, acc z left, roll right sole, pitch right sole, yaw right sole, pressure color threshold, acc x right, acc y right, acc z right)

Attached to this repository is a test data set with undoctored raw HEX values advertised from the soles. 

-Manomit 
