#include <LiquidCrystal_I2C.h> // Inclui a biblioteca para controlar displays LCD via I2C
#include <Servo.h> // Inclui a biblioteca para controlar servos

// Cria um objeto do tipo LiquidCrystal_I2C com o endereço I2C 0x20, 16 colunas e 2 linhas
LiquidCrystal_I2C oDisplay(0x20, 16, 2);

// Cria um array de objetos Servo para controlar quatro servos
Servo oListaServo[4];

// Declara uma variável para contar o número de pressionamentos de um botão
int vContagem = 0;

// Define constantes para os pinos dos botões
#define cBotaoContador 2 // Pino do botão contador
#define cBotaoAcionador 3 // Pino do botão acionador

// Função de configuração do programa
void setup() 
{
  // Configura os pinos dos botões como entradas
  pinMode(cBotaoContador, INPUT);
  pinMode(cBotaoAcionador, INPUT);

  // Inicializa a comunicação I2C
  Wire.begin();

  // Inicializa o display LCD
  oDisplay.init();
  // Liga a luz de fundo do display
  oDisplay.backlight();
  // Limpa o display
  oDisplay.clear();
  // Define a posição do cursor no display (coluna 0, linha 0)
  oDisplay.setCursor(0, 0);
  // Escreve uma mensagem de inicialização no display
  oDisplay.print("Inicializando...");

  // Anexa os servos aos pinos correspondentes  
  for (int i = 0; i < 4; i++)
  {
    oListaServo[i].attach(i + 8);
  }
  // Move todos os servos para a posição 180 graus
  for (int i = 0; i < 4; i++)
  {
    oListaServo[i].write(180);
  }
  // Espera por 2 segundos
  delay(2000);

  // Move todos os servos para a posição 0 graus
  for (int i = 0; i < 4; i++)
  {
    oListaServo[i].write(0);
  }

  // Define a posição do cursor no display (coluna 0, linha 0)
  oDisplay.setCursor(0, 0);
  // Limpa o display
  oDisplay.clear();
  // Escreve uma mensagem de inicialização concluída no display
  oDisplay.print("Inicializado!");
}

// Função para acionar o motor correspondente ao número recebido
void fAcionarMotor(int pMotor)
{
  if (pMotor >= 1 && pMotor <= 4)
  {
    oDisplay.clear();
    oDisplay.setCursor(0, 1);
    oDisplay.print("Acionado motor " + String(pMotor));
    oListaServo[pMotor - 1].write(180);
    delay(2000);
    oListaServo[pMotor - 1].write(0);
    delay(1000);
    oDisplay.setCursor(0, 1);
    oDisplay.print("                ");
  }
  else 
  {
    oDisplay.clear();
    oDisplay.print("  Selecione 0   ");
    oDisplay.setCursor(0, 1);
    oDisplay.print("     Motor      ");
    delay(2000);
    oDisplay.clear();
    oDisplay.print("Contagem = " + String(vContagem));  
  }
}

// Função principal do programa que executa continuamente
void loop()
{
  // Verifica se o botão contador foi pressionado
  if (digitalRead(cBotaoContador))
  {
    // Se o contador atingir 4, reseta para 0
    if (vContagem == 4)
    {
      vContagem = 0;
    }
    else
    {
      // Caso contrário, incrementa o contador
      vContagem++;
    }
    // Limpa o display
    oDisplay.clear();
    // Exibe o valor atual do contador no display
    oDisplay.print("Contagem = ");
    oDisplay.setCursor(12, 0);
    oDisplay.print(vContagem);
  }

  // Verifica se o botão acionador foi pressionado
  if (digitalRead(cBotaoAcionador))
  {
    // Aciona o servo correspondente ao valor do contador
    fAcionarMotor(vContagem);
  }
}
