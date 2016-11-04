//Constantes
const int numParpadeos = 3;
const int tiempoParpadeos = 500; //Milisegundos
const int ledpinLeft = 9;
const int ledpinRight = 5;
const int ledpinCommon = 6;
const int leftSignal = A3;
const int rightSignal = A5;
const int vibradorizq = 10;
const int vibradorder = 11;

//Variables internas
int estadodelbotonizd = 0;
int estadodelbotondch = 0;
bool botondrchpulsado = false;
bool botondizqpulsado = false;
int estadoanterior = 0; //0 derecha, 1 izquierda
int estadoled = LOW;
int parpadeos = 0;
int contadorparpadeo = 0;

void setup() {
  //Inicialización de los pines
  pinMode(ledpinLeft, OUTPUT);
  pinMode(ledpinRight, OUTPUT);
  pinMode(ledpinCommon, OUTPUT);
  pinMode(vibradorizq, OUTPUT);
  pinMode(vibradorder, OUTPUT);
  pinMode(leftSignal, INPUT_PULLUP);
  pinMode(rightSignal, INPUT_PULLUP);
}

void loop() {

  //Obtiene el estado de los botones
  estadodelbotonizd = digitalRead(leftSignal);
  estadodelbotondch = digitalRead(rightSignal);
  
  //Si el boton izquierdo esta pulsado
  if (estadodelbotonizd == LOW && botondizqpulsado == false){

    //Reinicia el estado de los output
    digitalWrite(ledpinLeft, LOW);
    digitalWrite(ledpinRight, LOW);
    digitalWrite(ledpinCommon, LOW);
    digitalWrite(vibradorizq, LOW);
    digitalWrite(vibradorder, LOW);


    //Si se ha pulsado el boton izquierdo y los leds izquierdos estan apagados 
    // o estaban parpadeando los leds derechos, enciende los leds izquierdos
    if(parpadeos == 0 || estadoanterior == 0){
      parpadeos = numParpadeos;
      estadoled = HIGH;
      contadorparpadeo = 0;
    } else { //Si se vuelve a pulsar el boton mientras parpadean deja de parpadear
      parpadeos = 0;
    }
    
    //Guarda el boton que se ha pulsado
    estadoanterior = 1;
    //Establece el boton como pulsado
    botondizqpulsado = true;
  }
  
  //Si se ha dejado de pulsar el boton izquierdo
  else if (estadodelbotonizd == HIGH){
    
    botondizqpulsado = false;  
  }

  //Si el boton derecho esta pulsado
  if (estadodelbotondch == LOW && botondrchpulsado == false){
    
    //Reinicia el estado de los output
    digitalWrite(ledpinLeft, LOW);
    digitalWrite(ledpinRight, LOW);
    digitalWrite(ledpinCommon, LOW);
    digitalWrite(vibradorizq, LOW);
    digitalWrite(vibradorder, LOW);

    //Si se ha pulsado el boton derecho y los leds derechos estan apagados 
    // o estaban parpadeando los leds izquierdos, enciende los leds derechos
    if(parpadeos == 0 || estadoanterior == 1){
      parpadeos = numParpadeos;
      estadoled = HIGH;
      contadorparpadeo = 0;
    }  else { //Si se vuelve a pulsar el boton mientras parpadean deja de parpadear
      parpadeos = 0;
    }

    //Guarda el boton que se ha pulsado
    estadoanterior = 0;
    //Establece el boton como pulsado
    botondrchpulsado = true;
  }

  //Si se ha dejado de pulsar el boton izquierdo
  else if (estadodelbotondch == HIGH){
    
    botondrchpulsado = false;  
  }

  //BUCLE PARPADEO LED

  //Parpadeo LED derecho
  if(estadoanterior == 0 && parpadeos > 0){
    
    if(contadorparpadeo < tiempoParpadeos){
      digitalWrite(ledpinRight, estadoled);
      digitalWrite(ledpinCommon, estadoled);
      digitalWrite(vibradorder, estadoled);
      delay(10);
      contadorparpadeo += 10;
    }
    else if(contadorparpadeo == tiempoParpadeos && estadoled == HIGH){
      contadorparpadeo = 0;
      estadoled = LOW;
    }
    else if(contadorparpadeo == tiempoParpadeos && estadoled == LOW){
      parpadeos--;
      contadorparpadeo = 0;
      estadoled = HIGH;
    }
  }

  //Parpadeo LED izquierdo
  if(estadoanterior == 1 && parpadeos > 0){
    
    if(contadorparpadeo < tiempoParpadeos){
      digitalWrite(ledpinLeft, estadoled);
      digitalWrite(ledpinCommon, estadoled);
      digitalWrite(vibradorizq, estadoled);
      delay(10);
      contadorparpadeo += 10;
    }
    else if(contadorparpadeo == tiempoParpadeos && estadoled == HIGH){
      contadorparpadeo = 0;
      estadoled = LOW;
    }
    else if(contadorparpadeo == tiempoParpadeos && estadoled == LOW){
      parpadeos--;
      contadorparpadeo = 0;
      estadoled = HIGH;
    }
  }
}

