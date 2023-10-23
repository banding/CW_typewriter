#CW typewriter 

The CW typewriter uses an Iambic key as a input device. It acts as the computers keyboard. On it's PCB there's a key input jack, speaker output jack  and uses the Arduino’s USB port for communications with PC.  

Choosing the Arduino Leonardo made communicating with the computer's USB port easy. The Leonardo uses a ATmega32u4 micro-controller which can emulate a keyboard or a mouse. I also tested the Arduino Micro board which uses the same micro controller. The Micro has a small form factor which might be better suited for some projects,  I choose the 16 Mhz, 5 volt version. 

 CW typewriter Features include: inputs  are Iambic (DIT and DAH), a SPACE switch and WPM speed potentiometer. For outputs there are  key (for the rig's key) , speaker for side tone. The side tone frequency is set in the program listing.

For the speaker output I would recommend an amplified speaker. I have an old PC speaker set  Some stations might want to use there rig as a speaker by hooking up the Arduino's key output pin to their rig, caution: the key output is logic level so check your rig's spec.

 The next block of code is a Letter array used to convert Morse code to ASCII. As each CW character is sent  using the Iambic key it is converter to an ASCII character and sent to the keyboard input of the computer. In the Letter array I have added the Morse code pro-sign “AA”  and assigned it to the computer's return key, which adds the ability to sent a return character when needed. 

Additionally other keys can be defined to add additionally characters. Morse code includes pro-signs which seem to make sense for this application. Interestingly I had a handicap ham ask me if this would work with his Sip/Puff Switch.  He uses. He thought it might be fast then the system he currently has setup. 

While we’re talking keyboard emulation it should noted that whatever is sent by the Key is transmitter to the computer . Whichever window  currently has focus. You can inadvertently add characters to a program on you computer. Remember to click the window you want the CW typewriter send to.

I started practice with note pad. I figured if a computer could understand my CW so could a ham. Open notepad window and click inside the window. Now use the Iambic key to send letters, numbers. When you get up to words you can use the space switch to automatically sent a space to the computer when you pause. After a while I found there were typing game on the internet that work with the CW typewriter. Those were fun because they would speed up as the game progressed .

GAME:

I wrote a small command line  C program. It was just a proof of concept test program. 
When using the small command line Practice-program it was necessary to send a return key at the end of each entry.  Reaching over and hitting the return key somehow broke my focus and slow me down. To send the return key I used the Prosign  'AA', (“start new line”). Using the Prosign allowed me to kept my focus on the key, which seem to make my practice go smoother.

So now I was faced with two wants. First was to rewrite my CW typewriter program to eliminate the unnecessary parts not needed for gaming. Second was to write a simple CW game program which used text files as the input like my little Practice-program did. Having the ability to make up text files of  your own choosing was a nice feature I wanted to keep.  Additionally I had a couple of caveats. I wanted to make the code “open source”. Since it's a simple little program I hope others will add to it, or use it as a guide and thereby allow it to grow. Also wanted it to work on the 3 commonly used operating systems, PC, MAC and Linux. Python plays on all these systems and it seemed like a good choice.

