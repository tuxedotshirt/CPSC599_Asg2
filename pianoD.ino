#include <synth.h>

synth chime;

int max0 = 0;

//2D array of frequencies representing C,D,E,F,G and five pitches for each.
int freqs[][5] = {{0,0,0,0,0},
                  {130, 146, 164, 174, 196},
                  {261, 293, 329, 349, 392},
                  {523, 587, 659, 698, 784},
                  {1046, 1174, 1318, 1396, 1567},
                  {2093, 2349, 2637, 2793, 3135}};

//required for tone generation
byte voice = 0;

//library function to generate tone
void play(int freq)
{
  chime.setFrequency(voice, freq);
  chime.trigger(voice);

  voice++;

  if (voice == 4)
  {
    voice = 0;
  }
}

void setup()
{
  Serial.begin(250000);

  chime.begin(CHA);

  //voices determine what the tone sounds like. This produces a bell sound.
  chime.setupVoice(0, SINE, 60, ENVELOPE0, 100, 64);
  chime.setupVoice(1, SINE, 60, ENVELOPE1, 100, 64);
  chime.setupVoice(2, SINE, 60, ENVELOPE2, 100, 64);
  chime.setupVoice(3, SINE, 60, ENVELOPE3, 100, 64);

  //A0 is used for touch sensor input.
  pinMode(A0, INPUT);
}


void loop()
{
  //Initially read the level of analog input pin 0. Play the ascending tones as pressure increases.
  int p0 = analogRead(A0)/200;
  if(p0 > max0){
    max0 = p0;
      play(freqs[max0][1]);
  }

  //When pressure is released from the sensor, play the max tone.
  //This gives the user control over what tone is actually played instead of playing all notes up and down 
  //  corresponding to pressure. 
  else if(analogRead(A0)/200 < max0){
    play(freqs[max0][1]);
    if(analogRead(A0)/200 == 0)
      max0 = 0; //reset max value
  }
}
