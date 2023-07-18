#include <LiquidCrystal.h>
#include "DHT.h"

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
const int relay_Pin = 8;
const int DHT11_Sesnor = 9;
const int moisture_sensor = A0;
const int rain_Sesnor = A1;

#define DHTTYPE DHT11
int moisture_sensor_value;
int rain_Sesnor_value;
float humudity_value, temprature_value;
DHT dht(DHT11_Sesnor, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println("\t\t\t\t\t\t\t\t\tSVIST\n");
  Serial.println("\t\t\t\t\t\t\t\tSmart Irrigation System\n");
  Serial.println("\t\t\t\t\t\t\t\t -presented by PRIME-5\n\n\n");
  pinMode(relay_Pin, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Smart Irrigation ");
  lcd.setCursor(0, 2);
  lcd.print(" SYSTEM");
  digitalWrite(relay_Pin, LOW);
  dht.begin();
  delay(1000);
}
void loop()
{

  readDTH11_Sesnor();
  moisture_level_detected();
  water_motor_start();
}

void readDTH11_Sesnor()
{

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humudity_value = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temprature_value = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humudity_value) || isnan(temprature_value))
  {
    Serial.println(("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print((" Humidity: "));
  Serial.print(humudity_value);
  Serial.print(("%"));
  lcd.clear();
  lcd.print("Humidity %: ");
  lcd.setCursor(0, 2);
  lcd.print(humudity_value);
  Serial.print("\n");
  delay(1000);
  Serial.print(("Temperature: "));
  Serial.print(temprature_value);
  Serial.print(("C "));
  lcd.clear();
  lcd.print("Temperature degCel");
  lcd.setCursor(0, 2);
  lcd.print(temprature_value);
  Serial.print("\n");
  delay(1000);
}

void moisture_level_detected()
{

  moisture_sensor_value = analogRead(moisture_sensor);
  Serial.println("Moisture Level : ");
  Serial.println(moisture_sensor_value);
  lcd.clear();
  lcd.print("Moisture Level :");
  lcd.setCursor(0, 2);
  lcd.print(moisture_sensor_value);
  delay(2000);
}

void water_motor_start()
{

  rain_Sesnor_value = analogRead(rain_Sesnor);
  Serial.print("rain sensor value :: ");
  Serial.println(rain_Sesnor_value);
  delay(1000);
  if (rain_Sesnor_value > 700)
  {
    if (moisture_sensor_value > 700)
    {
      digitalWrite(relay_Pin, HIGH);
      delay(2000);
    }
    else
    {
      digitalWrite(relay_Pin, LOW);
      delay(2000);
    }
  }
  else
  {
    digitalWrite(relay_Pin, LOW);
    delay(2000);
  }
}
