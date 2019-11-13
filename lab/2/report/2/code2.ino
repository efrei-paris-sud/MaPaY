//************************************************
//Lecture des données analogiques à partir de LDR
//Groupe MaPaY
//************************************************
const int LDR = A0;  // Broche d'entrée analogique sur laquelle le LDR est fixé
int valeur = 0;  // valeur lue du LDR

void setup() {

  pinMode(LDR, INPUT); // Définir la broche "LDR" comme étant une entrée
  Serial.begin(9600); // initialise les communications série à 9600 bps
}

void loop() {

  valeur = analogRead(LDR);// lire la valeur analogique:

  // imprime les résultats sur le moniteur série:
  Serial.print("Valeur LDR = ");
  Serial.print(valeur);
  Serial.print("   ");
  Serial.println("");
  delay(200); //attendre 200 millisecondes avant la prochaine boucle
}
