const int ser=3,rc=4,src=5;
int binArr[8],position;
char letters[]={'a','b','c','d','e','f','g','h','i','j','k','l','m',
                'n','o','p','q','r','s','t','u','v','w','x','y','z',
                '*','U','D','T','C','F','S','Z','O','N','H'};
int letValues[][8]={{66,102,102,60,36,36,60,24},//a
					{124,102,102,124,124,102,102,124},//b
					{126,126,96,96,96,96,126,126},//c
					{120,124,108,102,102,108,124,120},//d
					{126,126,96,126,126,96,126,126},//e
					{96,96,96,120,120,96,126,126},//f
					{126,126,102,110,96,96,126,126},//g
					{195,195,195,255,255,195,195,195},//h
					{126,60,24,24,24,24,60,126},//i
					{62,62,54,38,6,6,14,28},//j
					{102,108,108,120,120,108,108,102},//k
                    {60,60,48,48,48,48,48,48},//l
					{195,195,195,219,219,231,231,195},//m
					{193,195,199,207,219,243,195,131},//n
                    {126,126,102,102,102,102,126,126},//o
					{96,96,124,126,102,102,126,124},//p
					{1,62,68,74,66,66,66,60},//q
					{102,108,124,126,102,102,126,124},//r
					{60,2,2,2,60,64,64,60},//s
					{24,24,24,24,24,24,126,126},//t
					{126,126,102,102,102,102,102,102},//u
					{24,36,36,36,66,66,66,66},//v
					{195,231,231,219,219,195,195,195},//w
					{66,102,60,24,24,60,102,66},//x
					{24,24,24,24,36,102,195,129},//y
					{255,255,96,56,28,6,255,255},//z
					{0,0,0,0,0,0,0,0},//espacio
					{126,60,24,24,24,120,56,24},//1
					{124,124,96,56,12,12,124,124},//2
					{124,126,6,30,30,6,126,124},//3
					{4,4,126,68,36,20,12,4},//4
					{124,6,6,102,124,96,96,62},//5
					{60,102,102,102,124,96,124,60},//6
					{32,48,56,28,14,2,126,126},//7
					{60,102,102,60,60,102,102,60},//8
					{60,126,6,6,126,102,102,60},//9
					{24,36,66,0,36,36,36,0}};//cara feliz

void setup()
{
  /*Se configuran los pines del Arduino para que funcionen como
  salida y asi ingresar valores a los CI*/
  pinMode(ser, OUTPUT);
  pinMode(src, OUTPUT);
  pinMode(rc, OUTPUT);
  /*Inicializacion del puerto serial*/
  Serial.begin(9600);
}

void loop()
{
  int qty;
  unsigned int time;
  
  Serial.println("Ingrese el tamaño de la secuencia a mostrar.");
  Serial.print("(Considere el -1 como prueba de la matriz): ");
  
  while(Serial.available()==0);
  qty = Serial.parseInt();
  Serial.println(qty);
  
  if(qty==-1){
    verificacion();
  }
  else if(qty==1){
    int letPos;
    Serial.println("Ingrese imagen a mostrar: ");
    while(Serial.available()==0);
    char caracter = Serial.read();
    for(letPos=0;letPos<=36;letPos++){
      if(*(letters+letPos)==caracter) break;
    }
    imagen(letValues[letPos]);
  }
  else{
    
    Serial.print("Ingrese el tiempo entre patrones (milisegundos): ");
    while(Serial.available()==0);
    time = Serial.parseInt();
    Serial.print(time);
    Serial.println("ms");
    
    Serial.println("Ingrese la secuencia a mostrar: ");
    for(int count=1;count<=qty;count++){
      while(Serial.available()==0);
      char caracter = Serial.read();
      if(count!=qty) Serial.print(caracter);
      else Serial.println(caracter);
      publik(&caracter, qty, time);
    } 
  }
  delay(500);
  imagen(letValues[26]);
}

/*Funcion que guarda en la memoria de los CI, el bit ingresado*/
void store(int bit)
{
  digitalWrite(ser,bit);
  
  digitalWrite(src,0);
  digitalWrite(src,1);
  digitalWrite(src,0);
}

/*Funcion que permite mostrar en la matriz,
lo que previamente se almaceno en la memoria de los CI*/
void show()
{
  digitalWrite(rc,0);
  digitalWrite(rc,1);
  digitalWrite(rc,0);
}

/*Funcion imagen que muestra alguna imagen en la matriz LED,
recibiendo un arreglo de numeros decimales.*/
void imagen(int *arrN)
{
 for(int i=0;i<=7;i++){
    int bit,n=*(arrN+i),binArr[8];
    for(int j=0;j<=7;j++){
      bit=n%2;
      binArr[j]=bit;
      n/=2;
    }
    for(int h=0;h<=7;h++){
      store(binArr[h]);
    }
  }
  show();
}

/*Verifica el correcto funcionamiento de la matriz,
prendiendo todos los LEDs*/
void verificacion()
{
  int test[]={255,255,255,255,255,255,255,255};
  imagen(test);
}

/*Funcion que permite mostrar una seciencia de caracteres,
uno por uno en la matriz LED*/
void publik(char *charArr, int n, int retardo)
{
  for(int let=0;let<=(n-1);let++){
    char seqLet=charArr[let];
    for(int letPos=0;letPos<=36;letPos++){
      if(letters[letPos]==seqLet){
        position=letPos;
        imagen(letValues[letPos]);
      }
    }
    delay(retardo);
  }
  
  return;
}