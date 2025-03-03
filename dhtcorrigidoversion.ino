/*
IFPB CAMPUS ESPERANÇA
GRUPO: VITOR ALBUQUERQUE, IZABELY MARIA, SUZIANNE MARIA,
       MARIA CECÍLIA, GUILHERME GUEDES, HILDEMAR RIKELMY      
       EDILSON VINICIUS
Projeto de monitoramento de humidade com sensor dht11
190225.1 
*/

#include <LiquidCrystal.h>
#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11   // DHT 11 
#define pushbutton 13
#define tempo 500
//altere para 1 se for simular de verdade
/////////////////////VARIÁVEIS GLOBAIS/////////////

//variaveis boleanas verdadeiras ou falsas
bool flag = false;
bool flag2 = false;
bool flag3 = false;
bool flag4 = false;
bool flag5 = false;
bool alert = true;
bool monitorar = false;
bool desligar = false;

// variaveis sem sinal para tempo
unsigned long t1 = 0;
unsigned long time=0;
unsigned long time2=0;
unsigned long time3=0;
unsigned long time4=0;// VARIAVEL PARA TEMPO

//ints 
int contador = 0; // CONTADOR DE TOQUES NO BOTÃO
int TelaChange = 0;//troca de telas
int RefMinU=0, RefMaxU=0, contador2, contador3;
int SensorValue=0;


///////////////////////////////////////////////

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal LCD1(rs, en, d4, d5, d6, d7);
/*
12 - RS
11 - E
5 - DB4 
4 - DB5
3 - DB6
2 - DB7
*/
///////////////////////////////////////////////

DHT dht(DHTPIN, DHTTYPE);
void setup()
{
 pinMode(pushbutton, INPUT_PULLUP);
 LCD1.begin(16,2);
 dht.begin();

}
/////// funções de tela ///////

 void telaUmi(){
    LCD1.setCursor(0,0);
    LCD1.print("HUMIDITY MONITOR");
    LCD1.setCursor(3,1);
    LCD1.print("Valor(%):");

    int valorUmi = monitoramento();  // Chama a função de monitoramento

    if (valorUmi == -1) {  // Se a leitura falhou
        LCD1.setCursor(0, 1);  
        LCD1.print("Erro de leitura"); // Exibe mensagem de erro
    } else {
        LCD1.setCursor(13,1);  
        LCD1.print(valorUmi); // Exibe o valor da umidade
    }
}

 void telaclean()
 { 
  LCD1.setCursor(0, 0);
  LCD1.write("                ");
  LCD1.setCursor(0, 1);
  LCD1.print("                ");
 } //end void
 void telaMax() {
  LCD1.setCursor(0, 0);
  LCD1.print("UMIDADE MAXIMA");
  LCD1.setCursor(0, 1);
  LCD1.print("RELATIVA(%):");
  LCD1.setCursor(13, 1);
  LCD1.print(RefMaxU);
 }//end void
 void telaMin() {
  LCD1.setCursor(0, 0);
  LCD1.print("UMIDADE MINIMA");
  LCD1.setCursor(0, 1);
  LCD1.print("RELATIVA(%):");
  LCD1.setCursor(12, 1);
  LCD1.print(RefMinU);
 }//end void

 void telaAlert() {
  LCD1.setCursor(1, 0);
  LCD1.print("HUMIDITY SENSOR");
  LCD1.setCursor(2, 1);
  LCD1.print("UMIDADE RUIM!");
 }//endvoid

 void telastop() {
 LCD1.setCursor(1, 0);
 LCD1.print("HUMIDITY SENSOR");
 LCD1.setCursor(5, 1);
 LCD1.print("ok!");
 } 

//////////////funções de valor////////////////////
 //controlam valores máximos e mínimos
 void valormax()
  {
  // Se o botão está pressionado (estado LOW porque é PULLUP)
  if (!digitalRead(13)) { //SE MUDOU DE ESTADO ENQUANTO A
    if (!flag2) {          // A FLAG É FALSA
      time = millis();  // Armazena o tempo em que o botão foi pressionado
      flag2 = true;    // Marca que o botão foi pressionado
    }
  } else {
    // Se o botão foi solto e estava pressionado antes
    if (flag2) { 
      unsigned long duracao = millis() - time;

      if (duracao >= tempo) {
        // Se o botão foi pressionado por mais de tempo mantem refmax
        RefMaxU=RefMaxU;
      } else {
        // Caso contrário, incrementa o contador
        RefMaxU++;
        if (RefMaxU > 100) {
          RefMaxU = 0;  // Volta para 0 se passar de 100
        }
      }

      flag2 = false;  // Reseta a flag para detectar nova pressão
    }
  }}
 void valormin()
  {
  // Se o botão está pressionado (estado LOW porque é PULLUP)
  if (!digitalRead(13)) { //SE MUDOU DE ESTADO ENQUANTO A
    if (!flag3) {          // A FLAG É FALSA
      time2 = millis();  // Armazena o tempo em que o botão foi pressionado
      flag3 = true;    // Marca que o botão foi pressionado
    }
  } else {
    // Se o botão foi solto e estava pressionado antes
    if (flag3) { 
      unsigned long duracao2 = millis() - time2;

      if (duracao2 >= tempo) {
        // Se o botão foi pressionado por mais de tempo mantem refmax
        RefMinU=RefMinU;
      } else {
        // Caso contrário, incrementa o contador
        RefMinU++;
        if (RefMinU > 100) {
          RefMinU = 0;  // Volta para 0 se passar de 100
        }
      }

      flag3 = false;  // Reseta a flag para detectar nova pressão
    }
  }}

//////////////////////////funções monitoramento//////////////////////////////
 
 int monitoramento(){
  SensorValue = dht.readHumidity();
   if (isnan(SensorValue)) {
        return -1;  // Retorna um valor inválido se a leitura falhar
    }
   return SensorValue;
 }
 void avaliar(){
 //se o valor simulado do sensor estiver diferente do que programado ele mostra o alerta
 int sensor = monitoramento();
 if(sensor>RefMaxU || sensor<RefMinU){
      TelaChange=8; 
    }//endif
}

///////////////////////////funçao de alerta////////////////////////////////
 //desliga o alerta se der dois toques no botao
 void alertoff()
 {
  if(TelaChange==8){
    // Se o botão está pressionado (estado LOW porque é PULLUP)
  if (!digitalRead(13)) { //SE MUDOU DE ESTADO ENQUANTO A
    if (!flag4) {          // A FLAG É FALSA
      time3 = millis();  // Armazena o tempo em que o botão foi pressionado
      flag4 = true;    // Marca que o botão foi pressionado
    }
  } else {
    // Se o botão foi solto e estava pressionado antes
    if (flag4) { 
      unsigned long duracao3 = millis() - time3;

      if (duracao3 >= tempo) {
        // Se o botão foi pressionado por mais de 1 segundo, reseta o contador
        contador2 = 0;
      } else {
        // Caso contrário, incrementa o contador
        contador2++;
        if (contador2 > 2) {
          contador2 = 0;  // Volta para 0 se passar de 2
        }
      }

      flag4 = false;  // Reseta a flag para detectar nova pressão
    }}
    if(contador2==2){
    telaclean();
    TelaChange=0;
    contador2=0;
    }//endif
  }
 }//endvoid


/////////////////////////// função de contagem ////////////////////////////////////
 //contagem da troca de telas e reset do programa
 void contagem() {
  // Se o botão está pressionado (estado LOW porque é PULLUP)
  if (!digitalRead(13)) { //SE MUDOU DE ESTADO ENQUANTO A
    if (!flag) {          // A FLAG É FALSA
      t1 = millis();  // Armazena o tempo em que o botão foi pressionado
      flag = true;    // Marca que o botão foi pressionado
    }//if
    
  }//end 
  
  else {
    // Se o botão foi solto e estava pressionado antes
    if (flag) { 
      unsigned long duracaoPressionado = millis() - t1;
            
      if (duracaoPressionado >= 2000){
      desligar = true; //controla o reset, var booleana
      } //se for pressionado por 2 segundos, desligar vira 5 para que possamos resetar processo
      if (duracaoPressionado >= tempo) {
        // Se o botão foi pressionado por mais de 1 segundo, reseta o contador
        contador = 0;
           TelaChange++;
         if (TelaChange>=7) {
        TelaChange=0;
        }//end 
      }//end
      }
      flag = false;  // Reseta a flag para detectar nova pressão
    }
 }//end void contagem 

///////////////////////função de reset ////////////////////////

 void reset(){
 TelaChange=0;
 flag = false;
 flag2 = false;
 flag3 = false;
 flag4 = false;
 flag5 = false;
 desligar = false;
 alert = true;
 monitorar = false;
 RefMaxU=0; RefMinU=0; SensorValue;
 }   

 void zerorefmax(){
  if(RefMaxU>=0 && RefMaxU<10){
    LCD1.setCursor(14,1);
    LCD1.write("   ");
  }
 
  }
 void zerorefmin(){
  if(RefMinU>=0 && RefMinU<10){
    LCD1.setCursor(13,1);
    LCD1.write("   ");
  }
 }

//////////////////////////////////////// loop //////////////////////////////////////////

void loop()
{
  contagem();
  switch(TelaChange) {
   
    case 8:
    telaAlert();
    break;
    case 7:
    telaclean();
     delay(20);
    TelaChange++;
    break;
    case 6:
    telastop();
    break;
    case 5:
    telaclean();
     delay(20);
    TelaChange++;
    break;
     case 4:
      telaMin();
     valormin();
     zerorefmin();
    break;
    case 3:
    telaclean();
     delay(20);
    TelaChange++;
    break;
    case 2:
      telaMax();
      valormax();
      zerorefmax();
      break;
   case 1:
    telaclean();
    delay(20);
    TelaChange++;
    break;
    case 0:
      telaUmi(); 
      break;
 }//endcase
 
  if(TelaChange==6){
  monitorar=true;
  }
  if (monitorar==true){
  flag5=true;
  time4 = millis();
  avaliar();
  monitorar=false;
  }
  if(flag5){
  unsigned long tempomonitor = millis() - time4;
  if (tempomonitor >= 5000){
  monitorar=true;
  }}
  //dois toques desliga o botao
  alertoff();
  //se desligar for 5, reseta e inicia o processo novamente
  if (desligar==true){
  reset();
  }
}//edn void loop

