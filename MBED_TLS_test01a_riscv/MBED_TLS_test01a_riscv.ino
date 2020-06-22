//#include "mbedtls/md.h"
#include <Arduino.h>
#include "src/lib_mbedtls/md.h"
 
long timefinal=0;
long timetemp=0;
long timer1;
long timer2;

char buffer_[2048];
char *buffer_big = buffer_;
char *payload = "0123456789abcdef123456789abcdef123456789abcdef123456789abcdef123456789abcdef123456789abcdef123456789abcdef123456789abcdef";
uint8_t shaResult[32];
 
mbedtls_md_context_t ctx;
mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
 
//size_t payloadLength = strlen(payload);
size_t payloadLength;

int i,j,k;
 
void setup()
{
  timefinal=10000000;
  Serial.begin(115200);
}
 
void loop()
{
  
  for(i=1;i<17;i++)
  {
    for (j = 0; j < 128; j++) 
      {
        buffer_big += payload[i];
      }
    //payloadLength = strlen(buffer_big);
    payloadLength = i*128;
    for(k=0;k<100;k++)
      {

          timer1=micros(); 
          mbedtls_md_init(&ctx);
          mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
          mbedtls_md_starts(&ctx);
          mbedtls_md_update(&ctx, (const unsigned char *) buffer_big, payloadLength);
          mbedtls_md_finish(&ctx, shaResult);
          mbedtls_md_free(&ctx);
          timer2=micros();
          timetemp=timer2-timer1;
          if(timetemp<timefinal)timefinal=timetemp;
      }
    Serial.print("Time: ");
    Serial.println(timefinal);
    Serial.println("");
    Serial.print("Size: ");
    Serial.println(payloadLength);
    Serial.println("");
    timefinal=1000000;

  }
    
 

 
for(int i= 0; i< sizeof(shaResult); i++)
{
char str[3];
sprintf(str, "%02x", (int)shaResult[i]);
Serial.print(str);

}
while(true) {};
}
