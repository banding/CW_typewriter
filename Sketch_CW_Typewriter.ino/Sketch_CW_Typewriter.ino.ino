/*
  Keyboard Keyer uses an Arduino Leonardo or Pro-Micro to
  Sends an ASCII charter via USB port
  when CW is sent using Iambic paddles 
  an ASCII character is send to computer
 
  Bob Anding  Morse Code OSC
  Morse Code Iambic key Oscillator & rig keyer
  Bob Anding, 12-20-17
  update game version 1-20-20
  for personal use only
  This uses the " Tiny Iambic Keyer starting project" for Morse Code using a Iambic key.
  The sketch checks an Iambic key for Dits or Dahs. Then plays a tone and lights pin 13 built-in LED .
  The output at Pin 13 can be used to key a rig. 
  Most modern rigs use logic key input. An open-collector transistor interface is recommended.
  Tube rigs will use a different setup. ALWAYS! Check your radio specs.
  This a small sketch to converts CW to ASCII and acts as a keyboard and
  Using an Arduino Pro-Micro's USB port it sends text to the computer
********************************************************/
/* Bob Anding CW-tyewriter
  (c) 2019, Bob Anding, 10-03-2019
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and 
  associated documentation files (the "Software"), to deal in the Software without restriction, 
  including without limitation the rights to use, copy, modify, merge, publish, distribute, 
  sublicense, and/or sell copies of the Software, and to permit persons to whom the 
  Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be 
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN 
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


*******************************************************/
#include <Keyboard.h>
const int Dit = 7; //  iambic key dit paddle
const int Dah = 8; //  iambic key dah paddle
const int keyPin = 13; // Pro Micro use (const keyPin = 15;)***** Logic level output (open collector transistor for keying, check rig's specs.)****
const int spkPin = A0; //  send a CW tone
const int WpmPin = A1; // set WPM speed.
const int SpcPin = A2; //if HIGH automaticlly added a space after a CW word, or if LOW the space button is used
float CWspeed = 0;
int sideTone = 600; // Frequency of side tone
int ditLength = 64; // default setting for dit length, at startup program reads speed pot and set WPM (60 ~ 30 WPM, 80 ~ 20 WPM, 120 ~ 7 WPM)
int LetSpc = 7 * ditLength; // letter spacing is 7 dit length
int WDspc = 40 * ditLength;//WDspc = 35 dit length int WDspc = 0;
unsigned char CWchar = 0;
//unsigned char Hold = 0x85;
int Halt = 1  ; // halt keyboard print after space

////////////    Morse Code to ASCII Array  /////////////////////////
/* Each ASCII charter are assigned a value for keyed morse code characters.
    IE: a= 101, read from left to right, 1 stop bit then 0 =dit and finally 1 = dah.
    The arduino places a stop bit to start next it receives a dit is received folowed by a dah = 101
    using binary number (101) the array Lray is scannned for the binary number (101) and
    if a match is found an ascii charter is sent to the window with focus.
    there are 128 ascii charters and 8 bits minus the 1 stop bit allows for 7 data bits.
    with 7 bits we can have a total of 128 charters or the complete ascii set.
******************************************************************************/
struct Let {
  int num;
  char ch;
};
struct Let Lray[] = {

  {0x31, 0x0a}, //BT =  Line Feed

  {0x6b, '!'},
  {0xc8, '$'},
  {0x28, '&'}, //wait
  {0x5e, '\''},
  {0x2d, '('},
  {0x6d, ')'},
  {0x2a, '+'},
  {0x73, ','},
  {0x61, '-'},
  {0x55, '.'},
  {0x32, '/'},
  {0x3f, '0'},
  {0x2f, '1'},
  {0x27, '2'},
  {0x23, '3'},
  {0x21, '4'},
  {0x20, '5'},
  {0x30, '6'},
  {0x38, '7'},
  {0x3c, '8'},
  {0x3e, '9'},
  {0x78, ':'},
  {0x6a, ';'},
  {0x31, '='},
  {0x4c, '?'},
  {0x54, '@'},
  {0x6c, '_'},
  {0x15, 0xB0}, //return <AA>
  //{96, '`'},
  {0x05, 'a'},
  {0x18, 'b'},
  {0x1a, 'c'},
  {0x0c, 'd'},
  {0x02, 'e'},
  {0x12, 'f'},
  {0x0e, 'g'},
  {0x10, 'h'},
  {0x04, 'i'},
  {0x17, 'j'},
  {0x0d, 'k'},
  {0x14, 'l'},
  {0x07, 'm'},
  {0x06, 'n'},
  {0x0f, 'o'},
  {0x16, 'p'},
  {0x1d, 'q'},
  {0x0a, 'r'},
  {0x08, 's'},
  {0x03, 't'},
  {0x09, 'u'},
  {0x11, 'v'},
  {0x0b, 'w'},
  {0x19, 'x'},
  {0x1b, 'y'},
  {0x1c, 'z'},
  {0x7f, 127}, // last ascii character "DEL"
  {0xc5, '*'}, //break <BK>

};
void setup() {
  pinMode(Dit, INPUT_PULLUP); // Dit key input pin 11 , ground to send
  pinMode(Dah, INPUT_PULLUP); // Dah key input pin 12 , ground to send
  pinMode(SpcPin, INPUT_PULLUP); // Auto space  set pin A2, HIGH = Auto/  LOW = Manual
  pinMode(spkPin, OUTPUT); // spkPin output logic level, may use 100 ohms to limit current
  pinMode(keyPin, OUTPUT); // key output pin 13, logic level, limited current , use open collector to key rig
  pinMode(WpmPin, INPUT); // WPM set speed of key output pin A1,

  Serial.begin(9600);
  // initialize control over the keyboard:
  Keyboard.begin();
}

/*********************Manual Iambic Keyer  *************************
    This Iambic Keyer is a manual Keyer. It's design hark back to the first Iambic
    Keyers. The early keyer were little more then a couple of timer ICs.
    There was no Memory to catch and save dits or dahs. With this keyer its
    possible to over run the WPM speed adjustment which will cause omissions of code elements.
    To send clean code you must practice proper spacing and adjust the speed to the range of your sending speed.
    The Keyer will allow squeeze keying, without adding a ending dit or dah. Control is left to the operator's timing.
    I found this Keyer forces the operator to properly space code.
    It teaches better fist control and not to rely on the Keyer's memory . 73 Bob
 ********************************************************************/

/*************************************
    check for Iambic paddle press and
   send keyboard.print() to the computer
   using the program with currrent focus
************************************/

void loop() {
  /************* WPM speed  Set  **************/
  CWspeed = analogRead(WpmPin);
  ditLength = ((CWspeed / 1024) * 120) + 30; // 30 was added to adjust pot for mid range
  /************************************/

  ////////// enter a dit ////////////
  if ((digitalRead (Dit)) == 0) {

    if (CWchar == 0)
    {
      CWchar = 1; //CWchar=1;  // This is our start bit
    }
    CWchar = CWchar << 1;  //shift bits left , 0 for dit
    playTone(1); // plays tone and keys radio
    delay(ditLength * 0.2); // debounce
    LetSpc = (ditLength * 7);
    Halt = 0;


  }
  /////// enter a dah ///////////////
  if ((digitalRead (Dah)) == 0) {

    if (CWchar == 0) {
      CWchar = 1; // This is our start bit
    }
    CWchar = CWchar << 1;  //shift bits left
    CWchar++; // adds one for dah
    playTone(3); // plays tone and keys radio
    delay(ditLength * 0.2); // debounce
    LetSpc = (ditLength * 7);
    Halt = 0;
  }


  /******  print character and reset ********/
  LetSpc--;

  if (LetSpc == 0) {
    getLet(CWchar); //end of letter print letter
    CWchar = 0; // reset character to NULL
  }

  /******************   Auto Space for CW practice **************************/
  if ((WDspc == 0) && (digitalRead(SpcPin) == HIGH) && (CWchar == 0) && (Halt == 0)) {
    Keyboard.print(' ');
    Halt = 1 ;
  }
 
  WDspc--;
} // END OF LOOP()


/////////// Play tone & Key radio ////////////////////
void playTone(int Length) {
  tone(spkPin, sideTone); // play tone
  digitalWrite(keyPin, 1); //key radio
  delay(Length * ditLength);// spend Dah length tone
  noTone(spkPin); // tune off tone
  digitalWrite(keyPin, 0); // unkey radio
  delay (ditLength);// add char space

}

/////////////// scan array for character & print to PC focus window /////////////
void getLet(int  y) {
  char keyP;
  int x = 0;

  for (x = 0; x < (sizeof Lray / sizeof Lray[0]); x++)
  {
    if (y == Lray[x].num) {

      Keyboard.print(Lray[x].ch);
      Keyboard.print(keyP);//Keyboard.print(keypressed);//Keyboard.releaseAll(); //10   Keyboard.print(key);
    }
    Keyboard.releaseAll(); //   reset Keyboard, next(key);

    WDspc = (ditLength * 40 );
  }
}

////////////// WPM speed adjust    ///////////////////////////////
int WPM() {
  int x = 0;  // speed val
  x = analogRead(WpmPin);  // read the input pin
  return (x);         // send value back
}
