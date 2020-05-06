#include "TramaControl.h"
#include <stdio.h>

TramaControl::TramaControl()
{
   this->S = 22;
   this->C = 0;
   this->D = 'T';
   this->NT = '0';
}

void TramaControl:: setSincronismo(unsigned char S){
    this->S = S;
}

void TramaControl::  setDireccion(unsigned char D){
    this->D = D;
}

void TramaControl:: setControl(unsigned char C){
    this->C = C;
}

void TramaControl:: setNumeroTrama(unsigned char NT){
    this->NT = NT;
}

unsigned char TramaControl:: getSincronismo(){
    return this->S;
}

unsigned char TramaControl::  getDireccion(){
    return this->D;
}

unsigned char TramaControl:: getControl(){
    return this->C;
}

unsigned char TramaControl:: getNumeroTrama(){
    return this->NT;
}

TramaControl::~TramaControl()
{

}
