/*
Make practical use of the ability to draw several graphs simultaneously. Connect two photoresistors to the Arduino - we have already done this in other lessons.
Then measure the voltage reflecting the level of light falling on each sensor.
Present both values on a single graph. Brag in the comments with a screenshot showing your graph!
*/

#define PHOTOREISTOR_DOWN A0
#define PHOTOREISTOR_UP A1

void setup()
{
    Serial.begin(9600);
    pinMode(PHOTOREISTOR_DOWN, INPUT);
    pinMode(PHOTOREISTOR_UP, INPUT);
}

float convert_ADC_to_voltage(int adc_read)
{
    float voltage_value = (5 * adc_read) / 1023.0;
    return voltage_value;
}

void plot_voltage_via_teleplot(float photoresistor_down_value, float photoresistor_up_value)
{
    Serial.print(">Brigtness (Photoresistor_down) - Max (5[V]), minimum (0[V]) :"); 
    Serial.println(photoresistor_down_value);
    Serial.print(">Brigtness (Photoresistor_up) - Max (5[V]), minimum (0[V]) :"); 
    Serial.println(photoresistor_up_value);
}

void loop()
{
    float photoresistor_down_value = analogRead(PHOTOREISTOR_DOWN);
    float photoresistor_up_value = analogRead(PHOTOREISTOR_UP);
    photoresistor_down_value = convert_ADC_to_voltage(photoresistor_down_value);
    photoresistor_up_value = convert_ADC_to_voltage(photoresistor_up_value);
    plot_voltage_via_teleplot(photoresistor_down_value, photoresistor_up_value);
    delay(100);
}