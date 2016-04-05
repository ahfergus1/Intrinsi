
#include <SD.h>
#include "TransferManager.h"

TransferManager::TransferManager()
{
  buf_idx = 0;
}

void TransferManager::procInput(char inChar, bool busy)
{
  // Read into buffer
  if (buf_idx == BUF_SIZE - 1)
    buf_idx = 0;
  buff[buf_idx] = inChar;
  if (buff[buf_idx] == '\n')
  {
    buff[buf_idx] = '\0';
    respondToRequest(busy);
    buf_idx = 0;
    return;
  }
  buf_idx++;
  return;
}

void TransferManager::respondToRequest(bool busy)
{
  // If busy, just respond with two bytes
  if (busy)
  {
    // Send busy string, ends with \n\n
    Serial.println("b\r\n\n");
    return;
  }

  // Get request type
  char reqType = buff[0];

  // Switch for commands
  if (reqType == 'l')
  {
    // Respond with patient/session list
    // \n between patients
    // : between patient and their sessions
    // - between sessions
    File dataDir = SD.open("/Data/");
    while (true)
    {
      File entry = dataDir.openNextFile();
      if (! entry)
      {
        break;
      }
      if (entry.isDirectory())
      {
        // Print patient header
        Serial.print(entry.name());
        Serial.print(':');
        bool first = true;
        // Iterate through entries
        while (true)
        {
          File file = entry.openNextFile();
          if (!file)
          {
            break;
          }
          if (!file.isDirectory())
          {
            if (!first)
              Serial.print('-');
            first = false;
            String fname = String(file.name());
            int dotIdx = fname.indexOf('.');
            Serial.print(fname.substring(0, dotIdx));
          }
        }
        // End of this patient
        Serial.println("");
      }
    }
    // Done, print an extra new line
    Serial.print("\n");
  }
  else if (reqType == 'p')
  {
    // Respond with patient data
    String patientPath = String("/Data/");
    patientPath.concat(&(buff[1]));
    patientPath.concat(".CSV");
    patientPath.toCharArray(buff,BUF_SIZE);
    File file = SD.open(buff);
    if (!file)
    {
      Serial.print("i\r\n\n");
      return;
    }
    while (file.available())
      Serial.write(file.read());
    file.close();
    Serial.print("\n\n");
  }
  else if (reqType == 's')
  {
    // Respond with session data
    // Respond with patient data
    String request = String(buff);
    int a,b;
    a = 1;
    b = request.indexOf('-');
    if (b<0 || b >= request.length()-1)
    {
      Serial.print("i\r\n\n");
      return;
    }
    String patientPath = String("/Data/");
    patientPath.concat(request.substring(1,b));
    patientPath.concat('/');
    patientPath.concat(request.substring(b+1));
    patientPath.concat(".CSV");
    patientPath.toCharArray(buff,BUF_SIZE);
    File file = SD.open(buff);
    if (!file)
    {
      Serial.println("i\r\n\n");
      return;
    }
    while (file.available())
      Serial.write(file.read());
    file.close();
    Serial.print("\n\n");
  }
  else
  {
    // Respond with invalid request string
    Serial.println("i\r\n\n");
  }
}

void TransferManager::writePatient(char *ver, char *id, char *uname)
{
  const int LEN = 100;
  char buff[LEN];
  String path = String("/Data/");
  path.concat(id);
  path.toCharArray(buff,LEN);
  //Serial.println(path);
  if (!SD.exists(buff))
    SD.mkdir(buff);
  path.concat(".csv");
  path.toCharArray(buff,LEN);
  //Serial.println(path);
  if (!SD.exists(buff))
  {
    File file = SD.open(buff, FILE_WRITE);
    //Serial.println("File");
    if (file)
    {
      //Serial.println("File created");
      file.println(ver);
      file.print("ID,");
      file.println(id);
      file.print("User Name,");
      file.println(uname);
      file.close();
    }
  }
}

void TransferManager::writeSession(char *ver, char *id, char *timestamp, float freq, float readings[], int sets, int readingsLen)
{
  const int LEN = 100;
  char buff [LEN];
  String path = String("/Data/");
  path.concat(id);
  path.concat('/');
  path.concat(timestamp);
  path.concat(".csv");
  path.toCharArray(buff,LEN);
  //Serial.println(path);
  if (SD.exists(buff))
  if (SD.remove(buff))
  {
    File file = SD.open(buff, FILE_WRITE);
    if (file)
    {
      file.println(ver);
      file.print("Time Stamp,");
      file.println(timestamp);
      file.print("Frequency [Hz],");
      file.println(freq);
      for (int i = 0; i < sets; i++)
      {
        file.print("Readings ");
        file.print(i);
        file.print(',');
        bool first = true;
        for (int j = 1; j < readingsLen; j++)
        {
          if (!first)
            file.print(',');
          first = false;
          file.print(readings[i*readingsLen + j]);
        }
        file.println("");
      }
      file.close();
    }
  }
}

