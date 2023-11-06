//Montagem dos pinos dos LEDs
int r_pin = 16;
int b_pin = 18;
int g_pin = 23;
int y_pin = 15;

//Montagem dos botões
int r_button = 22;
int b_button = 21;
int g_button = 0;
int y_button = 19;
int reset_button = 17; 

int nivel = 1; //Nível inicial
int velocidade = 500; //Velocidade das piscadas

const int limite = 50; //Limite do nível
int minha_lista[limite]; //Sequência de botões apertados do usuário
int lista_correta[limite]; //Sequência correta dos botões

void setup() { //Inicializa o jogo
  pinMode(r_pin, OUTPUT);
  pinMode(b_pin, OUTPUT);
  pinMode(g_pin, OUTPUT);
  pinMode(y_pin, OUTPUT);
  pinMode(r_button, INPUT);
  pinMode(b_button, INPUT);
  pinMode(g_button, INPUT);
  pinMode(y_button, INPUT);
  pinMode(reset_button, INPUT);
  delay(500);
  criar_sequencia();
  mostrar_sequencia();
  receber_sequencia();
}

void loop() {//Configura o botão de reset
  int sla = 0;
  while (sla == 0) {
    if (digitalRead(reset_button) == LOW) {
      resetar();
      sla = 1;
    }
  }
}

void mostrar_sequencia() { //Exibe a sequência da piscagem dos LEDs
  digitalWrite(r_pin, LOW);
  digitalWrite(g_pin, LOW);
  digitalWrite(b_pin, LOW);
  digitalWrite(y_pin, LOW);
  for(int i = 0; i < nivel; i++) {
    digitalWrite(lista_correta[i], HIGH);
    delay(velocidade);
    digitalWrite(lista_correta[i], LOW);
    delay(velocidade);
  }
}

void criar_sequencia() {//Cria a sequência de piscagem dos LEDs
  int escolha;
  for(int i = 0; i < nivel; i++) {
    int rand_number = random(0,4);
    if (rand_number == 0) {
      escolha = 16;
    }
    if (rand_number == 1) {
      escolha = 18;
    }
    if (rand_number == 2) {
      escolha = 23;
    }
    if (rand_number == 3) {
      escolha = 15;
    }
    lista_correta[i] = escolha;
  }
}

void receber_sequencia() {//Recebe a sequência de input do usuário por meio dos botões, e compara com a sequência correta
  int control = 0; //Variável de controle
  for (int i = 0; i < nivel; i++) {
    control = 0;
    while (control == 0) {
      if (digitalRead(r_button) == LOW) {//Botão vermelho
        digitalWrite(r_pin, HIGH);
        minha_lista[i] = 16;
        if (minha_lista[i] != lista_correta[i]) {
          game_over();
          return;
        }
        control = 1;
        delay(200);
        digitalWrite(r_pin, LOW);
      }
      if (digitalRead(g_button) == LOW) {//Botão verde
        digitalWrite(g_pin, HIGH);
        minha_lista[i] = 23;
        if (minha_lista[i] != lista_correta[i]) {
          game_over();
          return;
        }
        control = 1;
        delay(200);
        digitalWrite(g_pin, LOW);
      }
      if (digitalRead(b_button) == LOW) {//Botão azul
        digitalWrite(b_pin, HIGH);
        minha_lista[i] = 18;
        if (minha_lista[i] != lista_correta[i]) {
          game_over();
          return;
        }
        control = 1;
        delay(200);
        digitalWrite(b_pin, LOW);
      }
      if (digitalRead(y_button) == LOW) {//Botão amarelo
        digitalWrite(y_pin, HIGH);
        minha_lista[i] = 15;
        if (minha_lista[i] != lista_correta[i]) {
          game_over();
          return;
        }
        control = 1;
        delay(200);
        digitalWrite(y_pin, LOW);
      }
      if (digitalRead(reset_button) == LOW) {//Botão do reset 
        resetar();
      }
    }
  }
  delay(200);
  ganhou(); //Caso acerte a sequência, ganha a rodada
}

void game_over() {//Acende os LEDs, indicando game over
  digitalWrite(r_pin, HIGH);
  digitalWrite(b_pin, HIGH);
  digitalWrite(y_pin, HIGH);
  digitalWrite(g_pin, HIGH);
}

void ganhou() {//pisca o LED após ganhar
  digitalWrite(r_pin, HIGH);
  digitalWrite(b_pin, HIGH);
  digitalWrite(y_pin, HIGH);
  digitalWrite(g_pin, HIGH);
  delay(400);
  digitalWrite(r_pin, LOW);
  digitalWrite(b_pin, LOW);
  digitalWrite(y_pin, LOW);
  digitalWrite(g_pin, LOW);
  delay(400);
  digitalWrite(r_pin, HIGH);
  digitalWrite(b_pin, HIGH);
  digitalWrite(y_pin, HIGH);
  digitalWrite(g_pin, HIGH);
  delay(400);
  digitalWrite(r_pin, LOW);
  digitalWrite(b_pin, LOW);
  digitalWrite(y_pin, LOW);
  digitalWrite(g_pin, LOW);
  delay(400);
  digitalWrite(r_pin, HIGH);
  digitalWrite(b_pin, HIGH);
  digitalWrite(y_pin, HIGH);
  digitalWrite(g_pin, HIGH);
  delay(400);
  digitalWrite(r_pin, LOW);
  digitalWrite(b_pin, LOW);
  digitalWrite(y_pin, LOW);
  digitalWrite(g_pin, LOW);
  delay(400);
  nivel ++; //Aumenta o nível
  velocidade -= 25; //Aumenta a velocidade das piscadas
  if (velocidade < 200) {//Estabelece um limite mínimo de velocidade
    velocidade = 200;
  }
  resetar();
}

void resetar() {//Reinicia a rodada
  criar_sequencia();
  mostrar_sequencia();
  receber_sequencia();
  delay(500);
}