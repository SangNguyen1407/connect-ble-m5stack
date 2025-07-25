#include "fileHandle.h"


bool isExsisted(){
  bool success = SPIFFS.begin(true);
  return SPIFFS.exists(CONF_FILENAME);
}

/* ファイルのクローズ
 */
File closeFile(File file){
  if (file){
    file.close();
  }
}

/* ファイルの削除
 */
void deleteFile(){
  bool success = SPIFFS.begin(true);
  if (success){
    SPIFFS.remove(CONF_FILENAME);
  }
}

/* ファイルの読み出す
 */
String readFile(){
  String sData = "";
  bool success = SPIFFS.begin(true);
  File file = SPIFFS.open(CONF_FILENAME, FILE_READ);

  if (success && file){
    sData = file.readStringUntil('\n');
    file.close();
  }
  else{
    M5.Lcd.drawString("not open file", 10, 90, 2);
  }
  return sData;
}

/* ファイルの書き込む
 */
bool writeFile(const char *content, const char *priority){
  bool success = SPIFFS.begin(true);
  File file = SPIFFS.open(CONF_FILENAME, FILE_WRITE);

  if (success && file){
    file.println(content);
    file.close();
  }

  return true;
}