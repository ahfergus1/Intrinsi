
#include "TransferManager.h"
#include <SD.h>
#include <ctype.h>

TransferManager::TransferManager()
{
  last_id = "00000000";
  buf_idx = 0;
  // Empty is invalid - no name will matchs
  _lastPatient = "";
  _lastSession = "";
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

  // If tree for commands
  // Didn't use switch to allow instantiations
  if (reqType == 'l')
  {
    // Respond with patient/session list
    // \n between patients
    // : between patient and their sessions
    // - between sessions
    File dataDir = SD.open(data_root.c_str()); // New String isn't const
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
            // Don't list header
            if ((header_name+ext).compareTo(file.name()) != 0)
            {
              if (!first)
              {
                Serial.print('-');
              }
              first = false;
              String fname = String(file.name());
              int dotIdx = fname.indexOf('.');
              Serial.print(fname.substring(0, dotIdx));
            }
          }
        }
        // End of this patient's sessions
        Serial.println("");
      }
    }
    // Done, print an extra new line
    Serial.print("\n");
  }
  else if (reqType == 'p')
  {
    // Check if ID is valid
    if (!patientExists(String(&(buff[1]))))
    {
      Serial.print("i\r\n\n");
      return;
    }
    // Respond with patient data
    String patientPath = String(data_root);
    patientPath.concat(&(buff[1]));
    patientPath.concat('/');
    patientPath.concat(header_name);
    patientPath.concat(ext);
    File file = SD.open(patientPath.c_str());
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
    // int a;
    int b;
    // a = 1;
    b = request.indexOf('-');
    if (b<0 || b >= request.length()-1)
    {
      Serial.print("i\r\n\n");
      return;
    }
    String sessionPath = String(data_root);
    sessionPath.concat(request.substring(1,b));
    sessionPath.concat('/');
    sessionPath.concat(request.substring(b+1));
    sessionPath.concat(ext);
    File file = SD.open(sessionPath.c_str());
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

bool TransferManager::validId(String id)
{
  int len = id.length();
  if (len != 8)
    return false;
  for (int i=0; i<len; i++)
  {
    if (!isdigit(id[i]))
    {
      return false;
    }
  }
  return true;
}

String TransferManager::nextValidPatientId()
{
  // Check if error has occurred
  if (last_id.compareTo("patients full") == 0)
    return last_id;
  // Make sure last_id is in use
  while (SD.exists((data_root + last_id).c_str()))
  {
    // Check if at end
    if (last_id.compareTo("99999999") == 0)
    {
      last_id = "patients full";
      return last_id;
    }
    // Increment id
    int idx = 8;
    bool inc = true;
    do
    {
      idx--;
      last_id[idx]++;
      if (last_id[idx] == ('9'+1))
        last_id[idx] = '0';
      else
        inc = false;
    } while (inc);
  }
  return last_id;
}

// Warning this takes linear time every time unless you save the seed externally!
String TransferManager::nextValidSessionId(String patientId, String seed)
{
  // // Check if error has occurred
  // if (last_id.compareTo("patients full") == 0)
  //   return last_id;
  // Make sure last_id is in use
  String id = seed;
  String dataRoot(data_root + patientId + '/');
  while (SD.exists((dataRoot + id + ext).c_str()))
  {
    // Check if at end
    if (id.compareTo("99999999") == 0)
    {
      id = "sessions full";
      return id;
    }
    // Increment id
    int idx = 8;
    bool inc = true;
    do
    {
      idx--;
      id[idx]++;
      if (id[idx] == ('9'+1))
        id[idx] = '0';
      else
        inc = false;
    } while (inc);
  }
  return id;
}

bool TransferManager::patientExists(String patientId)
{
  return SD.exists((data_root + patientId).c_str());
}

bool TransferManager::writePatient(String ver, String patientId, String uname)
{
  // Verify patient is new
  if (!SD.exists(data_root.c_str()))
    SD.mkdir(data_root.c_str());
  if (!validId(patientId))
    return false;
  if (patientExists(patientId))
    return false;

  // Don't need to check _lastPatient - must be new

  // Get path
  String path = data_root + patientId;
  //Serial.println(path);
  SD.mkdir(path.c_str());
  path = path + '/' + header_name + ext;
  //Serial.println(path);
  if (!SD.exists(path.c_str()))
  {
    File file = SD.open(path.c_str(), FILE_WRITE);
    //Serial.println("File");
    if (file)
    {
      //Serial.println("File created");
      file.println(ver);
      file.print("ID,");
      file.println(patientId);
      file.print("User Name,");
      file.println(uname);
      file.close();
    }
  }

  // Update _lastPatient
  _lastPatient = patientId;

  // Probably succeeded if flow gets here
  return true;
}

bool TransferManager::writeSession(String ver, String patientId, String timestamp, float freq, float readings[], int sets, int readingsLen)
{
  // Fail if patient does not exist
  if (!patientExists(patientId))
  {
    Serial.println("Patient does not exist");
    return false;
  }
  
  // Get a session ID
  String sessionId;
  if (_lastPatient == patientId)
    sessionId = nextValidSessionId(patientId, _lastSession);
  else
    sessionId = nextValidSessionId(patientId);
  // Fail if sessionId is invalid

  _lastPatient = patientId;
  _lastSession = sessionId;

  // Get a path and open file
  String path = data_root + patientId + '/' + sessionId + ext;
  //Serial.println(path);

  // Delete session if it exists
  if (SD.exists(path.c_str()))
    SD.remove(path.c_str());
  
  // Open file for writing
  File file = SD.open(path.c_str(), FILE_WRITE);
  if (file)
  {
    file.println(ver);
    file.print("ID,");
    file.println(sessionId);
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
      for (int j = 0; j < readingsLen; j++)
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

  // Probably succeeded if flow gets here
  return true;
}
