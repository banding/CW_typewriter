CW typewriter
 










The CW typewriter is small adapter board that uses an Iambic key as a input device. When plugged into the computer’s USB port it uses the Iambic key as the computer’s keyboard. On the adapter there’s a Iambic key input jack, speaker output jack and uses the Arduino’s USB port for communications with PC. 

Files: CW_typewriter

Choosing the Arduino Leonardo made communicating with the computer easy. The Leonardo uses a ATmega32u4 micro-controller which can emulate a keyboard or a mouse. In this application it only emulates the keyboard. I also tested the Arduino Pro Micro board which uses the same micro controller. The Pro Micro has a small form factor which might be better suited for some projects, I choose the 16 Mhz, 5 volt version.
CW typewriter Features include: inputs are Iambic (DIT on tip and DAH on sleeve), a SPACE switch and WPM speed potentiometer. For outputs there are key (uses the rig’s key input) , speaker for side tone. The side tone frequency is set in the Arduino’s program listing (Sketch_CW_Typewriter, int sideTone = 600; // Frequency in of side tone)

For the speaker output I would recommend an amplified speaker. I have an old PC speaker set Some stations might want to use their rig as a speaker by hooking up the Arduino’s key output jack to their rig‘s key input. CAUTION the key output is logic level so check your rig’s spec. Hooking up  the rig to a dummy load and the rig set rig’s power to low power.

The next block of code is a Letter array “Let Lray[]” used to convert Morse code to ASCII. As each CW character is sent using the Iambic key it is converter to an ASCII character and sent to the computer. In the Letter array I have added the Morse code pro-sign “AA” and assigned it to the computer’s return key, which adds the ability to sent a return character when needed.
Additionally other keys can be defined for make additional characters. Morse code includes pro-signs which seem to make sense for this application. Interestingly a handicap ham ask me if this would work with his Sip/Puff Switch he uses. He thought it might be fast to send morse code then the system he currently has setup. ARRL has an article abiut using the SIP/PUFF switch for sending morse code.

While we’re talking keyboard emulation it should noted that whatever is sent by the Key is transmitter to the computer’s screen. So whichever window currently has focus will receive the characters. You can inadvertently add characters to a document or program listing on you computer. Remember to click the window you want the CW typewriter send to.

I started my CW practice using Windows Note Pad, other OS have text editors as well. I figured if a computer could understand my CW so could a ham. Open notepad window and click inside the window. Now use the Iambic key to send letters, numbers. When you get up to words you can use the space switch to automatically sent a space to the computer when you pause. After using the note pad program to smooth out my CW. I found there were typing lessons and games on the internet that work with the CW typewriter. Those were fun because they would speed up as the game progressed, I enjoyed the balloon game. 

GAMES LOCATED HERE: https://www.typing.com/student/lessons and https://www.typing.com/student/games.

GAME:
After using Note Pad and playing the typing game I they were lacking the ability to change the preprogram charters. I was looking for something to focus my practice with. So I wrote a small command line C program (included in the code files). It was just a proof of concept test program which read from a text file which I could makeup. Using the input texts allowed me to tailor my practice. The text file only had one entry per line. The program would lookup the next line it didn’t care if it was a letter, a number or a word it just grab it and sent it.

When using the small command line Practice-program it was necessary to send a return key at the end of each entry. Reaching over and hitting the return key somehow broke my focus and slowed me down. To eliminate reaching over nd pushing the return key. I added a new character to the Letter array , Pro-sign ‘AA’, (“start new line”). Using the Pro-sign charter allowed me to kept my focus on the key, which seem to make my practice go smoother.

So now I had accumulated two wants:
First was to rewrite my CW typewriter program to eliminate the unnecessary parts not needed for gaming. 
Second was to write a simple CW game program which used text files as the input like my little Practice-program did and eliminate using the return key.  Having the ability to make up text files of your own choosing was a nice feature I wanted to keep. 

Additionally :
 I wanted to make the code “open source”. Since it’s a simple little program I hope others would add to it, or use it as a guide and thereby allow it to grow. 
I also wanted it to work on the 3 commonly used operating systems, PC, MAC and Linux. Python plays on all these systems and it seemed like a good choice.
