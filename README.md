# BFW_MQTT

Das **BFW_MQTT**-Projekt ist ein pädagogisches IoT-Beispiel, das die Funktionsweise des MQTT-Protokolls und das Publisher-/Subscriber-Prinzip anschaulich demonstriert. 
Mithilfe zweier ESP8266 WiFi-Boards, die über einen MQTT-Broker kommunizieren, wird ein einfacher Schaltvorgang umgesetzt: 

Betätigt man einen Schalter auf einem der Boards, schaltet sich eine Lampe auf dem anderen Board ein – und umgekehrt. 

Das Projekt vermittelt die grundlegenden Konzepte der IoT-Kommunikation und zeigt, wie Geräte drahtlos miteinander interagieren können.

Dieses Projekt wurde von mir in Zusammenarbeit mit der **Klasse FIA 11** des **bfw-Leipzig** entwickelt. Ziel ist es, 
das Projekt der Dozentin **N.R** (genauer Name w.g Daten/Personenschutz nicht genannt) sowie dem **bfw-Leipzig** zur Verfügung zu stellen, 
damit es in späteren Klassen oder von anderen Lernenden weiterentwickelt und als Lehrmaterial genutzt werden kann. 
Das Projekt bietet eine solide Grundlage, um den Umgang mit IoT-Technologien besser zu verstehen und praktisch anzuwenden.


## Inhaltsverzeichnis

1. [Installation](#installation)
2. [Verwendung](#verwendung)
3. [Beitragende](#beitragende)
4. [Bekannte Probleme](#bekannte-probleme)
5. [Zukünftige Entwicklungen](#zukünftige-entwicklungen)
6. [Lizenz](#lizenz)

## Installation

*Platzhalter für Installationsanweisungen.*

## Verwendung

Dieses Projekt ist ideal für den Unterricht im Bereich **Internet der Dinge (IoT)** und dient als praktisches Beispiel 
für die Implementierung des MQTT-Protokolls. 

Es kann verwendet werden, um zu demonstrieren, wie zwei Geräte über ein Netzwerk kommunizieren und einfache Steuerungsprozesse realisieren. 
Eine detaillierte Anleitung zur Implementierung und Anwendung des Projekts ist in der begleitenden Dokumentation enthalten.


### Beispiel:

1. Schließen Sie die ESP8266-Boards entsprechend der im Repository bereitgestellten Schaltpläne an.
2. Stellen Sie sicher, dass die MQTT-Broker-Konfiguration korrekt eingerichtet ist.
3. Drücken Sie den Schalter auf dem ersten Board – die Lampe auf dem zweiten Board sollte sich daraufhin einschalten.

Dieses einfache Setup hilft, die Grundlagen der IoT-Kommunikation verständlich zu machen.

## Beitragende

Dieses Projekt wurde von mir gemeinsam mit der **Klasse FIA 11** am **bfw-Leipzig** entwickelt. Das Projekt wird der Dozentin **N.R** (genauer Name w.g Daten/Personenschutz nicht genannt) und dem **bfw-Leipzig** übergeben, 
um es in zukünftigen Klassen weiterzuentwickeln und als Lehrmaterial einzusetzen.

## Bekannte Probleme

Einige Herausforderungen beim Aufbau und der Konfiguration sind dokumentiert. 
Diese sind z.B. in den beigefügten **.png-Dateien** festgehalten, welche die Schaltungsstruktur und die Verbindungsprobleme erläutern. 
In der Dokumentation werden Lösungsvorschläge für diese Probleme ausgearbeitet.

## Zukünftige Entwicklungen

Geplante Erweiterungen des Projekts umfassen:
- Integration zusätzlicher Sensoren und Aktoren
- Erweiterung der Dokumentation, um neue Features und fortgeschrittene Anwendungsfälle zu beschreiben

Diese zukünftigen Entwicklungen sollen das Projekt robuster und vielseitiger machen, sodass es in unterschiedlichen Lehrkontexten eingesetzt werden kann.

## Quellen

Für die Entwicklung dieses Projekts wurden verschiedene Quellen unteranderem aus dem Internet herangezogen, um die Implementierung und die technischen Details zu unterstützen. Eine vollständige Liste der verwendeten Ressourcen wird in der Dokumentation hinzugefügt.
[Quellenverzeichnis](./sources.md)

## Lizenz

Dieses Projekt steht unter der **MIT-Lizenz**. Es ist darauf ausgelegt, von anderen Dozenten oder Lernenden weiterentwickelt und angepasst zu werden. 
Die Lizenz erlaubt es, den Quellcode frei zu verwenden, zu modifizieren und weiterzugeben, solange die ursprünglichen Urheber genannt werden.

---

*Hinweis: Dieses Repository enthält noch **nicht** alle notwendigen Dateien, um das Projekt nachzubauen, zu erweitern und in anderen Bildungszusammenhängen zu nutzen.*
