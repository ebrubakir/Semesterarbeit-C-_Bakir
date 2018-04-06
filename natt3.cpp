//ANFANG
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

#include "natt3.h"

int ClattToken::getAttList(
char *in,
ClElement *element){
char puffer[200];
int zaehler;
enum attzustand { zwischenTags, inNamen, erwarteAttributNamen, erwarteAttributWert, verarbeiteAttributWert} ;
enum attzustand zustand;
for (zaehler=0,zustand=inNamen,anzahlAtt=0;*in!='\0';
     in = in + 1) {
switch(*in) {
case ' ':
if (zustand == inNamen) {
zustand = erwarteAttributNamen;
*in='\0';
zaehler=0; }
else if (zustand == verarbeiteAttributWert) {
puffer[zaehler] = *in;
zaehler++; }

break;

case '=':
if (zustand == erwarteAttributNamen) {
zustand = erwarteAttributWert;
puffer[zaehler] = '\0';
if (element->attributeIstErlaubt(puffer)<0)
cout << endl << " Folgendes " << puffer << " ist hier nicht erlaubt" << endl;
attName[anzahlAtt] = new char[zaehler+1];
strcpy(attName[anzahlAtt],puffer);
zaehler=0; }
else if (zustand == verarbeiteAttributWert) {
puffer[zaehler] = *in;
zaehler++; }
else cout << "Fehlerhaftes Zeichen! '='" << endl;

break;

case '"':
if (zustand == erwarteAttributWert) {
zustand = verarbeiteAttributWert;
zaehler = 0; }
else if (zustand == verarbeiteAttributWert) {
zustand = erwarteAttributNamen;
puffer[zaehler] = '\0';
attValue[anzahlAtt] = new char[zaehler+1];
strcpy(attValue[anzahlAtt],puffer);
zaehler=0;
anzahlAtt++; }
else cout << "Fehlerhaftes Zeichen! '\"'" << endl;

break;

default:
if (zustand >= erwarteAttributNamen) {
puffer[zaehler] = *in;
zaehler++; }

break; } }

return 1; }

//ENDE
