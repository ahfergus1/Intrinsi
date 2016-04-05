
class TransferManager {
private:
  // Maximum request length: 
  //   1 + 5 + 1 + 10 + 1 + 8 + 1
  //   = 27, use 30 for fun
  static const int BUF_SIZE = 100;
  char buff[BUF_SIZE];
  int  buf_idx;

  void respondToRequest(bool busy);

public:
  TransferManager();
  void procInput(char inChar, bool busy); 
  void writePatient(char *ver, char *id, char *uname);
  void writeSession(char *ver, char *id, char *timestamp, float freq, float readings[], int sets, int readingsLen);
};
