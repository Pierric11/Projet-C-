#include <LiquidCrystal.h>

// Broches de l'écran LCD
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Broches des boutons
#define BTN_DOWN 9
#define BTN_UP 8
#define BTN_LEFT 10
#define BTN_OK_RIGHT 11

// Broches des LEDs
#define GREEN_LED 13
#define RED_LED 12

// État du jeu
enum States { START_GAME, START, PAUSE_1, ENIGME_1, TEST_CODE_1, PAUSE_2, FLECHE_SEQUENCE, REPONSE_FLECHE, GAME_OVER };
States state = START_GAME;

// Définition des symboles de flèches
const char* fleches[] = {"^", "V", "<-", "->"};
// Indices des flèches pour la comparaison (doivent correspondre à l'ordre de saisie)
// ^:0, V:1, <-:2, ->:3

// Fonction pour afficher un symbole de flèche aléatoire sur l'écran LCD en fonction de l'index
void FlecheAleatoire(int index) {
    lcd.clear();
    lcd.print(fleches[index]);
}

int userCode[4] = {0};
int correctCode[4] = {1, 2, 3, 4};
int codeIndex = 3;
bool codeModified = false;

unsigned long lastButtonPress = 0;
unsigned long debounceDelay = 500; // Augmentation du debounceDelay
unsigned long errorDelay = 2000;

// Variables pour la séquence de flèches
int sequenceFleches[4];
int reponseFleches[4];
int indexFleche = 0;
bool validationEnCours = false; // Nouvelle variable pour éviter les validations multiples

void setup() {
    Serial.begin(9600);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_LEFT, INPUT_PULLUP);
    pinMode(BTN_OK_RIGHT, INPUT_PULLUP);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    lcd.begin(16, 2);
    lcd.print("Appuyez sur OK");
    randomSeed(millis()); // Initialisation du générateur de nombres aléatoires
}

void loop() {
    bool codeCorrect = true; // Déclaration et initialisation ici
    int previousFleche = -1; // Déclaration de previousFleche ici

    switch (state) {
      case START_GAME:
      		if (digitalRead(BTN_OK_RIGHT) == LOW){
        		lcd.clear();
              	lcd.print("Enigme 1 -> OK");
                state = START;
            }
      		break;
      
      case START:
      		if (digitalRead(BTN_OK_RIGHT) == HIGH){
      			state = PAUSE_1;
            }
      		break;
      
      case PAUSE_1:
            if (digitalRead(BTN_OK_RIGHT) == LOW && millis() - lastButtonPress > debounceDelay) {
                state = ENIGME_1;
                lcd.clear();
            	lcd.print("Code:");
            	lcd.setCursor(0, 1);
            	lcd.print("0000");
            	codeIndex = 3;
                lastButtonPress = millis();
            }
            break;

        case ENIGME_1:
            if (digitalRead(BTN_UP) == LOW && millis() - lastButtonPress > debounceDelay) {
                userCode[codeIndex]++;
                if (userCode[codeIndex] > 9) {
                    userCode[codeIndex] = 0;
                }
                lcd.setCursor(codeIndex, 1);
                lcd.print(userCode[codeIndex]);
                lastButtonPress = millis();
                codeModified = true;
            }

            if (digitalRead(BTN_LEFT) == LOW && millis() - lastButtonPress > debounceDelay) {
                codeIndex--;
                if (codeIndex < 0) {
                    codeIndex = 0;
                }
                lastButtonPress = millis();
            }

            if (digitalRead(BTN_OK_RIGHT) == LOW && millis() - lastButtonPress > debounceDelay && codeModified) {
                state = TEST_CODE_1;
                lcd.clear();
                lastButtonPress = millis();
            }
            break;

        case TEST_CODE_1:
            for (int i = 0; i < 4; i++) {
                if (userCode[i] != correctCode[i]) {
                    codeCorrect = false;
                    break;
                }
            }

            if (codeCorrect) {
                digitalWrite(GREEN_LED, HIGH);
                lcd.print("Correct !");
              	lcd.setCursor(0, 1);
            	lcd.print("Tirer carte 8");
                delay(errorDelay);
                digitalWrite(GREEN_LED, LOW);
                state = PAUSE_2;
                lcd.clear();
                lcd.print("Enigme 2 -> OK");
                validationEnCours = false; // Réinitialiser ici aussi, au cas où on revient directement
            } else {
                digitalWrite(RED_LED, HIGH);
                lcd.print("Faux !");
                delay(errorDelay);
                digitalWrite(RED_LED, LOW);
                state = PAUSE_1;
                lcd.clear();
                lcd.print("Enigme 1 -> OK");
                validationEnCours = false; // Réinitialiser ici
            }
            break;
      
        case PAUSE_2:
      		if (digitalRead(BTN_OK_RIGHT) == LOW && millis() - lastButtonPress > debounceDelay) {
              state = FLECHE_SEQUENCE;
            }
      		break;

        case FLECHE_SEQUENCE:
            lcd.clear();
            lcd.print("Memorisez:");
            delay(1000);
            Serial.println("Etat: FLECHE_SEQUENCE"); // Ajout pour vérification
            previousFleche = -1; // Réinitialiser previousFleche à chaque nouvelle séquence
            for (int i = 0; i < 4; i++) {
                int currentFleche;
                do {
                    currentFleche = random(4);
                } while (currentFleche == previousFleche); // Répéter jusqu'à obtenir une flèche différente de la précédente

                sequenceFleches[i] = currentFleche;
                FlecheAleatoire(currentFleche); // Utiliser la nouvelle fonction
                Serial.print("Sequence ["); Serial.print(i); Serial.print("]: ");
                if (sequenceFleches[i] == 0) Serial.println("^ (0)");
                else if (sequenceFleches[i] == 1) Serial.println("V (1)");
                else if (sequenceFleches[i] == 2) Serial.println("<- (2)");
                else if (sequenceFleches[i] == 3) Serial.println("-> (3)");
                delay(1000);
                previousFleche = currentFleche; // Mettre à jour la flèche précédente
            }
            indexFleche = 0;
            state = REPONSE_FLECHE;
            lcd.clear();
            lcd.print("Reponse:");
            break;

        case REPONSE_FLECHE:

            if (indexFleche < 4) {
                if (digitalRead(BTN_UP) == LOW && millis() - lastButtonPress > debounceDelay) {
                    reponseFleches[indexFleche] = 0; // ^
                    lastButtonPress = millis();
                    indexFleche++;
                    delay(debounceDelay);
                    Serial.print("Reponse ["); Serial.print(indexFleche); Serial.print("]: ^ (0) enregistré\n");
                } else if (digitalRead(BTN_OK_RIGHT) == LOW && millis() - lastButtonPress > debounceDelay) {
                    reponseFleches[indexFleche] = 3; // ->
                    lastButtonPress = millis();
                    indexFleche++;
                    delay(debounceDelay);
                    Serial.print("Reponse ["); Serial.print(indexFleche); Serial.print("]: -> (3) enregistré\n");
                } else if (digitalRead(BTN_LEFT) == LOW && millis() - lastButtonPress > debounceDelay) {
                    reponseFleches[indexFleche] = 2; // <-
                    lastButtonPress = millis();
                    indexFleche++;
                    delay(debounceDelay);
                    Serial.print("Reponse ["); Serial.print(indexFleche); Serial.print("]: <- (2) enregistré\n");
                } else if (digitalRead(BTN_DOWN) == LOW && millis() - lastButtonPress > debounceDelay) {
                    reponseFleches[indexFleche] = 1; // V
                    lastButtonPress = millis();
                    indexFleche++;
                    delay(debounceDelay);
                    Serial.print("Reponse ["); Serial.print(indexFleche); Serial.print("]: V (1) enregistré\n");
                }
            }

            if (indexFleche == 4 && !validationEnCours) {
                validationEnCours = true; // Empêcher la validation multiple
                Serial.println("Validation de la reponse:");
                for (int i = 0; i < 4; i++) {
                    Serial.print("Sequence["); Serial.print(i); Serial.print("]: ");
                    if (sequenceFleches[i] == 0) Serial.print("^ (0)");
                    else if (sequenceFleches[i] == 1) Serial.print("V (1)");
                    else if (sequenceFleches[i] == 2) Serial.print("<- (2)");
                    else if (sequenceFleches[i] == 3) Serial.print("-> (3)");
                    Serial.print(", Reponse["); Serial.print(i); Serial.print("]: ");
                    Serial.println(reponseFleches[i]);
                }

                // NOUVELLE TRACE DE DÉBOGAGE :
                Serial.print("Tableau sequenceFleches: [");
                for (int i = 0; i < 4; i++) {
                    Serial.print(sequenceFleches[i]);
                    if (i < 3) Serial.print(", ");
                }
                Serial.println("]");

                Serial.print("Tableau reponseFleches: [");
                for (int i = 0; i < 4; i++) {
                    Serial.print(reponseFleches[i]);
                    if (i < 3) Serial.print(", ");
                }
                Serial.println("]");

                bool reponseCorrecte = true;
                for (int i = 0; i < 4; i++) {
                    if (reponseFleches[i] != sequenceFleches[i]) {
                        reponseCorrecte = false;
                        break;
                    }
                }

                if (reponseCorrecte) {
                    digitalWrite(GREEN_LED, HIGH);
                    lcd.clear();
                    lcd.print("Gagné");
                  	delay(errorDelay);
                    lcd.clear();
                    lcd.print("Tirer carte 4");
                    state = GAME_OVER;
                } else {
                    digitalWrite(RED_LED, HIGH);
                    lcd.print("Faux");
                    delay(errorDelay);
                    digitalWrite(RED_LED, LOW);
                    state = FLECHE_SEQUENCE;
                    lcd.clear();
                    validationEnCours = false; // Réinitialisation ici !
                }
                lastButtonPress = millis();
            }
            break;

        case GAME_OVER:
            delay(errorDelay);
      		lcd.clear();
            lcd.print("Fin de partie");
            break;
    }
}