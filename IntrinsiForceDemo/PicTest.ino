
/*

  this demo can show specified bmp file in root Directory of SD card
  please ensure that your image file is 320x240 size. 

  change __Gnfile_num and __Gsbmp_files to display your image
*/

/*

void example_setup()
{
    Serial.begin(9600);
    
    __XPT2046_CS_DISABLE();
    
    pinMode(PIN_SD_CS,OUTPUT);
    digitalWrite(PIN_SD_CS,HIGH);
    Sd2Card card;
    card.init(SPI_FULL_SPEED, PIN_SD_CS); 
    if(!SD.begin(PIN_SD_CS))  { 
        Serial.println("failed!");
        while(1);                               // init fail, die here
    }
    
    SPI.setDataMode(SPI_MODE3);
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    SPI.begin();
    
    Tft.lcd_init();
//    Tft.lcd_display_string(50, 120, (const uint8_t *)"Start to display...", FONT_1608, RED);
    Serial.println("SD OK!");
    delay(1000);
  StartUp();
}

void example_loop()
{
  // current loop polls through every feature of draw.h
  // 
draw.DispMenu();
delay(1000);
draw.ClrMenu();
delay(1000);
draw.DispPinchPrompt();
delay(1000);
draw.ClrPinchPrompt();
delay(1000);
for (int i = 0; i < 10; i++){
    draw.DispPinchArea(i);
    delay(1000);
    draw.ClrPinchArea(i);
    delay(1000);
}
draw.DispResult(20,1);
delay(1000);
draw.ClrResult(20,1);
delay(1000);
draw.DispProbe(10);
delay(1000);
draw.ClrProbe(10);
delay(1000);
DispStream();
ClrStream();
draw.StartTone();
draw.EndTone();
}

*/
