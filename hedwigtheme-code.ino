#include <LiquidCrystal.h>

// ---- PINOS DOS LEDS ----
int led_pin1 = 2;
int led_pin2 = 4;
int led_pin3 = 3;

// ---- BUZZER ----
int buzzer_pin = 7;

// ---- LCD ----
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// ---- Estrutura das Notas ----
struct MusicStruct {
  int A = 550;
  int As = 582;
  int B = 617;
  int C = 654;
  int Cs = 693;
  int D = 734;
  int Ds = 777;
  int E = 824;
  int F = 873;
  int Fs = 925;
  int G = 980;
  int Gs = 1003;
  int A2 = 1100;
  int A2s = 1165;
  int B2 = 1234;
  int C3 = 1308;
  int C3s = 1385;
  int D3 = 1555;
} Music;

// ---- Estrutura dos Tempos ----
struct LengthStruct {
  float half = 0.5;
  float one = 1.0;
  float one_half = 1.5;
  float two = 2.0;
  float two_half = 2.5;
} Length;

int tempo = 400;

// ---- TEXTO PARA ROLAR CONSTANTEMENTE ----
String msg = "   Tocando musica - Hedwig's Theme   ";
unsigned long lastScroll = 0;
int scrollInterval = 250;  // velocidade da rolagem independente

void setup() {

  pinMode(led_pin1, OUTPUT);
  pinMode(led_pin2, OUTPUT);
  pinMode(led_pin3, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print(msg.substring(0, 16));
  lcd.setCursor(0, 1);
  lcd.print("Hedwig's Theme");
}

// ---- FUNÇÃO 1: LEDs sequenciais ----
void acendeLedSequencial(int step) {
  int pos = (step - 1) % 3;

  digitalWrite(led_pin1, pos == 0 ? HIGH : LOW);
  digitalWrite(led_pin2, pos == 1 ? HIGH : LOW);
  digitalWrite(led_pin3, pos == 2 ? HIGH : LOW);
}

// ---- FUNÇÃO 2: ROLAGEM DO LCD SEM PARAR A MÚSICA ----
void atualizaLCD() {
  if (millis() - lastScroll >= scrollInterval) {
    lcd.scrollDisplayLeft();
    lastScroll = millis();
  }
}

// ---- FUNÇÃO 3: tocar nota + acender LED, mas LCD rola sozinho ----
void setToneAndLed(int pin, int note, int duration, int step) {

  acendeLedSequencial(step);

  tone(pin, note, duration);
  unsigned long start = millis();
  
  while (millis() - start < (unsigned long)duration) {
    atualizaLCD();  // LCD continua rolando enquanto a nota toca
  }

  noTone(pin);
}

void loop() {

  int step = 1;

  setToneAndLed(buzzer_pin, Music.B,  tempo * Length.one,       step++);
  setToneAndLed(buzzer_pin, Music.E,  tempo * Length.one_half,  step++);
  setToneAndLed(buzzer_pin, Music.G,  tempo * Length.half,      step++);
  setToneAndLed(buzzer_pin, Music.F,  tempo * Length.one,       step++);
  setToneAndLed(buzzer_pin, Music.E,  tempo * Length.two,       step++);
  setToneAndLed(buzzer_pin, Music.B2, tempo * Length.one,       step++);
  setToneAndLed(buzzer_pin, Music.A2, tempo * Length.two_half,  step++);
  setToneAndLed(buzzer_pin, Music.Fs, tempo * Length.two_half,  step++);
  setToneAndLed(buzzer_pin, Music.E,  tempo * Length.one_half,  step++);
  setToneAndLed(buzzer_pin, Music.G,  tempo * Length.half,      step++);
  setToneAndLed(buzzer_pin, Music.F,  tempo * Length.one,       step++);
  setToneAndLed(buzzer_pin, Music.Ds, tempo * Length.two,       step++);
  setToneAndLed(buzzer_pin, Music.F,  tempo * Length.one,       step++);
  setToneAndLed(buzzer_pin, Music.B,  tempo * Length.two_half,  step++);

  // LCD continua rolando inclusive durante esse delay
  unsigned long t = millis();
  while (millis() - t < 1500) {
    atualizaLCD();
  }
}