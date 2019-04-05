/*  Example program which sends a lowercase word followed by an x and y 
 *  coordinate, separated by spaces. The baudrate is set to 9600, which
 *  should be the same value as the baudrate used by server.js. There is
 *  a 500ms delay between outputs.
*/
int index;
void setup() {
  int baudrate = 9600;
  Serial.begin(baudrate);
  randomSeed(analogRead(0));
  index = 0;
}

void loop() {
  Serial.println("one " + String(index + 1) + " " + String(0.01*random(1, 10)));
  delay(500);
  Serial.println("two " + String(index + 2) + " " + String(0.01*random(1, 10)));
  delay(500);
  Serial.println("three " + String(index + 3) + " " + String(0.01*random(1,10)));
  delay(500);
  index += 3;
}
