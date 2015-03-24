

/*
  This program is meant to take information from the analog input A0
  and print it out to a text file called "CardioCheckData.txt"
  Sample rate: 200Hz (project requires at least 160Hz)
  
 */

#include <SPI.h>
#include <SD.h>
#include <ECGFilters.h>

int i;
int sensorValue;
boolean SDInitSuccess = true;
File myFile;
qrs_filter filter = qrs_filter();

void setup()
{
  // Open serial communications and wait for port to open: use for debug purposes
  //Serial.begin(115200);
  
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  //Serial.println("Initializing SD Card");
  if (!SD.begin(10)) {
    SDInitSuccess = false;
    //Serial.println("SD card Not initialized");
    return;
  }
  //Serial.println("SD initialization success");
  
  //creating and opening file
  myFile = SD.open("CardioCheckData.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    //Serial.print("File created successfully. Writing analog info");
    for (i = 0; i <= 1000; i++)
    {
      sensorValue = analogRead(A0);
      return_value result = filter.step(sensorValue);
      myFile.println(millis());
      //This is how they pull respiration phase from the result
      //I need to find out how to get the filtered value as well
      //Serial.print(result.respiration_phase, BYTE);
      //myFile.println(analogRead(0));
    }
    // close the file:
    myFile.close();
    //Serial.println("done writing to file");
  } else {
    // if the file didn't open, print an error:
    //Serial.println("error opening CardioCheckData.txt");
  }
}

void loop()
{
  // nothing happens after setup
}


