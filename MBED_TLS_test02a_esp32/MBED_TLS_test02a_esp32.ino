#include "mbedtls/md.h"
//#include <Arduino.h>
//#include "src/lib_mbedtls/md.h"

long timefinal=0;
long timetemp=0;
long timer1;
long timer2;

char *key = "secretKeysecretKeysecretKeysecretKeysecretKeysecretKeysecretKeysecretKeysecretKeysecretKey";
char buffer_[2048];
char *buffer_big = buffer_;
char *payload = "0123456789abcdef123456789abcdef123456789abcdef123456789abcdef123456789abcdef123456789abcdef123456789abcdef123456789abcdef";
byte hmacResult[32];
 
  mbedtls_md_context_t ctx;
  mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
 
  //const size_t payloadLength = strlen(payload);
size_t payloadLength;
const size_t keyLength = strlen(key);  

int i,j,k;

void setup(){
timefinal=100000000; 
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
        mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
        mbedtls_md_hmac_starts(&ctx, (const unsigned char *) key, keyLength);
        mbedtls_md_hmac_update(&ctx, (const unsigned char *) payload, payloadLength);
        mbedtls_md_hmac_finish(&ctx, hmacResult);
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
    timefinal=100000000;

  }
  

  Serial.print("Hash: "); 
  for(int i= 0; i< sizeof(hmacResult); i++)
  {
      char str[3];
      sprintf(str, "%02x", (int)hmacResult[i]);
      Serial.print(str);
  }

while(true) {};
}
