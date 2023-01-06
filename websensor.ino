//library
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

//var indikator koneksi-led menyala jika terkoneksi wifi
#define led D1

//setting jaringan wifi yg digunakan
const char* ssid = "Edelweis";
const char* password = "B1234#";
// alamat ip server laptop yg digunakan. cek = setting > advance network setting > hardware and connection properties > name : wi-fi > IPv4
const char* host = "192.168.2.18"; 

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);

  //setting koneksi wifi
  WiFi.hostname("NodeMCU"); // nama board yg tertampil di wifi
  WiFi.begin(ssid, password);

  //cek koneksi
  while(WiFi.status() != WL_CONNECTED){
    //led mati
    digitalWrite(led, LOW);
    //terus mencoba koneksi
    Serial.print(".");
    delay(500);
  }
  // berhasil terkoneksi
  digitalWrite(led, HIGH);
  Serial.println("Wifi Connected");

}

void loop() {
  //ldr
  int sensor = analogRead(A0);
  Serial.println(sensor);

  //proses koneksi ke server
  WiFiClient client;
  if(!client.connect(host, 80)){
    Serial.println("Connection Failed");
    return;
  }

  //proses pengiriman data ke server
  String Link;
  HTTPClient http;

  Link = "http://192.168.2.18/websensor/kirimdata.php?sensor=" + String(sensor);

  //eksekusi link
  http.begin(client, Link);
  //mode GET
  http.GET();
  http.end();

  delay(1000);
}
