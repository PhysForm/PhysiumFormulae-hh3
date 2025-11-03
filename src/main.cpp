#include <appdef.h>
#include <sdk/os/debug.h>
#include <sdk/os/string.h>
#include <sdk/os/lcd.h>
#include <sdk/os/input.h>
#include <sdk/calc/calc.h>

APP_NAME("Physium Formulae")
APP_AUTHOR("PhysiumFormulae-dev")
APP_DESCRIPTION("The HHK3 version of Physium Formulae")
APP_VERSION("1.0.0")



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
					    while(num[1]!='_' && num[1]!='.'){
						    double ret = num[1]-'0';
						    int i=2;
						    while(num[i]!='_'){
						    	ret = (ret*10) + (num[i]-'0');
						    	i++;
						    }//num[i]!='_'
						    return ret;
              			} 
							break;
            case KEYCODE_X: Print(1,1,"No variables allowed in doubles");break;
            case KEYCODE_Y: Print(1,1,"No variables allowed in doubles");break;
            case KEYCODE_Z: Print(1,1,"No variables allowed in doubles");break;
            case KEYCODE_POWER_CLEAR: Print(1,1,"CLEAR NOT AVAILABLE USE: BACKSPACE");break;
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

void cls(){
	LCD_ClearScreen();
}


int main() {
    	fillScreen(0xFFFF);
  		UPD();
  		Debug_SetCursorPosition(264,160);
		Debug_PrintString("Physium Formulae",0);
		Debug_SetCursorPosition(263, 160);
		Debug_PrintString("ClassPad",0);
		UPD();
		while(true){
    		uint32_t key1, key2;    // First create variables
    		getKey(&key1, &key2); 
			cls();   // then read the keys
    		if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
    		    break;
    		}else if(testKey(key1,key2, KEY_CLEAR)){
				break;
			};
		}
		fillScreen(0xFFFF);
		UPD();
		Debug_SetCursorPosition(0,0);
  		Debug_PrintString("Physium Formulae\nClassPad", 0);
		Debug_SetCursorPosition(6,1);
		Debug_PrintString("[1] Solver",0);
		Debug_SetCursorPosition(6,2);
		Debug_PrintString("[2] Formulas",0);
		Debug_SetCursorPosition(6,3);
		Debug_PrintString("[3] Exit",0);
		UPD();
		uint32_t Menukey, MenKey;
		getKey(&Menukey, &MenKey);
		cls();
		if(Menukey == KEY_1){
			fillScreen(color(31,63,31));
			UPD();
			Debug_SetCursorPosition(1,0);
      		Debug_PrintString("Physium Formulae\nClassPad", 0);
			uint32_t k1, k2;
			getKey(&k1, &k2);
			Print(1,3,"Main Solver Menu");
			Print(1,5,"[1] GPE  GPE = m*g*h");
			Print(1,6,"[2] Force F = m*a ");
			Print(1,7,"[3] Fg = m*g");
			Print(1,8,"[4] Momentum = m*v");
			Print(1,9,"[5] Basic Work = F*d");
			Print(1,10,"[6] Work = F*d* cos(theta)"); 
			UPD();
			uint32_t SMenukey;
			uint32_t Skey;
			getKey(&SMenukey, &Skey);
			UPD();
			cls();
			if(SMenukey == KEY_1){
      			Debug_SetCursorPosition(0,160);
      			Debug_PrintString("Physium Formulae\nClassPad", 0);
				Debug_SetCursorPosition(6,0);
				Debug_PrintString("GPE Solver Submenu",0);
				Debug_SetCursorPosition(6,1);
				Debug_PrintString("[1] GPE",0);
				Debug_SetCursorPosition(6,2);
				Debug_PrintString("[2] Mass",0);
				Debug_SetCursorPosition(6,3);
				Debug_PrintString("[3] Acceleration to Gravity",0);
				Debug_SetCursorPosition(6,4);
				Debug_PrintString("[4] Height",0);
				UPD();
				uint32_t GPEKey;
				uint32_t ConfGPE;
				getKey(&GPEKey, &ConfGPE);
				UPD();
				cls();
				if(GPEKey == KEY_1){
					Print(1,1,"Mass?");
					UPD();
					double m = Input();
					cls();
					Print(1,1,"Acceleration to Gravity\ng on earth is ~9.8 m/s^2\n& is exactly 9.80665 m/s^2");
					UPD();
					double g = Input();
					cls();
					Print(1,1,"Height?");
					UPD();
					double h = Input();
					double GPE = g*m*h;
					cls();
					char* GPEAns = nullptr;
					Print(1,1, "GPE = ");
					Print(1, 2, dtstr(GPE,GPEAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
							break;
						}
					}
				}else if(GPEKey == KEY_2){
        			Debug_SetCursorPosition(0,160);
        			Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(1,1,"GPE=?");
					UPD();
					double GPE = Input();
        			cls();
	        		Debug_SetCursorPosition(0,160);
    	    		Debug_PrintString("Physium Formulae\nClassPad", 0);
	        		Print(1,1,"Acceleration to Gravity\ng on earth is ~9.8 m/s^2\n& is exactly 9.80665 m/s^2");
    	    		UPD();
        			double g = Input();
        			cls();
        			Debug_SetCursorPosition(0,160);
        			Debug_PrintString("Physium Formulae\nClassPad", 0);
        			Print(160,264,"Height=?");
        			UPD();
        			double h = Input();
        			cls();
        			Debug_SetCursorPosition(0,160);
	        		Debug_PrintString("Physium Formulae\nClassPad", 0);
    	    		Print(160,264,"Mass =");
					double m = (GPE /(g*h));
					char* Mass = nullptr;
					Print(160,264,dtstr(m,Mass));
					UPD();
					while(true){
    	  				uint32_t key1, key2;    // First create variables
      					getKey(&key1, &key2);    // then read the keys
      					break;
	    			};
				}else if(GPEKey == KEY_3){
        			Debug_SetCursorPosition(0,160);
        			Debug_PrintString("Physium Formulae\nClassPad", 0);
        			Print(160,264,"GPE = ?");
					UPD();
					double GPE = Input();
					cls();
					Debug_SetCursorPosition(0,160);
        			Debug_PrintString("Physium Formulae\nClassPad", 0);
        			Print(160,264,"Mass = ?");
					UPD();
					double Mass = Input();
					cls();
					Debug_SetCursorPosition(0,160);
        			Debug_PrintString("Physium Formulae\nClassPad", 0);
        			Print(160,264,"Height = ?");
					UPD();
					double Height = Input();
					cls();
					double g = GPE / (Mass * Height);
					char* gAns = nullptr;
					Print(160,264,"Acceleration to Gravity =");
					Print(160,298,dtstr(g,gAns));
					UPD();
					while(true){
    	  				uint32_t key1, key2;    // First create variables
      					getKey(&key1, &key2);    // then read the keys
						break;
	    			};
				}else if(GPEKey == KEY_4){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"GPE = ?");
					UPD();
					double GPE = Input();
					cls();
					Print(160,264,"Mass = ?");
					UPD();
					double Mass = Input();
					cls();
					Print(160,264,"Acceleration to Gravity\ng on earth is ~9.8 m/s^2\n& is exactly 9.80665 m/s^2");
					UPD();
					double g = Input();
					cls();
					double Height = GPE / (Mass * g);
					char* HeightAns = nullptr;
					Print(160,264,"Height =");
					Print(160,298,dtstr(Height,HeightAns));
					UPD();
					while(true){
		  				uint32_t key1, key2;    // First create variables
	  					getKey(&key1, &key2);
						break; // Break the loop to exit the program
	    			};
				}
		
			} else if(SMenukey == KEY_2){
				Debug_SetCursorPosition(0,160);
				Debug_PrintString("Physium Formulae\nClassPad", 0);
				Debug_SetCursorPosition(6,0);
				Debug_PrintString("Force Solver Submenu",0);
				Debug_SetCursorPosition(6,1);
				Debug_PrintString("[1] Force",0);
				Debug_SetCursorPosition(6,2);
				Debug_PrintString("[2] Mass",0);
				Debug_SetCursorPosition(6,3);
				Debug_PrintString("[3] Acceleration",0);
				UPD();
				uint32_t ForceKey;
				uint32_t ConfForce;
				getKey(&ForceKey, &ConfForce);
				UPD();
				cls();
				if(ForceKey == KEY_1){
					Print(160,264,"Mass?");
					UPD();
					double m = Input();
					cls();
					Print(160,264,"Acceleration?");
					UPD();
					double a = Input();
					double F = m * a;
					cls();
					char* ForceAns = nullptr;
					Print(160,150,"Force = ");
					Print(160,264,dtstr(F,ForceAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
							break;
						}
					}
				}else if(ForceKey == KEY_2){

					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Force=?");
					UPD();
					double F = Input();
					cls();
	        		Debug_SetCursorPosition(0,160);
		    		Debug_PrintString("Physium Formulae\nClassPad", 0);
	        		Print(160,264,"Acceleration?");
		    		UPD();
					double a = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Mass =");
					double m = F / a;
					char* MassAns = nullptr;
					Print(160,264,dtstr(m,MassAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					};
				} else if(ForceKey == KEY_3){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Force = ?");
					UPD();
					double F = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Mass = ?");
					UPD();
					double m = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Acceleration =");
					double a = F / m;
					char* AccelAns = nullptr;
					Print(160,264,dtstr(a,AccelAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					};
				}
			} else if(SMenukey == KEY_3){
				Debug_SetCursorPosition(0,0);
				Debug_PrintString("Physium Formulae\nClassPad", 0);
				Print(2,264,"Force of Gravity Solver Submenu");
				Print(2,281,"[1] Force of Gravity Fg");
				Print(2,298,"[2] Mass");
				Print(2,315,"[3] Acceleration to Gravity");
				UPD();
				uint32_t FgKey;
				uint32_t ConfFg;
				getKey(&FgKey, &ConfFg);
				cls();
				if(FgKey == KEY_1){
					cls();
					Print(160,264,"Mass?");
					UPD();
					double m = Input();
					cls();
					Print(160,264,"Acceleration to Gravity\ng on earth is ~9.8 m/s^2\n& is exactly 9.80665 m/s^2");
					UPD();
					double g = Input();
					double Fg = m * g;
					cls();
					char* FgAns = nullptr;
					Print(160,150,"Force of Gravity = ");
					Print(160,264,dtstr(Fg,FgAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						if(testKey(key1, key2, KEY_EXE)){ // Use testKey() to test if a specific key is pressed 
							break;
						}
					}
				} else if(FgKey == KEY_2){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Force of Gravity=?");
					UPD();
					double Fg = Input();
					cls();
	        		Debug_SetCursorPosition(0,160);
		    		Debug_PrintString("Physium Formulae\nClassPad", 0);
	        		Print(160,264,"Acceleration to Gravity\ng on earth is ~9.8 m/s^2\n& is exactly 9.80665 m/s^2");
		    		UPD();
					double g = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Mass =");
					double m = Fg / g;
					char* MassFgAns = nullptr;
					Print(160,264,dtstr(m,MassFgAns));
					UPD();
					while(true){
		  				uint32_t key1, key2;    // First create variables
	  					getKey(&key1, &key2);    // then read the
					}
				} else if(FgKey == KEY_3){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Force of Gravity = ?");
					UPD();
					double Fg = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Mass = ?");
					UPD();
					double m = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Acceleration to Gravity =");
					double g = Fg / m;
					char* AccelFgAns = nullptr;
					Print(160,264,dtstr(g,AccelFgAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				}
			} else if(SMenukey == KEY_4){
				Debug_SetCursorPosition(0,160);
				Debug_PrintString("Physium Formulae\nClassPad", 0);
				Print(160,264,"Momentum Solver Submenu");
				Print(160,264+17,"[1] Momentum");
				Print(160,264+17+17,"[2] Mass");
				Print(160,264+34+17,"[3] Velocity");
				UPD();
				uint32_t pKey, pkeyconf;
				getKey(&pKey, &pkeyconf);
				cls();
				if(pKey == KEY_1){
					Print(160,264,"Mass?");
					UPD();
					double m = Input();
					cls();
					Print(160,264,"Velocity?");
					UPD();
					double v = Input();
					double p = m * v;
					cls();
					char* pAns = nullptr;
					Print(160,150,"Momentum = ");
					Print(160,264,dtstr(p,pAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				} else if(pKey == KEY_2){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Momentum=?");
					UPD();
					double p = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Velocity?");
					UPD();
					double v = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Mass =");
					double m = p / v;
					char* MasspAns = nullptr;
					Print(160,264,dtstr(m,MasspAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				} else if(pKey == KEY_3){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Momentum = ?");
					UPD();
					double p = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Mass = ?");
					UPD();
					double m = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Velocity =");
					double v = p / m;
					char* VelAns = nullptr;
					Print(160,264,dtstr(v,VelAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				}
			} else if(SMenukey == KEY_5){
				Debug_SetCursorPosition(0,160);
				Debug_PrintString("Physium Formulae\nClassPad", 0);
				Print(160,264,"Basic Work Solver Submenu");
				Print(160,264+17,"[1] Basic Work");
				Print(160,264+34+17,"[2] Force");
				Print(160,264+51+17,"[3] Distance");
				UPD();
				uint32_t WorkKey;
				uint32_t Confwork;
				getKey(&WorkKey, &Confwork);
				cls();
				if(WorkKey == KEY_1){
					Print(160,264,"Force?");
					UPD();
					double F = Input();
					cls();
					Print(160,264,"Distance?");
					UPD();
					double d = Input();
					double W = F * d;
					cls();
					char* WorkAns = nullptr;
					Print(160,150,"Basic Work = ");
					Print(160,264,dtstr(W,WorkAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);
						break;
					}
				} else if(WorkKey == KEY_2){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Work=?");
					UPD();
					double W = Input();
					cls();
	        		Print(160,264,"Distance=?");
		    		UPD();
					double d = Input();
					cls();
	        		Debug_SetCursorPosition(0,160);
		    		Debug_PrintString("Physium Formulae\nClassPad", 0);
	        		Print(160,264,"Force =");
		    		double F = W / d;
					char* ForceAns = nullptr;
					Print(160,264,dtstr(F,ForceAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				}else if(WorkKey == KEY_3){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Work = ?");
					UPD();
					double W = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Force = ?");
					UPD();
					double F = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Distance =");
					double d = W / F;
					char* DistAns = nullptr;
					Print(160,264,dtstr(d,DistAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				}
			} else if(SMenukey == KEY_6){
				Debug_SetCursorPosition(0,160);
				Debug_PrintString("Physium Formulae\nClassPad", 0);
				Print(160,264,"Work Solver Submenu");
				Print(160,264+17,"[1] Work");
				Print(160,264+34+17,"[2] Force");
				Print(160,264+51+17,"[3] Distance");
				Print(160,264+68+17,"[4] Angle (in degrees)");
				UPD();
				uint32_t WorkKey;
				uint32_t Confwork;
				getKey(&WorkKey, &Confwork);
				cls();
				if(WorkKey == KEY_1){
					Print(160,264,"Force?");
					UPD();
					double F = Input();
					cls();
					Print(160,264,"Distance?");
					UPD();
					double d = Input();
					cls();
					Print(160,264,"Angle in degrees?");
					UPD();
					double angle = Input();
					double radian = angle * (3.14159265358979323846 / 180.0); // Convert degrees to radians
					double cosValue = cos(radian);
					double W = F * d * cosValue;
					cls();
					char* WorkAns = nullptr;
					Print(160,150,"Work = ");
					Print(160,264,dtstr(W,WorkAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				} else if(WorkKey == KEY_2){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Work=?");
					UPD();
					double W = Input();
					cls();
	        		Debug_SetCursorPosition(0,160);
		    		Debug_PrintString("Physium Formulae\nClassPad", 0);
	        		Print(160,264,"Distance=?");
		    		UPD();
					double d = Input();
					cls();
	        		Print(160,264,"Angle in degrees?");
		    		UPD();
					double theta = Input();
					double radian = theta * (3.14159265358979323846 / 180.0); // Convert degrees to radians
					double cosValue = cos(radian);
					cls();
	        		Debug_SetCursorPosition(0,160);
		    		Debug_PrintString("Physium Formulae\nClassPad", 0);
	        		Print(160,264,"Force =");
		    		double F = W / (d * cosValue);
					char* ForceAns = nullptr;
					Print(160,264,dtstr(F,ForceAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				}else if(WorkKey == KEY_3){
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Work = ?");
					UPD();
					double W = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Force = ?");
					UPD();
					double F = Input();
					cls();
					Debug_SetCursorPosition(0,160);
					Debug_PrintString("Physium Formulae\nClassPad", 0);
					Print(160,264,"Distance =");
	        		Print(160,264+17,"Angle in degrees?");
		    		UPD();
					double d = W / F;
					double angle = Input();
					double radian = angle * (3.14159265358979323846 / 180.0); // Convert degrees to radians
					double cosValue = cos(radian);
					d /= cosValue;
					char* DistAns = nullptr;
					Print(160,264,dtstr(d,DistAns));
					UPD();
					while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;
					}
				} else if(WorkKey == KEY_4){
	        		Debug_SetCursorPosition(0,160);
		    		Debug_PrintString("Physium Formulae\nClassPad", 0);
	        		Print(160,264,"Work = ?");
		    		UPD();
		    		double W = Input();
		    		cls();
		    		Debug_SetCursorPosition(0,160);
		    		Debug_PrintString("Physium Formulae\nClassPad", 0);
		    		Print(160,264,"Force = ?");
		    		UPD();
		    		double F = Input();
		    		cls();
		    		Debug_SetCursorPosition(0,160);
		    		Debug_PrintString("Physium Formulae\nClassPad", 0);
		    		Print(160,264,"Distance = ?");
		    		UPD();
		    		double d = Input();
		    		cls();
	        		Debug_SetCursorPosition(0,160);
		    		Debug_PrintString("Physium Formulae\nClassPad", 0);
		    		Print(160,264,"Angle in degrees =");
		    		UPD();
		    		double radian = cos(W / (F * d)); // Calculate the angle in radians
		    		double angle = radian * (180.0 / 3.14159265358979323846); // Convert radians to degrees
		    		char* AngleAns = nullptr;
		    		Print(160,264,dtstr(angle,AngleAns));
		    		UPD();
		    		while(true){
						uint32_t key1, key2;    // First create variables
						getKey(&key1, &key2);    // then read the keys
						break;	
					}
				}
			} else if(SMenukey == KEY_3){
				Debug_SetCursorPosition(0,160);
				Debug_PrintString("Physium Formulae\nClassPad", 0);
				Debug_SetCursorPosition(6,0);
				Debug_PrintString("NEW IDEA COMING SOON!",0);
				UPD();
				while(true){
					uint32_t key1, key2;    // First create variables
					getKey(&key1, &key2);    // then read the keys
					break;
				}
			}
		}else if (Menukey == KEY_2){
			cls();
	    	Debug_SetCursorPosition(0,160);
    		Debug_PrintString("Physium Formulae\nClassPad", 0);
    		Debug_SetCursorPosition(160,0);
			Debug_PrintString("Formulas",0);
			Print(0,527,"WIP");
			Print(160,40,"GPE = mass * accel. to grav. * height");
			Print(160,80,"F = Mass * Acceleration");
			Print(160,120,"p = Mass * Velocity");
			Print(160,160,"Basic Work = Force * Distance");
			UPD();
			while(true){
				uint32_t key1, key2;    // First create variables
	  			getKey(&key1, &key2);
				break;
			};
		}else if (Menukey == KEY_3){
    		Debug_SetCursorPosition(0,160);
    		Debug_PrintString("Physium Formulae\nClassPad", 0);
    		Debug_SetCursorPosition(264,160);
    		Debug_PrintString("Program Terminating...",0);
    		UPD();
			while(true){
				break;
			}
		}
						
			//if(testkey(SMenukey, KEY_1)){
			//	Debug_PrintString("GPE Solver Submenu");
			//	Debug_PrintString("[1] GPE");const char *string
			//	Debug_PrintString("[2] Mass");
			//	Debug_PrintString("[3] Acceleration to Gravity");
			//	Debug_PrintString("[4] Height");
			//	uint32_t GPEKey;
			//	getkey(&GPEKey);
			//	if(testkey())
			//	}
		//case KEY_2:
		//	Debug_PrintString(" Not Complete!",1);
		//	return 0;
		//case KEY_3:
		//	return 0;

		UPD();
		cls();
  Debug_WaitKey();
  return 0;
}
