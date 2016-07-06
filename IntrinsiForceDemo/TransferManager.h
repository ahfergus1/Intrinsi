/* TransferManager.h
 * Handles storing data on the SD car and sending it to a host PC.
 * @author Andrew Simpson, ahfergus1@gmail.com
 */

#ifndef _TRANSFERMANAGER_H
#define _TRANSFERMANAGER_H

#include "Arduino.h"

class TransferManager {
private:
  // Maximum request length: 
  //   1 + 5 + 1 + 10 + 1 + 8 + 1
  //   = 27, use 30 for fun
  static const int BUF_SIZE = 100;
  char buff[BUF_SIZE];
  int  buf_idx;
  String last_id; // Last AVAILABLE id
  const String data_root = "/Data/";
  const String header_name = "PATIENT";
  const String ext = ".CSV";
  String _lastPatient; // Last ACCESSED id
  String _lastSession;
  void respondToRequest(bool busy);

public:
  TransferManager();
  void procInput(char inChar, bool busy); 
  bool validId(String patientId);
  String nextValidPatientId();
  String nextValidSessionId(String patientId, String seed = "00000000");
  bool patientExists(String patientId);
  bool writePatient(String ver, String patientId, String uname);
  bool writeSession(String ver, String patientId, String timestamp, float freq, float readings[], int sets, int readingsLen);
};

#endif