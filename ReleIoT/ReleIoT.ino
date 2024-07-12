// Mapa de pines físicos a números de GPIO
const int D0 = 16;
const int D1 = 5;
const int D2 = 4;
const int D3 = 0;
const int D4 = 2;
const int D5 = 14;
const int D6 = 12;
const int D7 = 13;
const int D8 = 15;
const int D9 = 3;
const int D10 = 1;

const int relayPin = D1; 
const int redPin = D2;   
const int bluePin = D3;  
const int greenPin = D4; 
int value = 0;

void controlVents(char mode) {
  if (mode == '1') {
    digitalWrite(relayPin, HIGH); 
  } else if (mode == '0') {
    digitalWrite(relayPin, LOW); 
  }
}

void controlRGB(char color, char state) {
  int pin;
  switch(color) {
    case 'R': pin = redPin; break;
    case 'G': pin = greenPin; break;
    case 'B': pin = bluePin; break;
    default: return;
  }
  if (state == '1') {
    digitalWrite(pin, HIGH);
  } else if (state == '0') {
    digitalWrite(pin, LOW);
  }
}

void dimLed(int pin, int value) {
  analogWrite(pin, value);
}

void setup() {
  // Establecer los pines del led como salida
  pinMode(relayPin, OUTPUT); 
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.begin(115200);      
  digitalWrite(relayPin, LOW); 
  digitalWrite(redPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(greenPin, LOW);
}

void loop() {

  // dimLed(redPin, value);
  // delay(1000);
  // value += 5;
  // if (value > 255) {
  //   value = 0;
  // }
  if (Serial.available() > 0) {
    char command = Serial.read(); 
    if (command == '1' || command == '0') {
      controlVents(command);
    } else if (command == 'R' || command == 'G' || command == 'B') {
      while (!Serial.available()); // espera el siguiente caracter
      char state = Serial.read();
      if (state == '1' || state == '0') {
        controlRGB(command, state);
      }
    }
  }

}
