/*
void checkSensor()  {

  // check to see current time, which will determine if it is time to blink the LED
  uint64_t delta_t2 = currentMillis - previousMillis2;
  
 // FIRST SENSOR
  if (delta_t2 >= interval2) {

    // FIRST SENSOR (SENSOR ONE)
    // Get temperature event and print its value.
    sensors_event_t event_one;  
    dht_one.temperature().getEvent(&event_one);
    float temp1 = event_one.temperature;
    if (isnan(event_one.temperature)) {
     Serial.println("Error reading temperature for SENSOR ONE!");
    }
   else {
    Serial.print("Temperature (SENSOR_ONE): ");
    Serial.print(event_one.temperature);
    Serial.println(" *C");
    }
    //Get humidity event and print its value.
    dht_one.humidity().getEvent(&event_one);
    float hum1 = event_one.relative_humidity;
    if (isnan(event_one.relative_humidity)) {
      Serial.println("Error reading humidity for SENSOR ONE!");
    }
    else {
     Serial.print("Humidity (SENSOR_ONE): ");
     Serial.print(event_one.relative_humidity);
     Serial.println("%");
   }

    // SECOND SENSOR (SENSOR TWO)
    //Get temperature event and print its value.
    sensors_event_t event_two;  
    dht_two.temperature().getEvent(&event_two);
    float temp2 = event_two.temperature;
    if (isnan(event_two.temperature)) {
      Serial.println("Error reading temperature for SENSOR TWO!");
    }
    else {
      Serial.print("Temperature (SENSOR_TWO): ");
      Serial.print(event_two.temperature);
      Serial.println(" *C");
    }
    // Get humidity event and print its value.
    dht_two.humidity().getEvent(&event_two);
    float hum2 = event_two.relative_humidity;
    if (isnan(event_two.relative_humidity)) {
    Serial.println("Error reading humidity for SENSOR TWO!");
    }
    else {
      Serial.print("Humidity (SENSOR_TWO): ");
      Serial.print(event_two.relative_humidity);
      Serial.println("%");
    }

    // TEMPERATURE DATA FOR THE FAN - using average of temperature and humidity sensor data
    float avgTemp = (temp1 + temp2) / 2;
    float avgHum = (hum1 + hum2) / 2;
    Serial.print("Avg. Temp: ");
    Serial.print(avgTemp);
    Serial.println("*C");
    Serial.print("Avg. Hum: ");
    Serial.print(avgHum);
    Serial.println("%");  

    // FAN UPDATING
    if((avgTemp >= minTemp && avgTemp <= maxTemp) || avgTemp <= (minTemp - marginTemp)){
      analogWrite(fanPWMPin, fanPWMLOW);
    }
    else if(avgTemp >= (maxTemp + marginTemp)){
      analogWrite(fanPWMPin, fanPWMHIGH);
    }
    else{
     analogWrite(fanPWMPin, fanPWMLOW);
    }
      
    currentMillis = previousMillis2;
    } else {
      checkSensor();
    }  
}
*/
