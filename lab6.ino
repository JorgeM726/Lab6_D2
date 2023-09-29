/*
  Listfiles

  This example shows how print out the files in a
  directory on a SD card

  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe
  modified 2 Feb 2014
  by Scott Fitzgerald

  This example code is in the public domain.

*/
#include <SPI.h>
#include <SD.h>
int menu = 0;
File root;
File myFile;
String imagen;
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  SPI.setModule(0);


  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(10, OUTPUT);

  if (!SD.begin(32)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("done!");

  Serial.println("Ingrese 1 para 1D, ingrese 2 para TOP, ingrese 3 para flor, 4 para escribir");
}

void loop()
{


  while (!Serial.available());
  if (Serial.available()) {
    menu = Serial.read();

  }


  switch (menu) {
    case 49:
      myFile = SD.open("od.txt");
      if (myFile) {
        Serial.println("od.txt:");

        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening od.txt");
      }
      menu = 0;
      Serial.println("Ingrese 1 para 1D, ingrese 2 para TOP, ingrese 3 para flor, 4 para escribir");
      break;
    case 50:
      myFile = SD.open("top.txt");
      if (myFile) {
        Serial.println("top.txt:");

        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening top.txt");
      }
      menu = 0;
      Serial.println("Ingrese 1 para 1D, ingrese 2 para TOP, ingrese 3 para flor, 4 para escribir");
      break;
    case 51:
      myFile = SD.open("flor.txt");
      if (myFile) {
        Serial.println("flor.txt:");

        // read from the file until there's nothing else in it:
        while (myFile.available()) {
          Serial.write(myFile.read());
        }
        // close the file:
        myFile.close();
      } else {
        // if the file didn't open, print an error:
        Serial.println("error opening flor.txt");
      }
      menu = 0;
      Serial.println("Ingrese 1 para 1D, ingrese 2 para TOP, ingrese 3 para flor, 4 para escribir");
      break;

    case 52:
      Serial.println("Envíe '5' para guardar.");

  String Drawing = "";  

  while (true) {
    if (Serial.available() > 0) {
      char c = Serial.read();
  
      if (c == '5') {
        Serial.println("Saving");
  
        File myFile = SD.open("escribir.txt", FILE_WRITE);
  
        if (myFile) {
          myFile.print(Drawing);
          myFile.close();
          Serial.println("successfully save as escribir.txt");
        } else {
          Serial.println("Error");
        }
        break;
      } else {
        Drawing += c; 
      }
    }
  }
      menu = 0;
             Serial.println("Ingrese 1 para 1D, ingrese 2 para TOP, ingrese 3 para flor, 4 para escribir");
             break;
  }




}



void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
