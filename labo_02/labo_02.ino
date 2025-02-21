// TEMATIO TSAKENG
// DA: 2407822

unsigned long currentTime = 0;
const int POTEN_PIN = A1;
const int BUTTON_PIN = 2;
const int LED_COUNT = 4;
const int PROGRESS_BAR_LENGTH = 20;
const int LED_PIN[LED_COUNT] = { 8, 9, 10, 11 };
int MAP_VALUE = 0;
int POTEN_VALUE = 0;
int multiplicateur = 5;
int valeurMinPotent = 0;
int valeurMaxPotent = 1023;
int valeurPourcentage = 100;  // la valeur du pourcentage à afficher sur la LED
int echelle = 20;

int estClic(unsigned long ct) {
  static unsigned long lastTime = 0;
  static int lastState = HIGH;
  const int rate = 50;
  int clic = 0;

  if (ct - lastTime < rate) {
    return clic;  // Trop rapide
  }

  lastTime = ct;

  int state = digitalRead(BUTTON_PIN);

  if (state == LOW && lastState == HIGH) {
    clic = 1;
  }

  lastState = state;
  return clic;
}

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PIN[i], OUTPUT);
  }

  Serial.println("Setup completed");
}

void loop() {
  currentTime = millis();
  AllumerLed();
  afficherBarre();
}
void AllumerLed() {
  POTEN_VALUE = analogRead(POTEN_PIN);
  MAP_VALUE = map(POTEN_VALUE, valeurMinPotent, valeurMaxPotent, valeurMinPotent, echelle);

  for (int i = 0; i <= LED_COUNT; i++) {
    if (MAP_VALUE > (i * multiplicateur)) {
      digitalWrite(LED_PIN[i], HIGH);
    } else {
      digitalWrite(LED_PIN[i], LOW);
    }
  }
}
void afficherBarre() {

  int pourcentage = map(POTEN_VALUE, valeurMinPotent, valeurMaxPotent, valeurMinPotent, valeurPourcentage);

  if (estClic(currentTime)) {
    Serial.print("[");
    for (int i = 0; i < PROGRESS_BAR_LENGTH; i++) {
      if (i < MAP_VALUE) {
        Serial.print("#");
      } else {
        Serial.print(".");
      }
    }
    Serial.print("] ");
    Serial.print(pourcentage);
    Serial.println("%");
  }
}
