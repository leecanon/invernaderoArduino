#include <DHT.h>
#include <SPI.h>
#include <SD.h>

const int sensorDHT=2;
int sensorPin=2;
int sensorValue=0;

int temp = 0, humedad;
int val;

#define SSpin 10

File archivo;
DHT dht (sensorDHT,DHT11);

void setup() {
  
  Serial.begin(9600); //Comunicacion con la PC a 9600 batios
  dht.begin();//iniciamos nuestro sensor
  pinMode (2,INPUT); 

  Serial.println("Inicializando targeta ...");
  if (!SD.begin(SSpin)){
    Serial.println("Fallo en inicializacion !");
    return;
    }
  Serial.println("inicializacion correcta");
  archivo = SD.open("datos.txt", FILE_WRITE );

  if (archivo) {
    for (int i=1; i < 31; i++);{
      temp = dht.readTemperature();
      humedad = dht.readHumidity();

      archivo.print(val);
      archivo.print(",");
      archivo.print(i);
      archivo.print(",");
      archivo.print(temp);
      archivo.print(",");
      archivo.print(humedad);

      Serial.print(val);
      Serial.print(",");
      Serial.print(i);
      Serial.print(",");
      Serial.print(temp);
      Serial.print(",");
      Serial.print(humedad);

      delay(1000);
      }
      archivo.close();
      Serial.println("escritura correcta");
    }else{
      Serial.println("error en apertura de datos.txt");
      }
}

void loop() {

      int val = map(analogRead(A0), 0, 1023, 100,0);//map() convierte el rango de medicion de 0a100 asumiendo q el suelo es humedo al 100% y de 1023 a 0 asumiendo 0% de humedad
      sensorValue = analogRead(sensorPin);
      humedad= dht.readHumidity(); //Permite leer la humedad incluyendo la libreria 
      temp= dht.readTemperature(); //Permite leer la temperatura "" "" 

      //Imprimir en la pantalla datos leidos.
      Serial.print("Temperatura: ");
      Serial.print(temp);
      Serial.println("°C"); //temperatura: 21°C
      Serial.print("Humedad:");
      Serial.print(humedad);
      Serial.print("%");
      Serial.print("  Humedad de suelo: ");
      Serial.print(val);
      Serial.print("%");
      Serial.print(" ");
      Serial.print(" ");      

      //pausa 1 segundo para apreciar los datos
      delay(1000);      
}
