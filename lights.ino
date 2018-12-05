#include <Adafruit_NeoPixel.h>
#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(9, PIN, NEO_GRB + NEO_KHZ800);

/*
void setup(){
	strip.begin();
	strip.show();
	low();
	medium();
	high();
}
void loop() {
	lightPattern(400);
	delay(1000);
	lightPattern(600);
	delay(1000);
	lightPattern(900);
	delay(1000);
}
*/

void lightsInit() {
	strip.begin();
	strip.show();
	low();
	medium();
	high();
}
void lightPattern(int panelOutputValue){
	if(panelOutputValue < 500){
		low();
	}else if(panelOutputValue < 700){
		medium();
	}else if(panelOutputValue >= 700){
		high();
	}
}
void low(){
	
	for(int i = 0; i < 3; i++){
		//Gold farge:	
		strip.setPixelColor(i, 64, 54, 0);
	}
	for(int j = 5; j >= 3; j--){
		//Crimson farge:	
		strip.setPixelColor(j, 127, 5, 5);
			
	}
	for(int z = 6; z < 9; z++){
		//Teal farge:	
		strip.setPixelColor(z, 0, 128, 128);
	}
	strip.show();
	delay(100);
}
void medium(){
	for(int i = 0; i < 3; i++){
		//Gold farge:	
		strip.setPixelColor(i, 128, 107, 0);
	}
	for(int j = 5; j >= 3; j--){
		//Crimson farge:	
		strip.setPixelColor(j, 255, 10, 10);
	}
	for(int z = 6; z < 9; z++){
		//Teal farge:	
		strip.setPixelColor(z, 0, 64, 64);
	}
	strip.show();
	delay(100);
}
void high(){
	for(int i = 0; i < 3; i++){
		//Gold farge:	
		strip.setPixelColor(i, 255, 215, 0);
	}
	for(int j = 5; j >= 3; j--){
		//Crimson farge:	
		strip.setPixelColor(j, 128, 5, 5);
	}
	for(int z = 6; z < 9; z++){
		//Teal farge:	
		strip.setPixelColor(z, 0, 64, 64);
	}
	strip.show();
	delay(100);
}
