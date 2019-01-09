//Author: Bhargav Aparoksham
// Does Basic line following on any given side.


int m1[2] = {2,3};  
int m2[2] = {4,5};    
int m3[2] = {6,7};
int m4[2] = {8,9};

//Note: m[0] -- HIGH => front , m[1] - HIGH => back


int Lm1[2] = {32,34};  
int Lm2[2] = {11,36};    
int Lm3[2] = {12,38};
int Lm4[2] = {40,42};

int sensor1[3] = {0,1,2};
int sensor2[3] = {4,5,6};
int sensor3[3] = {8,9,10};
int sensor4[3] = {12,13,14};

int sensor1_data[3];
int sensor2_data[3];
int sensor3_data[3];
int sensor4_data[3];

int buzzer = 44;

//int rpm1 = 245;
int rpm = 180;
int rpm1 = 245;
int rpm2 = 180;
int rpm3 = 120;
int a;
int i;

int s = 0;
int data_pins[4] = {22,24,26,28} ;
int data[4];

int centroid = 20;
int current_centroid;
float error = 0;
float correction;
float total_error = 0;
float prev_error = 0;

int mean_rpm = 150;
int kp = 5;
int ki = 0.1;
int kd = 0.1;

int junction = 0;
int line = 0;

int num = 0;

void setup()
{
  for(i=0;i<2;i++)
  {
    pinMode(m1[i], OUTPUT);
    pinMode(m2[i], OUTPUT);
    pinMode(m3[i], OUTPUT);
    pinMode(m4[i], OUTPUT);
    
    pinMode(Lm1[i], OUTPUT);
    pinMode(Lm2[i], OUTPUT);
    pinMode(Lm3[i], OUTPUT);
    pinMode(Lm4[i], OUTPUT);    
    
    pinMode(buzzer , OUTPUT);
  }
  
   for(i=0;i<4;i++)
   {
     pinMode(data[i] ,OUTPUT);
   }
  
  Serial.begin(9600);
}

void loop()
{
  
/* mov_fwd();
 delay(1500);
 stp();
 delay(3000);
 mov_bwd();
 delay(1500);
 stp();
 delay(3000);*/
// Lift();
 


 
 /* data_read();
  data_process();
  //Serial.println();
  delay(50);*/
 // Lift_clk();

  if(junction == 3)
  {
    stp();
    delay(5000);

  }
  sensorRead(1);
  PIDcontrol(1);



  
 // sensorRead(1);
 // sensorRead(2);
  //sensorRead(3);
 // sensorRead(4);
  delay(10);
  
}

void stp()
{
  analogWrite(m1[0] , s); 
  analogWrite(m1[1] , s); 
  analogWrite(m2[0] , s); 
  analogWrite(m2[1] , s);
  analogWrite(m3[0] , s);
  analogWrite(m3[1] , s);
  analogWrite(m4[0] , s);
  analogWrite(m4[1] , s);
}

void  rotate_clk()
{
  analogWrite(m1[1] , rpm3); 
  analogWrite(m2[0] , rpm3);
  analogWrite(m3[0] , rpm3);
  analogWrite(m4[1] , rpm3);
}
  
void rotate_anti_clk()
{
  analogWrite(m1[0] , rpm3); 
  analogWrite(m2[1] , rpm3);
  analogWrite(m3[1] , rpm3);
  analogWrite(m4[0] , rpm3);  
}

void mov_fwd()
{
  analogWrite(m1[0] , rpm2); 
  analogWrite(m2[0] , rpm);
  analogWrite(m3[0] , rpm2);
  analogWrite(m4[0] , rpm);
}

void mov_bwd()
{
  analogWrite(m1[1] , rpm2); 
  analogWrite(m2[1] , rpm);
  analogWrite(m3[1] , rpm2);
  analogWrite(m4[1] , rpm);
}

void mov_rgt()
{
  analogWrite(m1[1] , rpm2); 
  analogWrite(m2[0] , rpm);
  analogWrite(m3[1] , rpm2);
  analogWrite(m4[0] , rpm);
}

void mov_lft()
{
  analogWrite(m1[0] , rpm2); 
  analogWrite(m2[1] , rpm);
  analogWrite(m3[0] , rpm2);
  analogWrite(m4[1] , rpm);
}

void mov_NE()
{
  analogWrite(m1[0] , s); 
  analogWrite(m2[0] , rpm);
  analogWrite(m3[0] , s);
  analogWrite(m4[0] , rpm);
}

void mov_NW()
{
  analogWrite(m1[0] , rpm); 
  analogWrite(m2[0] , s);
  analogWrite(m3[0] , rpm);
  analogWrite(m4[0] , s);
}

void mov_SE()
{
  analogWrite(m1[1] , rpm); 
  analogWrite(m2[1] , s);
  analogWrite(m3[1] , rpm);
  analogWrite(m4[1] , s);
}

void mov_SW()
{
  analogWrite(m1[1] , s); 
  analogWrite(m2[1] , rpm);
  analogWrite(m3[1] , s);
  analogWrite(m4[1] , rpm);
}

void data_read()
{
  for(i=0;i<4;i++)
  {
    data[i] = digitalRead(data_pins[i]);
   // Serial.println(data[i]);
    delay(50);
  }
}

void data_process()
{
  if((data[0] == 0) && (data[1] == 0) && (data[2] == 0) && (data[3] == 0))                 // 0
  {
    stp();
  }
  
  if((data[0] == 1) && (data[1] == 0) && (data[2] == 0) && (data[3] == 0))                  // 1
  {
    mov_NW();
  }
  
  if((data[0] == 0) && (data[1] == 1) && (data[2] == 0) && (data[3] == 0))                 // 2
  {
    mov_fwd();
  }
  
  if((data[0] == 1) && (data[1] == 1) && (data[2] == 0) && (data[3] == 0))                 // 3
  {
    mov_NE();
  }
  
  if((data[0] == 0) && (data[1] == 0) && (data[2] == 1) && (data[3] == 0))                // 4
  {
    rotate_clk();
  }
  
  if((data[0] == 1) && (data[1] == 0) && (data[2] == 1) && (data[3] == 0))                // 5
  {
    mov_lft();
  }
  
  if((data[0] == 0) && (data[1] == 1) && (data[2] == 1) && (data[3] == 0))                // 6
  {
    stp();
  }
  
  if((data[0] == 1) && (data[1] == 1) && (data[2] == 1) && (data[3] == 0))                // 7
  {
    mov_rgt();
  }
  
  if((data[0] == 0) && (data[1] == 0) && (data[2] == 0) && (data[3] == 1))               // 8
  {
    rotate_anti_clk();
  }
  
  if((data[0] == 1) && (data[1] == 0) && (data[2] == 0) && (data[3] == 1))              // 9
  {
    mov_SW();
  }
  
  if((data[0] == 0) && (data[1] == 1) && (data[2] == 0) && (data[3] == 1))             // 10
  {
    mov_bwd();
  }
  
  if((data[0] == 1) && (data[1] == 1) && (data[2] == 0) && (data[3] == 1))             // 11
  {
    mov_SE();
  }
  
  if((data[0] == 0) && (data[1] == 0) && (data[2] == 1) && (data[3] == 1))            // 12
  {
    stp();
  }
  
  if((data[0] == 1) && (data[1] == 0) && (data[2] == 1) && (data[3] == 1))           // 13
  {
    stp();
  }
  
  if((data[0] == 0) && (data[1] == 1) && (data[2] == 1) && (data[3] == 1))           // 14
  {
    stp();
  }
  
  if((data[0] == 1) && (data[1] == 1) && (data[2] == 1) && (data[3] == 1))           // 15
  {
    stp();
  } 
  
}  



void Lift_clk()
{
  digitalWrite(Lm1[0] , HIGH); 
  analogWrite(Lm2[0] , rpm1);
  analogWrite(Lm3[0] , rpm1);
  digitalWrite(Lm4[0] , HIGH);
}


void Lift_stp()
{
  digitalWrite(Lm1[0] , HIGH); 
  digitalWrite(Lm1[1] , LOW); 
  analogWrite(Lm2[0] , 0); 
  digitalWrite(Lm2[1] , LOW);
  analogWrite(Lm3[0] , 0);
  digitalWrite(Lm3[1] , LOW);
  digitalWrite(Lm4[0] , LOW);
  digitalWrite(Lm4[1] , LOW);
}

void buzz()
{
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
}

void Lift()
{
  Lift_clk();
 delay(3000);
 Lift_stp();
 delay(5000);
 Lift_clk();
 delay(3000);
 Lift_stp();
 delay(5000);
}

void sensorRead(int p)
{
  if(p==1)
  {
   for(i=0;i<3;i++)
   {
     sensor1_data[i] = analogRead(sensor1[i]);
     if(sensor1_data[i] > 700)
     {
       sensor1_data[i] = 0;
     }
     else
     {
       sensor1_data[i] = 1;
     }
   // Serial.println(sensor1_data[i]);
    delay(10);
   }
  // Serial.println();
  }
  if(p==2)
  {
    for(i=0;i<3;i++)
    {
     sensor2_data[i] = analogRead(sensor2[i]);
     if(sensor2_data[i] > 700)
     {
       sensor2_data[i] = 0;
     }
     else
     {
       sensor2_data[i] = 1;
     }
   // Serial.println(sensor2_data[i]);   
    delay(10);
    }
   // Serial.println();
  }
 if(p==3)
 {
   for(i=0;i<3;i++)
   {
    sensor3_data[i] = analogRead(sensor3[i]);
    if(sensor3_data[i] >700)
    {
      sensor3_data[i] = 0;
    }
    else
    {
      sensor3_data[i] = 1;
    }
    //Serial.println(sensor3_data[i]);
    delay(10);
   }
  // Serial.println();
 }
 if(p==4)
 {
    for(i=0;i<3;i++)
    {
    sensor4_data[i] = analogRead(sensor4[i]);
    if(sensor4_data[i] > 700)
    {
      sensor4_data[i] = 0;
    }
    else
    {
      sensor4_data[i] = 1;
    }
   // Serial.println(sensor4_data[i]);
    delay(10);
   }
  // Serial.println();
 }
 
    delay(10);
}
 


void PIDcontrol(int q)
{
  int sum = 0;
  int mass = 0;
  int rgt_motor_rpm =0;
  int lft_motor_rpm =0;
  
  for(i=0;i<3;i++)
  {
    if(q == 1)
    {
    mass += sensor1_data[i];
    sum += sensor1_data[i]*(i+1)*10;
    }
    
    if(q == 2)
    {
    mass += sensor2_data[i];
    sum += sensor2_data[i]*(i+1)*10;
    }
    
    if(q == 3)
    {
    mass += sensor3_data[i];
    sum += sensor3_data[i]*(i+1)*10;
    }
    
    if(q == 4)
    {
    mass += sensor4_data[i];
    sum += sensor4_data[i]*(i+1)*10;
    }
  }
    
      
  
 // Serial.println(mass);
 // Serial.println(sum);
  if(mass == 1 || mass == 2) line = 1;
  if(mass==3 && line ==1) 
    {
      junction++;
      line =0;
    }
   current_centroid = sum/mass;
   error = (current_centroid - centroid) ;
   //Serial.println(error);
   correction = kp*error + kd*(error - prev_error);
   //total_error += correction;
   prev_error = error;
   if(mass==0) correction = 50;
   rgt_motor_rpm = mean_rpm - correction;
   lft_motor_rpm = (mean_rpm + correction);
  // Serial.println(rgt_motor_rpm);
   //Serial.println(lft_motor_rpm);
  if(q==1)
  { 
  analogWrite(m1[0] , rgt_motor_rpm); 
  analogWrite(m2[0] , lft_motor_rpm);
  analogWrite(m3[0] , lft_motor_rpm);
  analogWrite(m4[0] , rgt_motor_rpm);
  }
  
  if(q==2)
  {
  analogWrite(m1[1] , lft_motor_rpm); 
  analogWrite(m2[0] , rgt_motor_rpm);
  analogWrite(m3[1] , lft_motor_rpm);
  analogWrite(m4[0] , rgt_motor_rpm);
  }
  
  if(q==3)
  {
  analogWrite(m1[1] , rgt_motor_rpm); 
  analogWrite(m2[1] , lft_motor_rpm);
  analogWrite(m3[1] , rgt_motor_rpm);
  analogWrite(m4[1] , lft_motor_rpm);
  }  
  
  if(q==4)
  {
  analogWrite(m1[0] , lft_motor_rpm); 
  analogWrite(m2[1] , rgt_motor_rpm);
  analogWrite(m3[0] , lft_motor_rpm);
  analogWrite(m4[1] , rgt_motor_rpm);
  }
    
  delay(10);
}
   
  
  
