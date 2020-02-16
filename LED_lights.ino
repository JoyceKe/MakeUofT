int ledcolor = 0;
int a = 200;
int red = 11; 
int green = 12; 
int blue = 13; 

void setup() {

pinMode(red, OUTPUT);
pinMode(green, OUTPUT);
pinMode(blue, OUTPUT);
}

void loop() {
int ledcolor = random(7); //this randomly selects a number between 0 and 6

switch (ledcolor) {
case 0: //if ledcolor equals 0 then the led will turn red
  digitalWrite(red, LOW);
digitalWrite(green, HIGH); 
digitalWrite(blue, HIGH);
delay(a);
break;
case 1: //if ledcolor equals 1 then the led will turn green
digitalWrite(red, HIGH);
digitalWrite(green, LOW); 
digitalWrite(blue, HIGH);
delay(a);

break;
case 2: //if ledcolor equals 2 then the led will turn blue
  digitalWrite(red, HIGH);
digitalWrite(green, HIGH); 
digitalWrite(blue, LOW);
delay(a);

break;
case 3: //if ledcolor equals 3 then the led will turn yellow

analogWrite(red, 0);
analogWrite(green, 125);
digitalWrite(blue, HIGH);
delay(1000);  
break;
case 4: //if ledcolor equals 4 then the led will turn cyan
analogWrite(red, 87);
digitalWrite(blue, LOW);
delay(a);
break;
case 5: //if ledcolor equals 5 then the led will turn magenta
digitalWrite(green, LOW);
digitalWrite(blue, LOW);
delay(a);
break;
case 6: //if ledcolor equals 6 then the led will turn white
analogWrite(red, 0);
digitalWrite(green, LOW);
digitalWrite(blue, LOW);
delay(a);
break;
}}
