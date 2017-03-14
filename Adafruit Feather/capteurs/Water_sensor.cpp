/*macro definition of water sensor and the buzzer*/
#define WATER_SENSOR 12

void setup()
{
    pins_init();
}
void loop()
{
    isExposedToWater();
}

void pins_init()
{
    pinMode(WATER_SENSOR, INPUT);
}

/************************************************************************/
/*Function: Determine whether the sensor is exposed to the water        */
/*Parameter:-void                                                       */
/*Return:   -boolean,if it is exposed to the water,it will return true. */
/************************************************************************/
boolean isExposedToWater()
{
    if(digitalRead(WATER_SENSOR) == LOW){
       Serial.print("Immerge\n");
      return true;
    }
    else{
      Serial.print("Hors de l'eau\n");
      return false;
    }
}
