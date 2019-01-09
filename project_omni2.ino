// m[0] -- HIGH => front , m[1] - HIGH => back

// lifting included

int m1[2] = {2,3};  
int m2[2] = {4,5};    
int m3[2] = {6,7};
int m4[2] = {8,9};

int Lm1[2] = {32,34};  
int Lm2[2] = {11,36};    
int Lm3[2] = {12,38};
int Lm4[2] = {40,42};

int buzzer = 44;

//int rpm1 = 245;
int rpm = 175;
int rpm1 = 235;
int rpm2 = 140;
int rpm3 = 120;
int a;
int i;

int s = 0;
int data_pins[4] = {22,24,26,28} ;
int data[4];


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
 


  /*digitalWrite(Lm1[0] , HIGH); 
  analogWrite(Lm2[0] , 235);
  analogWrite(Lm3[0] , 235);
  digitalWrite(Lm4[0] , HIGH);*/

 
  data_read();
  data_process();
  //Serial.println();
  delay(50);
  
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
