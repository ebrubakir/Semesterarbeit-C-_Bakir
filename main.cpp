//ANFANG
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

#include "ntoken3.h"


ClElement *verarbeite(ifstream& datei);
enum ezustand {direktive, element, attribute, abhaengigElement,abhaengigAttribute, inID, noise};

int main() {
char file[200];
ifstream in;
ofstream out;
ClToken *token;
ClElement *jetzt=NULL, *wurzel;
char switchkowsky;

char zeichen;
char puffer[200];
int zaehler;

//MENUEFUEHRUNNG
cout <<"Menue"<< endl;

cout <<"Fuer die Funktion CONVERT DATA bitte (C) eingeben"<<endl;
cout<<"Fuer die Funktion HELP bitte (H) eingeben" <<endl;
cout<<"Achten Sie bei der in bitte darauf den Buchstaben in GROSS zu schreiben!";
cin >> switchkowsky;


switch(switchkowsky) {

case 'C':
cout <<"Konvertierfunktion wurde ausgewaehlt! "<<endl;

break;

case 'H':
cout << "Mit dieser Option koennen die die XML Datei und die TXT zusammen gefuehrt werden. Weiterleitung wird automatish gestartet." <<endl;

break;

default:

return switchkowsky;

break; }

//DTD

cout << "DTD-file: " << endl;
cin >> file;
in.open(file);
wurzel=verarbeite(in);
for (jetzt=wurzel;jetzt!=NULL;jetzt=jetzt->getNext())
    jetzt->druckeElement(0,wurzel);
in.close();
cout << "DTD Funktion" << endl;


//XML

cout << "XML-file:" << endl;
cin >> file;
in.open(file);
cout << "XML Funktion" << endl;


//in1

token=new ClToken;
if (token->getToken(in,NULL,wurzel)!=0) token->druckeToken(1);
in.close();

//TXT

cout << "TXT-file:" << endl;
cin >> file;
in.open(file);

ifstream text ("flug.txt");

ifstream doremi("fluege.xml", ios::binary);


ofstream txtoutput("Flugplan.xml", ios::app);
txtoutput << text.rdbuf();
ofstream abc("Flugplan.xml", ios::binary);
abc << doremi.rdbuf();
abc.close();

cout << text.rdbuf()<<endl;

}

//in2

ClElement *verarbeite(ifstream& datei) {
char zeichen, letztes;
char puffer[100];
int zaehler;
enum ezustand zustand = noise;
ClElement *jetzt=NULL, *wurzel=NULL, *neu;
for (datei.get(zeichen);!datei.eof();datei.get(zeichen)) {
switch(zeichen) {
case '<':
zustand=direktive;
zaehler=0;

break;

case '>':
if (letztes!=' ') {
puffer[zaehler]='\0';
switch(zustand) {
case abhaengigElement:
jetzt->addTag(puffer);

break;

case abhaengigAttribute:
jetzt->addAttribute(puffer);

break;

case element:
neu=new ClElement(puffer);
if (jetzt!=NULL) jetzt->setNext(neu);
else wurzel=neu;
jetzt=neu;
zustand=abhaengigElement;

break; } }

zustand=noise;

break;
case ' ':
if (letztes==' ') continue;
puffer[zaehler]='\0';
zaehler=0;
switch(zustand) {
case direktive:
if (!strcmp(puffer,"!ELEMENT")) zustand=element;
else if (!strcmp(puffer,"!ATTLIST")) zustand=attribute;
else {
cout << endl << "Folgendes nicht verstanden: " << puffer;
zustand=noise; }

break;

case element:
neu=new ClElement(puffer);
if (jetzt!=NULL) jetzt->setNext(neu);
else wurzel=neu;
jetzt=neu;
zustand=abhaengigElement;

break;

case attribute:
if (wurzel==NULL) neu=NULL;
else neu=wurzel->sucheElement(puffer,wurzel);
if (neu==NULL) {
cout << endl << "Es gibt kein Element mit dem Namen: " << puffer << endl; zustand=noise; }
else {
zustand=abhaengigAttribute;
jetzt=neu; }

break;

case abhaengigElement:
jetzt->addTag(puffer);

break;

case abhaengigAttribute:
jetzt->addAttribute(puffer);

break; }

break;

default:
if (zustand!=noise) puffer[zaehler] = zeichen;
zaehler++;

break; }

letztes=zeichen; }
return wurzel;

}

//ENDE
