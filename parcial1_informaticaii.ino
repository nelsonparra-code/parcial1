const int ser=3,rc=4,src=5,reset=6;
//:){24,36,66,0,36,36,36,0} {255,255,255,255,255,255,255,255}
int cont=1,aux;
int decArr[] = {193,195,199,207,219,243,195,131}, binArr[8];

void setup()
{
  pinMode(ser, OUTPUT);
  pinMode(src, OUTPUT);
  pinMode(rc, OUTPUT);
  pinMode(reset, OUTPUT);
  digitalWrite(reset,1);
}

void loop()
{
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

void store(int bit)
{
  digitalWrite(ser,bit);
  
  digitalWrite(src,0);
  digitalWrite(src,1);
  digitalWrite(src,0);
}

void show()
{
  digitalWrite(rc,0);
  digitalWrite(rc,1);
  digitalWrite(rc,0);
}