#define ENA 11
#define IN1 13
#define IN2 12
#define ANALOG_IN A0


unsigned long t = 0, t0 = 0;
const double setpoint_rpm = 200.0;
double rpm = 0;

const double motorMaxRpm = 300.0;

void calculatePWM();

void setup() {
  Serial.begin(115200);

  pinMode(5, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ANALOG_IN, INPUT);

  interrupts();

  TCCR1A = 0 << COM1A1 | 0 << COM1A0 | 0 << COM1B1 | 0 << COM1B0 | 0 << WGM11 | 0 << WGM10;
  TCCR1B = 0 << ICNC1 | 0 << ICES1 | 0 << WGM13 | 1 << WGM12 | 1 << CS12 | 1 << CS11 | 1 << CS10;
  TIMSK1 = 0 << OCIE1B | 0 << OCIE1A | 0 << TOIE1;
  TCNT1 = 0;

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

/*
  PWM - RPM
  255 - 300
  x   - y
  
  y = (300.0 * x) / 255.0
  x = (255 * y) / 300.00
*/

double P = 0, I = 0, D = 0;
const double kp = 0.984375, ki = 0.009375, kd = 0.0000;
double error = 0;
double control = 0;
unsigned pwm = 0;
double previousError = 0;

void loop() {
  TCNT1 = 0;
  delay(200);
  rpm = (TCNT1 / 209.0 / 0.2 * 60.0);
  calculatePWM();
  analogWrite(ENA, pwm);

  Serial.print(rpm);
  Serial.print('\t');
  Serial.print(setpoint_rpm);
  Serial.print('\t');
  Serial.print(control);
  Serial.print('\t');
  
  Serial.println();
}

void calculatePWM() {
  error = setpoint_rpm - rpm;
  P = error;
  I = I + error;
  D = error - previousError;

  control += P * kp + I * ki + D * kd;
  if(control > 300) control = 300;
  if(control < 0)   control = 0;

  pwm = floor((255.0 * control) / 300.0);
  
  previousError = error;
}
