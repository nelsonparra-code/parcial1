const int ser=3,rc=4,src=5,reset=6;
int binArr[8],position;
int decArr[] = {195,195,195,219,219,231,231,195},
    happy[]={24,36,66,0,36,36,36,0};
char letters[]={'a','b','c','d','e','f','g','h','i','j','k','l','m',
                'n','o','p','q','r','s','t','u','v','w','x','y','z'};
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
					{},//p
					{},//q
					{},//r
					{},//s
					{},//t
					{},//u
					{},//v
					{},//w
					{},//x
					{},//y
					{}};//z

void setup()
{
  /*Se configuran los pines del Arduino para que funcionen como
  salida y asi ingresar valores a los CI*/
  pinMode(ser, OUTPUT);
  pinMode(src, OUTPUT);
  pinMode(rc, OUTPUT);
  pinMode(reset, OUTPUT);
  /*Se configura el puerto SRCL para que permita 
  el correcto almacenamiento de datos en los CI*/
  digitalWrite(reset,1);
  /*Inicializacion del puerto serial*/
  Serial.begin(9600);
}

void loop()
{
  //imagen(happy);
  //verificacion();
  publik();
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
void publik()
{
  int n=4;

  char charArr[]="hola";

  for(int let=0;let<=(n-1);let++){
    char seqLet=charArr[let];
    for(int letPos=0;letPos<=26;letPos++){
      if(letters[letPos]==seqLet){
        
        position=letPos;

        imagen(letValues[letPos]);
      }

    }
    
    delay(1000);

  }
  
  digitalWrite(reset,0);
  digitalWrite(reset,1);
}