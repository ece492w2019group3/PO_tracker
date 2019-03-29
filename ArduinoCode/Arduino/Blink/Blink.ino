
    // the onboard LED is attached to pin 13
    int ledPin = 13;
     
    /*
        When the Arduino board is reset, this method is 
        run exactly once.  Its job is to put the board into
        the proper configuration.
    */
    void setup() {
      // configure ledPin to be a digital output
      pinMode(ledPin, OUTPUT);
    }
     
    /*
        An Arduino program is generally not meant to stop.
        It is supposed to keep interacting with its environment.
        The loop method is run over and over until the power
        is removed from the board, or the board is reset.
    */
    void loop() {
      // set the pin to output a HIGH value and turn the LED on
      digitalWrite(ledPin, HIGH);
     
      // wait for 1000 milliseconds
      delay(1000);
     
      // set the pin to output a LOW value and turn the LED off
      digitalWrite(ledPin, LOW);
     
      // wait for 1000 milliseconds
      delay(1000);
    }
