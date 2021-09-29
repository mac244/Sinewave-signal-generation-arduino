

#define DAC A0 //define DAC0/A0 pin 
#define buffersize 400 // array size for the sine wave points

int f = 20  ; // signal frequency (Hz)
float  fs= (400.0); //Sampling Frequency

int samplingdelay = 1/ ((int)fs); // time delay between sample points
int sig[buffersize]; // to store signal 
const float pi = 3.14;
float t; 
int const resolution = 10 ; // 10 bits max DAC on Arduino WiFi 1010
float maxBitVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // make our digital pin an output
  //pinMode(DAC, OUTPUT);   // generate sinusouidal signal
  maxBitVal = pow(2,resolution); // 2^10
  for(int i = 0; i<buffersize; i++)
  {
    t = ((float)i)/fs; // timeline of discretized sinewave
    sig[i]= (int)((((float)(maxBitVal/2)*0.6 ))*((sin(2*pi*f*t))+1.08)); //  (0-2)Vpp for amplifier
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i<buffersize; i++)
    {
      analogWriteResolution(resolution);
      analogWrite(DAC,sig[i]);
      delay((1/fs)*1000); // sampling interval in ms ,
      Serial.println(sig[i]);
      //Serial.println(sig);
    }
}
