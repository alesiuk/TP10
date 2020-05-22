#include "puertos.h"
regconjunto_u registro;

/**************************Funciones Privadas***************************************************/
int Toggle (int bit);				//como es una funcion privada, no se ubica el protipo en el header

int Toggle(int bit)							//funcion privada , ya que es complementaria a BitToggle
{
	if (bit==1)							//recibo un bit y devuelvo el opuesto
	{
		return 0;
	}	
	else
	{
		return 1;
	}
}
/*************************************************************************************************
********************************Funciones Publicas*********************************************/
void BitSet(char puerto, int bit)
{	
    if ((puerto=='D') || (puerto=='d'))
     {
	switch(bit)
	{
	    case 0: registro.bits.b0=1;break;
            case 1: registro.bits.b1=1;break;
            case 2: registro.bits.b2=1;break;
            case 3: registro.bits.b3=1;break;
            case 4: registro.bits.b4=1;break;
            case 5: registro.bits.b5=1;break;
            case 6: registro.bits.b6=1;break;
            case 7: registro.bits.b7=1;break; 
	    case 8: registro.bits.b8=1;break;
            case 9: registro.bits.b9=1;break;
            case 10: registro.bits.b10=1;break;
            case 11: registro.bits.b11=1;break;
            case 12: registro.bits.b12=1;break;
            case 13: registro.bits.b13=1;break;
            case 14: registro.bits.b14=1;break;
            case 15: registro.bits.b15=1;break; 
	}
     }
    else if ((puerto=='B') || (puerto=='b'))         		//pregunta ṕor el puerto en el q se desea hacer la modificacion 
    {                                         			  		//en el caso de que sea el B, pregunta por medio de un switch 
        switch(bit)                            				//cual es el bit marcado para prender
        {
            case 0: registro.bits.b0=1;break;
            case 1: registro.bits.b1=1;break;
            case 2: registro.bits.b2=1;break;
            case 3: registro.bits.b3=1;break;
            case 4: registro.bits.b4=1;break;
            case 5: registro.bits.b5=1;break;
            case 6: registro.bits.b6=1;break;
            case 7: registro.bits.b7=1;break;       
        }
    }
    else                            
    {
        switch(bit)
        {
            case 8: registro.bits.b8=1;break;
            case 9: registro.bits.b9=1;break;
            case 10: registro.bits.b10=1;break;
            case 11: registro.bits.b11=1;break;
            case 12: registro.bits.b12=1;break;
            case 13: registro.bits.b13=1;break;
            case 14: registro.bits.b14=1;break;
            case 15: registro.bits.b15=1;break; 
        }
                
    }
}
void BitClr(char puerto,int bit)
{
    if ((puerto=='D') || (puerto=='d'))
     {
	switch(bit)
	{
	    case 0: registro.bits.b0=0;break;
            case 1: registro.bits.b1=0;break;
            case 2: registro.bits.b2=0;break;
            case 3: registro.bits.b3=0;break;
            case 4: registro.bits.b4=0;break;
            case 5: registro.bits.b5=0;break;
            case 6: registro.bits.b6=0;break;
            case 7: registro.bits.b7=0;break; 
	    case 8: registro.bits.b8=0;break;
            case 9: registro.bits.b9=0;break;
            case 10: registro.bits.b10=0;break;
            case 11: registro.bits.b11=0;break;
            case 12: registro.bits.b12=0;break;
            case 13: registro.bits.b13=0;break;
            case 14: registro.bits.b14=0;break;
            case 15: registro.bits.b15=0;break; 
	}
     }	
    else if ((puerto=='B') || (puerto=='b'))         //pregunta ṕor el puerto en el q se desea hacer la modificacion 
    {                                           			//en el caso de que sea el B, pregunta por medio de un switch 
        switch(bit)                            			//cual es el bit marcado para apagar
        {
            case 0: registro.bits.b0=0;break;
            case 1: registro.bits.b1=0;break;
            case 2: registro.bits.b2=0;break;
            case 3: registro.bits.b3=0;break;
            case 4: registro.bits.b4=0;break;
            case 5: registro.bits.b5=0;break;
            case 6: registro.bits.b6=0;break;
            case 7: registro.bits.b7=0;break; 
        }
    }
    else                            
    {
        switch(bit)
        {
            case 8: registro.bits.b8=0;break;
            case 9: registro.bits.b9=0;break;
            case 10: registro.bits.b10=0;break;
            case 11: registro.bits.b11=0;break;
            case 12: registro.bits.b12=0;break;
            case 13: registro.bits.b13=0;break;
            case 14: registro.bits.b14=0;break;
            case 15: registro.bits.b15=0;break; 
        }               
    }
}
int BitGet(char puerto,int bit)
{
     if((puerto=='D') || (puerto=='d'))
     {
	switch(bit)
	{
	    case 0: return registro.bits.b0;break;
            case 1: return registro.bits.b1;break;
            case 2: return registro.bits.b2;break;
            case 3: return registro.bits.b3;break;
            case 4: return registro.bits.b4;break;
            case 5: return registro.bits.b5;break;
            case 6: return registro.bits.b6;break;
            case 7: return registro.bits.b7;break;  
	    case 8: return registro.bits.b8;break;
            case 9: return registro.bits.b9;break;
            case 10: return registro.bits.b10;break;
            case 11: return registro.bits.b11;break;
            case 12: return registro.bits.b12;break;
            case 13: return registro.bits.b13;break;
            case 14: return registro.bits.b14;break;
            case 15: return registro.bits.b15;break;
	}
     }
     else if ((puerto=='B') || (puerto=='b'))         //pregunta ṕor el puerto 
    {                                           //en el caso de que sea el A, pregunta por medio de un switch 
        switch(bit)                            //cual es el bit marcado para devolver
        {
            case 0: return registro.bits.b0;break;
            case 1: return registro.bits.b1;break;
            case 2: return registro.bits.b2;break;
            case 3: return registro.bits.b3;break;
            case 4: return registro.bits.b4;break;
            case 5: return registro.bits.b5;break;
            case 6: return registro.bits.b6;break;
            case 7: return registro.bits.b7;break;       
        }
    }
    else                            
    {
        switch(bit)
        {
            case 8: return registro.bits.b8;break;
            case 9: return registro.bits.b9;break;
            case 10: return registro.bits.b10;break;
            case 11: return registro.bits.b11;break;
            case 12: return registro.bits.b12;break;
            case 13: return registro.bits.b13;break;
            case 14: return registro.bits.b14;break;
            case 15: return registro.bits.b15;break;
        }
    }
}
void BitToggle (char puerto, int bit)
{
	int c=BitGet(puerto,bit);								//obtengo el estado original del bit seleccionado
	c=Toggle(c);										//obtengo el opuesto del estado mediante la funcion Toggle y la guardo en la var c
	if((puerto=='D') || (puerto='d'))						//pregunto que puerto me pasaron 
	{												//dependiendo del puerto que me pasaron y el bit , le asigno al bit seleccionado su nuevo estado
		switch(bit)
		{
			case 0: registro.bits.b0=c; break;
			case 1: registro.bits.b1=c; break;
			case 2: registro.bits.b2=c; break;
			case 3: registro.bits.b3=c; break;
			case 4: registro.bits.b4=c; break;
			case 5: registro.bits.b5=c; break;
			case 6: registro.bits.b6=c; break;
			case 7: registro.bits.b7=c; break;
			case 8: registro.bits.b8=c; break;
			case 9: registro.bits.b9=c; break;
			case 10: registro.bits.b10=c; break;
			case 11: registro.bits.b11=c; break;
			case 12: registro.bits.b12=c; break;
			case 13: registro.bits.b13=c; break;
			case 14: registro.bits.b14=c; break;
			case 15: registro.bits.b15=c; break;	
		}
	
	}
	else if((puerto=='B') || (puerto=='b'))						 
	{												
		switch(bit)
		{
			case 0: registro.bits.b0=c; break;
			case 1: registro.bits.b1=c; break;
			case 2: registro.bits.b2=c; break;
			case 3: registro.bits.b3=c; break;
			case 4: registro.bits.b4=c; break;
			case 5: registro.bits.b5=c; break;
			case 6: registro.bits.b6=c; break;
			case 7: registro.bits.b7=c; break;
		}	
	}
	else
	{
		switch(bit)
		{
			case 8: registro.bits.b8=c; break;
			case 9: registro.bits.b9=c; break;
			case 10: registro.bits.b10=c; break;
			case 11: registro.bits.b11=c; break;
			case 12: registro.bits.b12=c; break;
			case 13: registro.bits.b13=c; break;
			case 14: registro.bits.b14=c; break;
			case 15: registro.bits.b15=c; break;	
		}
	}
}

void MaskOn(char puerto,int mascara)
{
    int resultado;
    if((puerto=='D') || (puerto=='d'))
    {
	resultado=(registro.portD.word | mascara);
	registro.portD.word=resultado;
    }
    else if((puerto=='A') || ((puerto=='a')))
    {
        resultado=(registro.portA.high | mascara);          //se realiza un or(bitwise) entre el puerto y la mascara
        registro.portA.high=resultado;
    }
    else
    {
        resultado=(registro.portB.low | mascara);
        registro.portB.low=resultado;
    }
}
void MaskOff(char puerto,int mascara)
{
    int maskaux;
    int resultado;
    if( (puerto=='D') || (puerto=='d') )
    {
	maskaux=(registro.portD.word & mascara);
	resultado=(registro.portD.word ^ maskaux);
	registro.portD.word=resultado;
    }
    else if( (puerto=='A') || (puerto=='a'))
    {
        maskaux=(registro.portA.high & mascara);                //se realiza primero un AND entre el puerto y la mascara para que despues cuando realice
        resultado=(registro.portA.high ^ maskaux);               //el xor, no me modifique algun byte del puerto. De esta manera solo apago los que me 
        registro.portA.high=resultado;                        //indica la mascara respetando el estado del resto.
    }
    else
    {
        maskaux=(registro.portB.low & mascara);
        resultado=(registro.portB.low ^ maskaux);
        registro.portB.low=resultado;
    }
}
void MaskToggle(char puerto,int mascara)
{
    int resultado;
    if( (puerto=='D') || (puerto=='d') )
    {
	resultado=(registro.portD.word ^ mascara);
	registro.portD.word=resultado;	
    }
    else if( (puerto=='A') || (puerto=='a'))
    {
        resultado=(registro.portA.high ^ mascara);              //se realiza un xor(bitwise) entre el puerto y la mascara
        registro.portA.high=resultado;
    }
    else
    {
        resultado=(registro.portB.low & mascara);
        registro.portB.low=resultado;
    }
}
/*************************************************************************************/