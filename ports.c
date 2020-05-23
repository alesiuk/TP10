/*
ports.c - Source file
Esta libreria se utiliza para el manejo completo de puertos de un microcontrolador
Controla 2 puertos de 8 bits (A y B) y un puerto de 16 bits (D) que es en realidad la union de los anteriores
Creado por el grupo 5 en mayo de 2020
*/

#include "ports.h"

/*DEFINICIONES DE CONSTANTES*/
#define MAX_OPERATIONS 20	//Maxima cantidad de operaciones diferentes que se pueden realizar. Incrementar para agregar mas

/*ARREGLOS GLOBALES EN FILE LEVEL*/
static int operation_code_array[MAX_OPERATIONS];						//En este arreglo se guardan los codigos de operacion.
static BOOLEAN (*operations[MAX_OPERATIONS])(char, int);				//En este arreglo se guardan los punteros a las funciones de operacion
//Estos arreglos estan ordenados de forma tal que son del mismo tamaño y que la posicion de un opcode y de un puntero a una funcion de operacion
//relativo al comienzo del arreglo correspondiente es la misma, y en esto basa su funcionamiento la funcion get_operation

/*PROTOTIPOS DE FUNCIONES INTERNAS GENERALES*/
static BOOLEAN add_operation (int operation_code, int (*operation_function)(char, int)); //Agrega las operaciones en forma dinamica
static int get_operation (int opcode);	//Obtiene la posicion de la operacion buscada respecto al inicio del arreglo de punteros
static BOOLEAN is_a_valid_port (char port); //Esta funcion comprueba que el identificador de puerto provisto sea valido
static BOOLEAN is_a_valid_bit (char port, int bit);	//Dado un puerto valido, esta funcion comprueba si el numero de bit pedido es valido

/*PROTOTIPOS DE FUNCIONES INTERNAS DE MANEJO DE PUERTOS*/
static BOOLEAN bitSet (char port, int data);		//Setea (pone en 1) un bit de un puerto determinado
static BOOLEAN bitClear (char port, int data);		//Limpia (pone en 0) un bit de un puerto determinado
static BOOLEAN bitToggle (char port, int data);		//Conmuta el valor de un bit de un puerto determinado
//static BOOLEAN bitGet (char port, int data);		//Obtiene y devuelve el valor de un bit de un puerto determinado
static BOOLEAN maskOn (char port, int data);		//Enciende todos los bits de un puerto segun los bits seteados de una mascara
//static BOOLEAN maskOff (char port, int data);		//Apaga todos los bits de un puerto segun los bits seteados de una mascara
//static BOOLEAN maskToggle (char port, int data);	//Conmuta todos los bits de un puerto segun los bits seteados de una mascara

/*FUNCION EXTERNA*/

//Esta funcion realiza operaciones sobre los puetos de un microcontrolador. Devuelve TRUE si hubo un error, o FALSE si no lo hubo
//Recibe la operacion que hay que realizar en la variable operation mediante un opcode definido y los datos necesarios para la operacion
BOOLEAN port_operations(int operation, char port, int data){
//Agrego dinamicamente las operaciones
	static BOOLEAN ops_added = FALSE;
	if (ops_added == FALSE){	//Defino dinamicamente las operaciones al iniciar, pero solo la primera vez que ejecuto esta funcion
		ops_added = TRUE;				//Defino que ya se añadieron las operaciones para no hacerlo mas de una vez 
		int error = 0;					//Variable para errores
		error += add_operation(0, bitSet);	//Cargo cada operacion y veo si hubo un error al cargarlas, sumando a la variable error
		error += add_operation(1, bitClear);
		error += add_operation(2, bitToggle);
		//error += add_operation(3, bitGet);
		error += add_operation(4, maskOn);
		//error += add_operation(5, maskOff);
		//error += add_operation(6, maskToggle);
		if (error != 0){				//Si no hubo errores, esta variable tiene que seguir valiendo cero
			return TRUE;				//Asique si la variable no es cero, hubo un error y se informa
		}
	}
//Busqueda y llamado a funcion que realiza las operaciones
	BOOLEAN error1;							//Esta variable detecta si hubo un error en alguna funcion de operacion
	int op_position_in_array = get_operation(operation);	//Obtengo la posicion de la operacion
	if (op_position_in_array == -1){						//Si get_operation devolvio -1 no se encontro el opcode. Error
		error1 = TRUE;
	}
	else{
		error1 = operations[op_position_in_array](port, data);	//Si el opcode es valido, realizo la operacion pedida
	}
	return error1;								//Vuelvo al programa principal, devuelvo que no hubo errores
}

/*FUNCIONES INTERNAS*/

//Esta funcion carga las operaciones de manera dinamica. Recibe un puntero a la funcion de operacion y el codigo de operacion
//Devuelve FALSE si no hubo errores o TRUE si los hubo
static BOOLEAN add_operation (int operation_code, int (*operation_function)(char, int)){
	static int last_added = -1;					//Esta variable se usa para ir agregando funciones al arreglo
	if (last_added > (MAX_OPERATIONS - 1)){				//Compruebo que no se haya excedido el maximo de operaciones soportadas
		printf ("Error: se añadieron demasiadas operaciones. El maximo es %d.\n", MAX_OPERATIONS);
		printf ("Incremente \"MAX_OPERATIONS\" en \"ports.c\" para soportar mas operaciones.\n");
		return TRUE;						//Si se excedio devuelvo un error
	}								//Caso contrario:
	operation_code_array[++last_added] = operation_code;		//Agrego el codigo de operacion al arreglo
	operations[last_added] = operation_function;			//Agrego el puntero a la operacion en el arreglo correspondiente
	return FALSE;							//Devuelvo que no hubo errores
}

//Esta funcion recibe el opcode de la operacion a realizar y devuelve la posicion de la operacion buscada en el arreglo de operaciones
//Tipicamente la posicion de la operacion en el arreglo coincide con el opcode, pero esto puede no ser verdad siempre, ya que si se
//agregaran operaciones, podrian quedar desordenadas. Si no se encuentra el opcode devuelve -1
static int get_operation (int opcode){
	unsigned int i = 0;								//Esta variable recorre el arreglo de opcodes
	while (operation_code_array[i] != opcode){		//Mientras no se encuentre el opcode pedido, incrementar la variable
		i++;
		if (i == MAX_OPERATIONS){					//Si se recorrio todo el arreglo sin una coincidencia, ese opcode no existe
			i = -1;									//Entonces devuelvo un error
			printf ("Error: El opcode %d no corresponde a ninguna operacion conocida.\n", opcode);
			break;									//Y salgo del while
		}
	}
	return i;	//Al encontrar el opcode, la devolver la variable. Esta variable le indicara al
}				//programa en que posicion del arreglo de punteros se encuentra el puntero a la funcion que necesita

//Esta funcion verifica si se recibio una letra de puerto correcta recibiendola en un char y devuelve TRUE o FALSE segun lo sea o no
static BOOLEAN is_a_valid_port (char port){
	char valid_ports[6] = {'a', 'A', 'b', 'B', 'd', 'D'};		//Estas son las posibilidades correctas
	BOOLEAN valid = FALSE;						//Comienzo suponiendo que la letra no es valida
	for (unsigned int i = 0; i < 6; i++){		//Y luego para cada posicion del arreglo de letras de puerto validas, veo si coinciden
		valid = ((port == valid_ports[i]) ? TRUE : valid);		//Si el char recibido coincide con alguna posicion del arreglo hago valid = TRUE, y si
	}								//no coincide dejo valid como esta para no perder la validez
	if (valid == FALSE){
		printf ("Error: El caracter %c no es un identificador de puerto valido.\n", port);
	}
	return valid;						//Devuelvo el valor de si la entrada es o no un identificador de puerto valido
}

//Esta funcion verifica si el numero de bit ingresado es valido segun el puerto dado. Recibe un char de identificador de puerto y el numero de bit, y
//devuelve BOOLEAN FALSE si no es valido, o TRUE si lo es
static BOOLEAN is_a_valid_bit (char port, int bit){
	BOOLEAN valid;				//Variable para evaluar la validez
	int maxbits;				//Variable que contendra el maximo de bits permitidos para el puerto
	switch(port){
		case 'A': case 'a':
		case 'B': case 'b':
			maxbits = 7;		//Los puertos A y B son de 8 bits (numerados de 0 a 7)
			break;
		case 'D': case 'd':
			maxbits = 15;		//El puerto D es de 16 bits (numerados de 0 a 15)
			break;
		default:
			break;				//Caso por defecto (nunca se deberia utilizar)
	}
	valid = ((bit <= maxbits) ? TRUE : FALSE);		//Verifico que el numero de bit sea menor o igual a maxbits. Valid es FALSE si esto no se cumple
	if (valid == FALSE){
		printf ("Error: El numero de bit excede el maximo permitido para el puerto especificado (%d).\n", maxbits);
	}
	if (bit < 0){				//Por ultimo, si el numero de bit es negativo, esto es un error
		printf ("El numero de bit no puede ser negativo.\n");
		valid = FALSE;			//Y se fuerza valid a ser FALSE
	}
	return valid;				//Devuelvo la validez
}

//Esta funcion si la mascara recibida en data es valida o no segun el puerto dado. Recibe, ademas de la mascara en un int, un identificador de puerto ya validado
//en forma de un char. Devuelve BOOLEAN FALSE si no es valido, o TRUE si lo es
static BOOLEAN is_a_valid_mask (char port, int mask){
	BOOLEAN valid;				//Variable para evaluar la validez
	int maxmask;				//Variable que contendra el maximo valor de la mascara permitido para el puerto
	int maxbits;				//Variable que contendra el maximo de bits permitidos para el puerto
	switch(port){
		case 'A': case 'a':
		case 'B': case 'b':
			maxmask = 0xFF;		//Los puertos A y B son de 8 bits y la mascara mas grande que ocupa 8 bits es 0xFF
			maxbits = 8;		//Numero de bits que tienen los puertos A y B
			break;
		case 'D': case 'd':
			maxmask = 0xFFFF;	//El puerto D es de 16 bits y la mascara mas grande que ocupa 16 bits es 0xFFFF
			maxbits = 16;		//Numero de bits que tiene el puerto D
			break;
		default:
			break;				//Caso por defecto (nunca se deberia utilizar)
	}
	valid = ((mask <= maxmask) ? TRUE : FALSE);		//Verifico que la mascara sea menor o igual que maxmask. Valid es FALSE si esto no se cumple
	if (valid == FALSE){
		printf ("Error: La mascara ingresada excede el maximo de bits permitido para el puerto especificado (%d bits).\n", maxbits);
		printf ("Nota: La mascara mas grande que puede definir para el puerto %c es 0x%X.\n", port, maxmask);
	}
	if (mask < 0){				//Por ultimo, si la mascara es negativa, esto es un error
		printf ("La mascara no puede ser negativa.\n");
		valid = FALSE;			//Y se fuerza valid a ser FALSE
	}
	return valid;				//Devuelvo la validez
}

/*Funciones pedidas: bitSet, bitClr, bitToggle, bitGet, maskOn, maskOff y maskToggle*/

//Funcion para encender un bit. Recibe el puerto y el bit. Devuelve TRUE si hubo un error o FALSE si no lo hubo
static BOOLEAN bitSet (char port, int data){
	BOOLEAN error = FALSE;											//Variable para almacenar si hay error
//VERIFICACION DE ENTRADA
	if (is_a_valid_port(port) == FALSE){							//Veo si el identificador del puerto es valido
		error = TRUE;												//Si no lo es, hay un error
	}
	else if (is_a_valid_bit(port,data) == FALSE){					//Luego veo si el numero de bit que se provee es un bit valido
		error = TRUE;												//Indico que hubo un error
	}																//Si el puerto no es valido no tiene sentido ver si el bit lo es. Por eso el else if
//OPERACION BITSET
	else{		//Aqui es donde realmente ocurre el seteo pedido. Solo se llega a este caso si los anteriores, que son solo comprobacion, no generaron error
		int offset = 0;												//Genero un offset para la mascara que va a valer 8 para portA y 0 para los otros
		if ((port == 'A') || (port == 'a')){						//Asigno el offset
			offset = 8;
		}
		uint16_t msk = 1;											//Creo una mascara con solo un 1
		msk = msk << (data + offset);								//Shifteo la mascara al bit pedido
		p.portD.W = p.portD.W | msk;								//Y realizo un OR bitwise solo poniendo un uno en el bit que quiero encender
	}
	return error;													//Devuelvo si hubo un error
}																	//POR FAVOR VER LA NOTA AL FINAL DE ESTE ARCHIVO

//Funcion para apagar un bit. Recibe el puerto y el bit. Devuelve TRUE si hubo un error o FALSE si no lo hubo
static BOOLEAN bitClear (char port, int data){
	BOOLEAN error = FALSE;											//Variable para almacenar si hay error
//VERIFICACION DE ENTRADA
	if (is_a_valid_port(port) == FALSE){							//Veo si el identificador del puerto es valido
		error = TRUE;												//Si no lo es, hay un error
	}
	else if (is_a_valid_bit(port,data) == FALSE){					//Luego veo si el numero de bit que se provee es un bit valido
		error = TRUE;												//Indico que hubo un error
	}																//Si el puerto no es valido no tiene sentido ver si el bit lo es. Por eso el else if
//OPERACION BITCLEAR
	else{		//Aqui es donde realmente ocurre el borrado pedido. Solo se llega a este caso si los anteriores, que son solo comprobacion, no generaron error
		int offset = 0;												//Genero un offset para la mascara que va a valer 8 para portA y 0 para los otros
		if ((port == 'A') || (port == 'a')){						//Asigno el offset
			offset = 8;
		}
		uint16_t msk = 0xFFFE;										//Creo una mascara con todos 1s y solo un cero al final
		for (unsigned int i = 0; i < (data + offset); i++){			//Shiftear un cero es mas dificil que shiftear unos porque se ingresan ceros por la derecha
			msk = msk << 1;											//Entonces con un ciclo for shifteo de a una posicion hasta llegar a la posicion pedida
			p.b0 = 1;												//Y uso las operaciones de struct para ir rellenando con unos cada vez que se shiftea
		}
		p.portD.W = p.portD.W & msk;								//Luego realizo un AND bitwise solo poniendo el cero en el bit que quiero apagar
	}
	return error;													//Devuelvo si hubo un error
}																	//POR FAVOR VER LA NOTA AL FINAL DE ESTE ARCHIVO

//Funcion para conmutar un bit. Recibe el puerto y el bit. Devuelve TRUE si hubo un error o FALSE si no lo hubo
static BOOLEAN bitToggle (char port, int data){
	BOOLEAN error = FALSE;											//Variable para almacenar si hay error
//VERIFICACION DE ENTRADA
	if (is_a_valid_port(port) == FALSE){							//Veo si el identificador del puerto es valido
		error = TRUE;												//Si no lo es, hay un error
	}
	else if (is_a_valid_bit(port,data) == FALSE){					//Luego veo si el numero de bit que se provee es un bit valido
		error = TRUE;												//Indico que hubo un error
	}																//Si el puerto no es valido no tiene sentido ver si el bit lo es. Por eso el else if
//OPERACION BITTOGGLE
	else{		//Aqui es donde realmente ocurre la conmutacion pedida. Solo se llega a este caso si los anteriores, que son solo comprobacion, no generaron error
		int offset = 0;												//Genero un offset para la mascara que va a valer 8 para portA y 0 para los otros
		if ((port == 'A') || (port == 'a')){						//Asigno el offset
			offset = 8;
		}
		uint16_t msk = 1;											//Creo una mascara con solo un 1
		msk = msk << (data + offset);								//Shifteo la mascara al bit pedido
		p.portD.W = p.portD.W ^ msk;								//Y realizo un XOR bitwise conmutando solo el bit pedido
	}	//Para entender esta operacion es util recalcar que la compuerta XOR puede ser vista como un negador controlado de una entrada cuando la otra se pone en 1
	return error;													//Devuelvo si hubo un error
}																	//POR FAVOR VER LA NOTA AL FINAL DE ESTE ARCHIVO

/*
static BOOLEAN bitGet (char port, int data){
}
*/

//Funcion para encender todos los bits en estado alto de una mascara. Recibe el puerto y la mascara. Devuelve TRUE si hubo un error o FALSE si no lo hubo
static BOOLEAN maskOn (char port, int data){
	BOOLEAN error = FALSE;											//Variable para almacenar si hay error
//VERIFICACION DE ENTRADA
	if (is_a_valid_port(port) == FALSE){							//Veo si el identificador del puerto es valido
		error = TRUE;												//Si no lo es, hay un error
	}
	else if (is_a_valid_mask(port,data) == FALSE){					//Luego veo si la mascara es correcta, osea, si tiene sentido para la cantidad de bits del puerto
		error = TRUE;												//Indico que hubo un error
	}																//Si el puerto no es valido no tiene sentido ver si la mascara lo es. Por eso el else if
//OPERACION MASKON
	else{		//Aqui es donde realmente ocurre el seteo pedido. Solo se llega a este caso si los anteriores, que son solo comprobacion, no generaron error
	uint8_t msk8 = data;	//Transformo la mascara recibida a uint8_t para poder trabajar con los puertos A y B
	uint16_t msk16 = data;	//Transformo la mascara recibida a uint16_t para poder trabajar con el puerto D
		switch (port){
			case 'A': case 'a':
				p.portA_byte.B = p.portA_byte.B | msk8;				//Aplico OR bitwise entre todo el byte del puerto y la mascara
				break;
			case 'B': case 'b':
				p.portB_byte.B = p.portB_byte.B | msk8;				//Aplico OR bitwise entre todo el byte del puerto y la mascara
				break;
			case 'D': case 'd':
				p.portD.W = p.portD.W | msk16;						//Aplico OR bitwise entre todo el word del puerto y la mascara
				break;
			default:
				break;		
		}		
	}
	return error;													//Devuelvo si hubo un error
}
/*
static BOOLEAN maskOff (char port, int data){
}
*/

/*
static BOOLEAN maskToggle (char port, int data){
}
*/

/*NOTA IMPORTANTE PARA EL PROFESOR:
Es verdad, la forma en la que el struct esta definido incluye operaciones bit a bit, haciendo p.bX, o p.portD_[low/high]_bit.bX, o directamente
p.port[A/B]_bit.bX; pero la razon real por la cual hacemos operaciones bit a bit utilizando mascaras y no utilizando todo el potencial que el struct que
definimos ofrece, es por eficiencia y tamaño del codigo. Si bien en un programa para correr en un compilador es necesario hacer funciones que verifiquen
que la entrada que dio el usuario sea correcta, cosa que si tuvieramos que correr el programa en un microcontrolador probablemente no se necesitaria en
ciertos casos, ya que la entrada es mas limitada; lo que no se puede suprimir a la hora de cargar el programa en un microcontrolador real son las funciones
que hacen que el programa haga lo pedido, y la eficiencia del codigo al correrlo en un microcontrolador, donde los recursos son limitados, puede ser importante.
Como las macros se resuelven en tiempo de compilacion, no es posible crear una macro parametrizada que se le de como entrada el numero de bit deseado y que
"construya" la linea de codigo necesaria para operarlo, por lo que hay dos posibles soluciones para el problema de poder operar sobre cada uno de los 16 bits
del puerto D y sobre cada uno de los 8 bits de los puertos A y B:
1_ Escribir switches con 32 case en total anidados dentro de condicionales if, else if y else; lo que genera muchisimas operaciones de branch a nivel assembly,
y hace que el codigo sea larguisimo y terriblemente ineficiente. Pro: se podria utilizar todo el poder del struct definido
2_ Minimizar las decisiones que el microcontrolador debe tomar, mejorando la eficiencia y el uso de memoria, utilizando operaciones bitwise.
Contra: se utiliza poco de todo el poder del struct definido.
Basado en esto, y dado que el target que supone el ejercicio es un microcontrolador, priorizamos eficiencia frente a la simpleza de poner muchos switch case
y encender o apagar bits utilizando las operaciones que provee el struct.
Ahora bien, cabe preguntarse, "por que definieron un struct con tantas formas de utilizacion para usar una o dos? Por la misma razon que incluimos add_operation.
Al ser una libreria quisimos que sea facilmente actualizable con nuevas funciones, nuevos usos. Esta modularidad heredada del TP8 tiene muchisimo sentido al
considerar que queremos hacer una libreria para manejo de puertos en lugar de un simple programa que haga algo puntual. Pensando en esto, si quisieramos implementar
una nueva funcion especifica que haga uso de ciertos bytes, bits, o partes puntuales de un puerto, hacer una mascara es, como poco, engorroso. Es por esto que
decidimos ofrecer mas soporte a la hora de crear nuevas funciones para esta libreria, poniendo a disposicion herramientas para cualquier desarrollo.
Si, es verdad, es un TP, no el firmware de un microcontrolador para un proyecto que debe ser mantenido, pero si el struct definido ocupa la misma memoria que un
bitfield de 16 members, por que no agregar mas usos que idealmente le den soporte a cualquier desarrollo?
*/
 
