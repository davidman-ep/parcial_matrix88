const int SER = 8;
const int RCLK = 11;
const int SRCLK = 12;

char opcion;//v:verificacion,i:imagen,y:usuario,
int tiempo;
boolean **matriz=new boolean *[8];
void reloj(int c);
void verificacion(boolean);
void publik();
void imagen(boolean **);
void patrones(boolean **,int);
void reservaFilas(boolean **);
void datosMatriz(boolean **);
void intaBinary(int, boolean *);
void liberarMatriz(boolean **);
void datosMatrizP(boolean **,int []);


void setup()
{	
  //paso 1: configuracion de puertos digitales como salida
  	pinMode(SER, OUTPUT );
  	pinMode(RCLK, OUTPUT );
  	pinMode(SRCLK, OUTPUT );
  //inicializar en bajo
  	digitalWrite(SER,0);
    digitalWrite(RCLK,0);
  	digitalWrite(SRCLK,0);
  //inicio de puerto serial
  	Serial.begin(9600);
  //mostrar menu una sola vez  	
  	Serial.print("*****menu*****\n");
 	Serial.print("v:verificacion\n");
  	Serial.print("i:imagen\n");
  	Serial.print("p:patrones\n");
  	Serial.print("n:publik\n");
  	Serial.print("**************\n");  
  	Serial.print("ingrese opcion: ");
  //incializacion de numeros semi-aleatorios
  	randomSeed(analogRead(0)); 
}

void loop()
{
  if(Serial.available()>0){
    opcion=Serial.read();
    switch (opcion){
      case 'v':
      	Serial.print("tiempo encendido-apagado: ");
    	while (!Serial.available()) {}
    	tiempo=Serial.parseInt();
    	Serial.println(tiempo);
      	verificacion(1);
        delay(tiempo);
        verificacion(0);
        delay(tiempo);
      break;
      case 'i':
      	reservaFilas(matriz);
    	datosMatriz(matriz);
      	imagen(matriz);
        delay(1000);    	
      break;
      case 'p':
      	reservaFilas(matriz);
      for(int p=0;p<4;p++){
        patrones(matriz,p);
        delay(1);
        imagen(matriz);
        delay(1500);
      }  
      break;
      case 'n':
      	Serial.println(opcion);     	
      	publik();
      break;
      default:
      Serial.println("opcion invalida");
    }
    Serial.print("*****menu*****\n");
 	Serial.print("v:verificacion\n");
  	Serial.print("i:imagen\n");
  	Serial.print("p:patrones\n");
  	Serial.print("n:publik\n");
  	Serial.print("**************\n");  
  	Serial.print("ingrese opcion: ");
  }  
}

void publik(){ 
  
  int secuencias;
  char opcionP;
  
  Serial.print("*****menu_publik*****\n");
  Serial.print("v:verificacion\n");
  Serial.print("i:imagen\n");
  Serial.print("p:patrones\n");
  Serial.print("**************\n");  
  Serial.print("ingrese opcion_publik: ");
  while (!Serial.available()) {}
  opcionP=Serial.read();
  Serial.println(opcionP);
  
  switch (opcionP){
    case 'v': 
    	Serial.print("tiempo encendido-apagado: ");
    	while (!Serial.available()) {}
    	tiempo=Serial.parseInt();
    	Serial.println(tiempo);
    	Serial.print("numero secuencias: ");    	
    	while (!Serial.available()) {}
    	secuencias=Serial.parseInt();
    	Serial.println(secuencias);
   		for(int i=0;i<secuencias;i++){
          verificacion(1);
          delay(tiempo);
          verificacion(0);
          delay(tiempo);
    	}
    	
    break;
    case 'i':    	
    	reservaFilas(matriz);
    	datosMatriz(matriz);
    	Serial.print("tiempo encendido-apagado: ");
        while (!Serial.available()) {}
    	tiempo=Serial.parseInt();
    	Serial.println(tiempo);
    		while(true){           	
          		imagen(matriz);
              	delay(tiempo);
              	verificacion(0);
              	delay(tiempo);
    		}      
    break;
    case 'p':
    	reservaFilas(matriz);    	
    	Serial.print("tiempo encendido-apagado: ");
        while (!Serial.available()) {}
    	tiempo=Serial.parseInt();
    	Serial.println(tiempo);
    	while(true){
          patrones(matriz,random(5));
          delay(1);
          imagen(matriz);
          delay(tiempo);
    	}
    break;
    default: 
      Serial.print("opcion invalida_p\n");
  }  
  
}

void verificacion(boolean valor){      
    for(int j=0;j<64;j++){
      	digitalWrite(SER,valor);
		reloj(SRCLK);
    	reloj(RCLK);
    }       
}

void imagen(boolean **m){ 
  	//llevar matriz al serial(SER)
  	for(int y=0;y<8;y++){
    	for(int x=0;x<8;x++){
      		digitalWrite(SER, m[y][x]);
			reloj(SRCLK);
    		reloj(RCLK);     
    	}
 	}
}
void reservaFilas(boolean **m){   
  	for (int i=0;i<8;i++ ) {
        m[i]=new boolean [8];
    }
}
void datosMatriz(boolean **m){
  //usuario ingresa fila por fila dato en decimal ->byte
  	int valor=0;
  	for(int i=0;i<8;i++){
    	Serial.print("Ingrese dato de fila " + String(i) + " en decimal: ");
      	while (!Serial.available()) {}
    	valor=Serial.parseInt();
    	Serial.println(valor);
      	intaBinary(valor,m[i]);   
  	}
}
void datosMatrizP(boolean **m,int a[]){
  for(int i=0;i<8;i++){
    intaBinary(a[i],m[i]);
  }   
}

void patrones(boolean **m,int rand){
  int array[4][8]={
  {24,60,126,255,255,126,60,24},
  {129,66,36,24,24,36,66,129},
  {219,219,109,109,219,219,109,109},
  {240,120,60,30,30,60,120,240},
  };
  switch (rand){
    case 0:
    	datosMatrizP(m,array[0]);    	
    break;
    case 1:
    	datosMatrizP(m,array[1]);
    break;
    case 2:
    	datosMatrizP(m,array[2]);
    break;
    case 3:
    	datosMatrizP(m,array[3]);
    break;    
    default:
    Serial.print("\n");
  }
}
void liberarMatriz(boolean **m){
  	//liberacion de memoria
  	for(int i=0;i<8;i++){
        delete [] m[i];
    }
    delete []m;
  	m = nullptr; 
}

void intaBinary(int valor, boolean *ptr){
  for (int i = 0; i < 8; i++) {
    // extrae el ultimo bit del valor utilizando
    //desplazamiento a la derecha y operación and.
    int bit = (valor >> i) & 1;
    // almacena el bit en el arreglo de booleanos,
    //invirtiendo el orden para que el bit más significativo
    // del entero se almacene en la posición 7 del arreglo.    
    ptr[7 - i] = boolean(bit);
  }  
}

void reloj (int c){
  digitalWrite(c,0);
  digitalWrite(c,1);
  digitalWrite(c,0);
}



