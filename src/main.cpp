#include <appdef.h>
#include <sdk/os/debug.h>
#include <sdk/os/string.h>
#include <sdk/os/lcd.h>
#include <sdk/os/input.h>
#include <sdk/os/gui/dialog.hpp>
#include <string>
#include <array>
#include <cstdio>

APP_NAME("Physium Formulae")
APP_AUTHOR("The HHK3 version of Physium Formulae")
APP_DESCRIPTION("A very cool app!")
APP_VERSION("1.0.0")


    std::string exec(const char* cmd) {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }


void Print(int x, int y, const char* text){
  Debug_Printf(x,y,false,0,"%s", text);
  LCD_Refresh();
}
char* dtstr(double value, char* buffer, int precision = 1000000000) {
    // Basic implementation for positive numbers and limited precision
    long long intPart = static_cast<long long>(value);
    double fracPart = value - intPart;

    int i = 0;
    // Convert integer part
    if (intPart == 0) {
        buffer[i++] = '0';
    } else {
        // Reverse digits
        char temp[20]; // Temporary buffer for digits
        int k = 0;
        while (intPart > 0) {
            temp[k++] = (intPart % 10) + '0';
            intPart /= 10;
        }
        while (k > 0) {
            buffer[i++] = temp[--k];
        }
    }

    // Add decimal point and fractional part (simplified)
    if (precision > 0) {
        buffer[i++] = '.';
        for (int p = 0; p < precision; ++p) {
            fracPart *= 10;
            int digit = static_cast<int>(fracPart);
            buffer[i++] = digit + '0';
            fracPart -= digit;
        }
    }
    buffer[i] = '\0'; // Null-terminate the string
    return buffer;
}
void UPD(){
	LCD_Refresh();
}
int pow(double base, double exp) {
	int result = 1;
	for (int i = 0; i < exp; ++i) {
		result *= base;
	}
	return result;
}
int factorial(int n){
	if(n == 1){
		double result = 1;
		return result;
	} else{
		double result = 1;
		for(int i = 1; i <= n; i++){
			result *= i;
		}
		return result;
	}
}
int cos(double x,double termn = 1000000000000000000){
	int cos_x = 0;
	if(x < 45 and x > 0){
		return (1 - (0.000145 *(x * x)));
	}else{
		for (int n =0; n < termn; ++n) { //for (int n = 0; n < 10; ++n) {// Code to be executed in each iteration}
			double pow_x = 2*n;
			int term = ( pow((-1),n) * pow(x,pow_x)) / factorial(pow_x);
			cos_x += term;
		}
	}
	return cos_x;
}

double Input(){
  char num[13];
  int pos = 1;
  String_Strcpy(num, ">_                            ");

  struct Input_Event event;
  while (true) {
    Debug_Printf(1,43,false,0,"%s",num); UPD();
		GetInput(&event,0xFFFFFFFF,0x10);
    if(event.type==EVENT_KEY){
      if( event.data.key.direction==KEY_PRESSED){
        if(pos<=28){
          switch(event.data.key.keyCode){
            case KEYCODE_0: num[pos++]='0';num[pos]='_';break;
						case KEYCODE_1: num[pos++]='1';num[pos]='_';break;
						case KEYCODE_2: num[pos++]='2';num[pos]='_';break;
						case KEYCODE_3: num[pos++]='3';num[pos]='_';break;
						case KEYCODE_4: num[pos++]='4';num[pos]='_';break;
						case KEYCODE_5: num[pos++]='5';num[pos]='_';break;
						case KEYCODE_6: num[pos++]='6';num[pos]='_';break;
						case KEYCODE_7: num[pos++]='7';num[pos]='_';break;
						case KEYCODE_8: num[pos++]='8';num[pos]='_';break;
						case KEYCODE_9: num[pos++]='9';num[pos]='_';break;
            case KEYCODE_NEGATIVE: num[pos++]='-';num[pos]='_';break;
            case KEYCODE_EXP: Print(1,1,"No Exponents in Double Please");break;
						case KEYCODE_OPEN_PARENTHESIS:Print(1,1,"No Special Characters in Double Please");break;
            case KEYCODE_CLOSE_PARENTHESIS:Print(1,1,"No Special Characters in Double Please");break;
            case KEYCODE_PLUS:Print(1,1,"No Operations in Double Please");break;
            case KEYCODE_MINUS:Print(1,1,"No Operations in Double Please");break;
            case KEYCODE_EQUALS:Print(1,1,"No Operations in Double Please");break;
            case KEYCODE_TIMES:Print(1,1,"No Operations in Double Please");break;
            case KEYCODE_DIVIDE:Print(1,1,"No Operations in Double Please");break;
            case KEYCODE_COMMA:Print(1,1,"No Special Characters in Double Please");break;
            case KEYCODE_POWER: Print(1,1,"No Exponents in Double Please");break;
            case KEYCODE_BACKSPACE: 
              if(pos>1){
                num[pos--]=' ';num[pos]='_';break;
              } else{
                Print(1,1,"ERROR: TOO LITTLE \nCHARACTERS");
              }
            case KEYCODE_EXE: 
					    while(num[1]!='_'&&num[1]!='.'){
						    double ret = num[1]-'0';
						    int i=2;
						    while(num[i]!='_'){
						    	ret = (ret*10) + (num[i]-'0');
						    	i++;
						    }//num[i]!='_'
						    return ret;
              }
            case KEYCODE_X: Print(1,1,"No variables allowed in doubles");break;
            case KEYCODE_Y: Print(1,1,"No variables allowed in doubles");break;
            case KEYCODE_Z: Print(1,1,"No variables allowed in doubles");break;
            case KEYCODE_POWER_CLEAR: Print(1,1,"CLEAR NOT \nAVAILABLE \nUSE: BACK\n-SPACE");break;
            case KEYCODE_DOWN:   Print(1,1,"No Direction available for doubles");break;
            case KEYCODE_UP:    Print(1,1,"No Direction available for doubles");break;
            case KEYCODE_LEFT:    Print(1,1,"No Direction available for doubles");break;
            case KEYCODE_RIGHT :   Print(1,1,"No Direction available for doubles");break;
            case KEYCODE_DOT: 
							if (pos==1){
								if(num[1]=='.'){
                  return 0.0;
								}else{ 
									break;
									num[1]='.';
									return 0.0; //Return 0.0 if the user inputs a dot at the start.
								}
							}break;
						case KEYCODE_KEYBOARD: 
							UPD();
							Debug_PrintString("ERROR! ", 0);
							return 0;
						case KEYCODE_SHIFT: 
							return 0;
            
          }
        }
      }
    } else{
      return 0;
    }
    
  };
}



int main() {
  Debug_WaitKey();
  
}