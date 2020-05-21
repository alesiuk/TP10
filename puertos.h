/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * Archivo:   puertos.h    
 * Autor: salta
 * Funcion: Emulacion de los puerto A,B y D; y contiene declaraciones de dichos puertos 
 * Created on 20 de mayo de 2020, 15:37
 */

#ifndef PUERTOS_H
#define PUERTOS_H

#include <stdio.h>
#include <stdlib.h>  
#include <stdint.h>  

/***********************Estrucuturas, Uniones *********************************/
typedef struct {                     //se crea una estrucutura con un alias llamado regbit_t, hace referencia a que 
        uint16_t b0   :1;                //podemos controlar el registro bit a bit.
        uint16_t b1   :1;                //Tiene un tamañp de 2 byte porque incluye al portA y portB, todo es el portD
        uint16_t b2   :1;
        uint16_t b3   :1;
        uint16_t b4   :1;
        uint16_t b5   :1;
        uint16_t b6   :1;
        uint16_t b7   :1;
        uint16_t b8   :1;
        uint16_t b9   :1;
        uint16_t b10   :1;
        uint16_t b11   :1;
        uint16_t b12   :1;
        uint16_t b13   :1;
        uint16_t b14   :1;
        uint16_t b15   :1;
    }regbit_t;   
    typedef struct{                     //se crea un estrucutra con un alias puertos_t que hace al portA y al portB.
        uint8_t low;                  //parte low (b0-b7)
        uint8_t high;                  //parte high(b8-b15)
    }puertos_t;
    typedef struct{                     //se crea una estrucutura com un alias registro_t , porque solo hace referencia al puerto D     
        uint16_t word;
    }registro_t;
    
    typedef union{                      //se crea una union para tener un control bit a bit, de puertos A,B y D al mismo tiempo.
        registro_t portD;
        puertos_t portB,portA;
        regbit_t bits;
    }regconjunto_u;

/***************************Prototipos*****************************************/

 void BitSet(char puerto,int bit);         //dado un puerto y el numero de bit,la funcion cambia el estado del bit a un 1
 void BitClr(char puerto,int bit);         //dado un puerto y el numero de bit,la funcion cambia el estado del bit a un 0
 int BitGet(char puerto,int bit);          //dado un puerto y el numero de bit,la funcion devuelve el estado del bit
 void BitToggle(char puerto,int bit);      //dado un puerto y el numero de bit,la funcion cambia el estado del bit por su opuesto
void MaskOn(char puerto,int mascara);      //dado un puerto y una mascara, la funcion debe prender todos los bit que esten prendidos en la mascara
 void MaskOff(char puerto,int mascara);     //dado un puerto y una mascara, la funcion debe apagar todos los bit que esten prndidos en la mascara
 void MaskToggle(char puerto,int mascara);  //dado un puerto y una mascara, la funcion debe cambiar por el opuesto todos los bit que esten prendidos en la mascara

/*******************************************************************************/

#endif /* PUERTOS_H */
