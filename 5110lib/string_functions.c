unsigned char message[70];
unsigned int8 strlen(char *s)
{
   char *sc;

   for (sc = s; *sc != 0; sc++);
   return(sc - s);
}

void display_char_byte(unsigned char ascii_char, unsigned char char_column)
{
   unsigned char char_position;
   if (ascii_char<0x50)
   {
      char_position=(((ascii_char&0xff)-0x20)*5);
      nokia_write_data(TABLE1[(char_position+char_column)]);
   }
   else if (ascii_char>0x4f)
   {
      char_position=(((ascii_char&0xff)-0x50)*5);
      nokia_write_data(TABLE2[(char_position+char_column)]);
   }   
   else return;
}
void display_R2L(unsigned char line)
{
   unsigned char a, b, c, d;
   for(a=0; a<strlen(message) - 14; a++)
   {
      for (b=0; b<5; b++)
      {
         nokia_gotoxy(0,line-1);
         for(c=b; c<5; c++) display_char_byte(message[a],c);
         if(b!=4) nokia_write_data(0x00);
         for (d=1; d<14; d++) nokia_printchar(message[a+d]);         
         for (c=1; c<=b; c++) display_char_byte(message[a+14],c-1);
         if(b==4) display_char_byte(message[a+14],4);
         //delay_ms(50);      
      }     
   }   
}
void display_R2L_fast(unsigned char line)
{
   unsigned char a, b;
   for(a=0; a<strlen(message) - 14; a++)
   {
      nokia_gotoxy(0,line-1);
      for (b=0; b<14; b++) nokia_printchar(message[a+b]);
      delay_ms(200);    
   }   
}
