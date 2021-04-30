double Kp=15;
double Ki=8;
double Kd=7;
double KP=24.3;

unsigned long current_time, prev_time;
double elapsed_time;
double error=0;
double last_error=0;
double input, output, setpoint;
double cum_error, rate_error;
double valve_time=1;

int T = 5;
int p;
void setup() {
  
  Serial.begin(9600);
setpoint=50*1000;
}

void loop() {
 
    input=analogRead(A1);
    int y= input*142*1000;
 analogWrite(A2,input);
    output=computePID(y);
    
    delay(1000);
}
double computePID(double inp)
{
  current_time=millis();
  elapsed_time=(current_time-prev_time);
  error=setpoint-inp;
  cum_error += (error*elapsed_time)/1000;
  rate_error = ((error-last_error)*1000)/elapsed_time;

  double out = Kp*error + Ki*cum_error + Kd*rate_error;
  //double out =Kp*error;
  
  float flowrate;
  flowrate= (KP)*1000/(valve_time*out);
  Serial.println(error);
  //Serial.println(flowrate,5);
  last_error = error;
  prev_time = current_time;

 

p=flowrate*255;
//Serial.println(p);
  analogWrite(A3,p);

   if(A3==HIGH)
   {
    analogWrite(A4,HIGH);
    }
//   if(error<20000)
//   {
//    flowrate=0;
//   }
   return flowrate;

   
  }
