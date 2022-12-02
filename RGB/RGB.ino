                   /* // // // // //   //          //
                          //          //          //
                         //          //          //
                        //          // // // // //
                       //          //          //
                      //          //          //
                     //          //          //     */
                  
                  
                  /* Configurações de RGB! */
                  
              /* CONFIGURAÇOES FITA-LED-RGB ! ! */

           //   CRÉDITOS: © 2022 Thiago Macedo.   \\


#include <ESP8266WiFi.h>
#include <ESP8266HTTPUpdateServer.h> //Biblioteca que cria o servico de atualizacão via wifi (ou Over The Air - OTA)
#include "Updates.h"

const char *ssid = "RGB-PC";
const char *password = "corsair450";


IPAddress local_IP(192,168,4,45);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);

//variáveis de controle para cada cor do padrão RGB
int vermelho, verde, azul;




//LED Connections
#define R D6
#define G D7
#define B D8


void setup()
{
  Serial.begin(115200);   //Start serial connection  

  Serial.println();
  Serial.print("Definindo a configuração do soft-AP .... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Preparar" : "Fracassado!");
  Serial.print("Configurando soft-AP .... ");
  Serial.println(WiFi.softAP(ssid,password) ? "Preparar" : "Fracassado!");
  //WiFi.softAP(ssid);
  //WiFi.softAP(ssid, password, channel, hidden, max_connection)
  
  Serial.print("Endereço IP Soft-AP = ");
  Serial.println(WiFi.softAPIP());




  
  //setando os pinos PWM do Arduino como saída
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  
  
 InicializaServicoAtualizacao(); 
}



//=======================================================================
//                    LOOP
//=======================================================================



void loop()
{
  Serial.print("[Server Connected] ");
  Serial.println(WiFi.softAPIP());
  check_updates();






  //incrementa a cor vermelha gradativamente, atingindo a cor magenta
  for (vermelho = 0; vermelho <= 255; vermelho++){
    analogWrite(R, vermelho);
    delay(10);
  }
//remove a cor azul gradativamente, atingindo a cor vermelha pura
  for (azul = 255; azul >= 0; azul--){
    analogWrite(B, azul);
    delay(10);
  }
//incrementa a cor verde gradativamente, atingindo a cor amarela
  for (verde = 0; verde <= 255; verde++){
    analogWrite(G, verde);
    delay(10);
  }
//remove a cor vermelha gradativamente, atingindo a cor verde pura
  for (vermelho = 255; vermelho >= 0; vermelho--){
    analogWrite(R, vermelho);
    delay(10);
  }
//adiciona a cor azul gradativamente, atingindo a cor ciano
  for (azul = 0; azul <= 255; azul++){
    analogWrite(B, azul);
    analogWrite(R, azul);
    delay(10);
  }
//remove a cor verde gradativamente, atingindo a cor azul pura
  for (verde = 255; verde >= 0; verde--){
    analogWrite(G, verde);
    analogWrite(R, verde);
    delay(10);
  }
//reinicia o ciclo
}
