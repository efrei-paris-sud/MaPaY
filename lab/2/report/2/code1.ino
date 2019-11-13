//Groupe MaPaY

int buzzer_pin = 12;

void setup()
{
    pinMode(buzzer_pin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available()>0)
    {
        int buzzer_freq = Serial.parseInt();
        write_freq(buzzer_freq);
    }
}

void write_freq(int frequency)
{
        tone(buzzer_pin, frequency, 5000);
        return;
}
