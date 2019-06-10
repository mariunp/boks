//Definerer input til komponentene
const int trykkPlateKunde = 4; //Input til trykkplate forran kasse
const int mottakerVibrasjon = 13; //Input til vibrasjonsmotorene i mottakerne
const int trykkPlateAnsatt = 2; //Input til trykkplate bak kasse
const int mottakerKnapp = 12; //Input til knappene i mottakerne

//Variabel som holder på statusen fra mottakerknappene, trykkplate forran kasse, og trykkplaten bak kasse
int mkStatus;
int tpkStatus;
int tpaStatus;

//Variabel som holder på forrige statusen fra mottakerknappene, trykkplate forran kasse, og trykkplaten bak kasse
int forrigemkStatus = LOW;
int forrigetpkStatus = LOW;
int forrigetpaStatus = LOW;

//Variabel som holder på tiden siden forrige knappetrykk
unsigned long mkTid = 0;
unsigned long tpkTid = 0;
unsigned long tpaTid = 0;

//DebounceDelay for mottakerknappene og trykkplate bak kasse
//DebounceDelay er til for å forhinde dobbeltklikk
unsigned long debounceDelay = 50;

//DebounceDelay for trykkplaten forran kasse
unsigned long trykkPlateKundeDelay = 3000;

void setup() {
  //Setter opp komponentene
  pinMode(trykkPlateKunde, INPUT);
  pinMode(mottakerVibrasjon, OUTPUT);
  pinMode(trykkPlateAnsatt, INPUT);
  pinMode(mottakerKnapp, INPUT);
}

void loop() {
  //Debounce mottakerKnapp
  int leseAMKnapp = digitalRead(mottakerKnapp);
  
  if (leseAMKnapp != forrigemkStatus) {
    mkTid = millis();
  }
  
  if ((millis() - mkTid) > debounceDelay) {
    if (leseAMKnapp != mkStatus) {
      mkStatus = leseAMKnapp;
      if (mkStatus == HIGH) {
        digitalWrite(mottakerVibrasjon, LOW);
      }
    }
  }
  
  forrigemkStatus = leseAMKnapp;

  //Debounce trykkPlateAnsatt
  int leseAKKnapp = digitalRead(trykkPlateAnsatt);
  
  if (leseAKKnapp != forrigetpaStatus) {
    tpaTid = millis();
  }
  
  if ((millis() - tpaTid) > debounceDelay) {
    if (leseAKKnapp != tpaStatus) {
      tpaStatus = leseAKKnapp;
      if (tpaStatus == HIGH ) {
        digitalWrite(mottakerVibrasjon, LOW);
      }
    }
  }
  
  forrigetpaStatus = leseAKKnapp;

  //Debounce trykkPlateKunde
  int leseTPKnapp = digitalRead(trykkPlateKunde);
  
  if (leseTPKnapp != forrigetpkStatus) {
    tpkTid = millis();
  }
  
  if ((millis() - tpkTid) > trykkPlateKundeDelay) {
    if (leseTPKnapp != tpkStatus) {
      tpkStatus = leseTPKnapp;
      digitalWrite(mottakerVibrasjon, tpkStatus);
    }
  }
  
  forrigetpkStatus = leseTPKnapp;
}
