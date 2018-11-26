include<Servo.h>

//ett servoobjekt per servo
Servo myServo1;
Servo myServo2;
int lysverdi = A0;
int maxVal = 0;
int sensorValue = 0;

/* alle disse Serial.print brukes eller har vært brukt til debugging.
   Håper du kan unnskylde at det blir litt rotete ;-) */

//Verdien som gir utgangspunt til sektorene 
const int radius = 90;
//denne verdien reguleres for å justere størrelsen på kvadrantene
int quadCounter = 2;
//definerer origo til midtpunktet for begge servoene
int origo[] = {90,90};

void setup(){
    //definer signal pin for servo objektene
    myServo1.attach(3);
    myServo2.attach(9);
    //sette opp serial 
    Serial.begin(9600);
    //roterer motorene til utgangsposisjon
    movePattern(origo[0],origo[1]);
}

void loop(){
    //delay(1000);
    //begrenser antall omganger den vil kjøre til 3.
    if(quadCounter <= 8 ){
      	searchPattern();
    }
}

void searchPattern(){
    /*Søker etter høyeste effekt fra sensor,
      Juster posisjon, registrer verdier fra sensor, 
      evaluer og juster origo hvis høyere verdi finnes

     */
    int patternResult[4];
    //setter opp variabelen som brukes til å gi verdier relativ til origo
    int modulatorlissom = floor(radius/quadCounter);
    //Serial.print("Soekeboksradius?: ");
    //Serial.println(modulatorlissom);

    //Roter motorene relativt til origo og mål effekten i punktene
    movePattern(origo[0] + modulatorlissom, origo[1] + modulatorlissom);
    patternResult[0] = analogRead(lysverdi);
    //Serial.print("Sensor output 0: ");
    //Serial.println(patternResult[0]);

    movePattern(origo[0] - modulatorlissom, origo[1] - modulatorlissom);
    patternResult[2] = analogRead(lysverdi);
    //Serial.print("Sensor output 2: ");
    //Serial.println(patternResult[2]);

    movePattern(origo[0] - modulatorlissom, origo[1] + modulatorlissom);
    patternResult[3] = analogRead(lysverdi);
    //Serial.print("Sensor output 3: ");
    //Serial.println(patternResult[3]);

    movePattern(origo[0] + modulatorlissom, origo[1] - modulatorlissom);
    patternResult[1] = analogRead(lysverdi); 
    //Serial.print("Sensor output 1: ");
    //Serial.println(patternResult[1]); 

    //Finn den av posisjonene som hadde den høyeste verdien
    maxVal = 0;
    sensorValue = 0;
    for(int i = 0; i<4;i++){
        if(patternResult[i] > sensorValue){
            maxVal = i + 1;          
            sensorValue = patternResult[i];            
        }
    }

    //Juster origo til posisjonen med høyest verdi og flytt.
    switch(maxVal){
      	case 1:
        	origo[0] = origo[0] + modulatorlissom;
        	origo[1] = origo[1] + modulatorlissom;
        	movePattern(origo[0],origo[1]);
        	//Serial.println("Case 1");
      		break;

        case 2:
        	origo[0] = origo[0] + modulatorlissom;
        	origo[1] = origo[1] - modulatorlissom;
        	movePattern(origo[0],origo[1]);
        	//Serial.println("Case 2");
      		break;

        case 3:
        	origo[0] = origo[0] - modulatorlissom;
        	origo[1] = origo[1] - modulatorlissom;
        	movePattern(origo[0],origo[1]);
        	//Serial.println("Case 3");
      		break;

        case 4:
        	origo[0] = origo[0] - modulatorlissom;
        	origo[1] = origo[1] + modulatorlissom;
        	movePattern(origo[0],origo[1]);
        	//Serial.println("Case 4");
      		break;

        default:
        	//Hvis det ikke finnes en bedre verdi, returner til utgangsposisjon
        	//Serial.print("Ingen ny origo. Origo i: ");
        	//Serial.println(origo[0]);
        	//Serial.println(origo[1]);
        	movePattern(origo[0],origo[1]);
      		break;
    }
    //Serial.println(origo[0]);
    //Serial.println(origo[1]);
  	modulatorlissom = 0;
  	quadCounter = quadCounter + 1;
}

void movePattern(int serv1, int serv2){
    /*Tar inn vinkler og vender motorene */
    for (int pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      	// Ta inn verdiene for nåværende posisjon for motorene
      	int currentPos1 = myServo1.read();
      	int currentPos2 = myServo2.read();

      	// rotere servo 1 ett steg mot målposisjonen gitt ved serv1:
      	//delayen her justerer hastigheten på bevegelsen
		if(currentPos1 < serv1){
        	myServo1.write(currentPos1 + 1);
      	}else if(currentPos1 > serv1){
        	myServo1.write(currentPos1 - 1);                       
      	}
      	delay(3);
      	// rotere servo 2 ett steg mot målposisjonen gitt ved serv2:
      	if(currentPos2 < serv2){
        	myServo2.write(currentPos2 + 1);
      	}else if(currentPos2 > serv2){
        	myServo2.write(currentPos2 - 1);                       
      	}
      	delay(3);     
    }
    /*Legger inn en pause for at motorene skal kunne gjennomføre 
      rotasjonen før målingen tas. kan vi f.eks måle når motorene 
      slutter å gå og hente data fra panelet da?*/
}

