const int ser=3,rc=4,src=5,reset=6;
int cont=1,aux,binArr[8];
int decArr[] = {193,195,199,207,219,243,195,131},
    happy[]={24,36,66,0,36,36,36,0};

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
}

void loop()
{
  imagen(decArr);
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

/*Verifica el correcto funcionamiento de la matriz,
prendiendo todos los LEDs*/
void verificacion()
{
  int decArr[]={255,255,255,255,255,255,255,255};
  for(int i=0;i<=7;i++){
    int bit, n=decArr[i];
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