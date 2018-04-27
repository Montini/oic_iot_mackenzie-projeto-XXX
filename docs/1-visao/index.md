# Documento de Visão do Projeto "CHOVE MAS NÃO MOLHA"

Este documento apresenta uma solução de software e hardware para o projeto *"CHOVE MAS NÃO MOLHA"*, 
apresentando os problemas a serem solucionados, as necessidades dos principais envolvidos, o alcance do projeto e as funcionalidades esperadas.

## Objetivos

* Estabelecer comunicação entre Arduino e Raspberry Pi via Firmata (Unidade 1). 
* Conectar um sensor de chuva à Unidade 1.
* Conectar um servo à um módulo NodeMCU (Unidade 2).
* Enviar dados a partir da Unidade 1 para a Unidade 2, utilizando um broker MQTT e Node-Red.
* Acionar o Servo (remotamente) na Unidade 2, na presença/detecção de chuva na Unidade 1.

## Problema

* Descrição do problema: Consequências negativas geradas pela falta de monitoramento em tempo real, sob efeito do grande volume de chuvas.
* Quem é afetado pelo problema: Pessoas, imóveis, comerciantes, indústrias, agro-negócio.
* Impacto no negócio: Agilidade na tomada de decisões decorrentes da chuva.
* Benefícios de uma boa solução: A prevenção de efeitos negativos causados pela chuva.

## Definições, abreviações e outros termos do domínio do problema

* Unidade 1: É composta de 1 Arduino, 1 Raspberry Pi, 1 Sensor de chuva.
* Unidade 2: É composta de 1 NodeMCU, 1 Servo, 1 PaperSignal
* PaperSignal: Dobradura em papel em formato de guarda-chuva.

## Integração com outros sistemas

* Amazon AWS IoT.
 
## Interessados

* Indivíduos e setores que desejam monitorar em tempo real a presença de chuva em locais remotos.

## Usuários

* Pessoas comuns.
* Estudantes.
* Hobistas. 
* Empresas.
* Agro negócio.

## Funcionalidades do produto

* Monitoramento remoto da presença de chuva, via soluções MQTT.
* Acionamento de servo

## Restrições do projeto

* Ter acesso à internet.
* Cada unidade deve estar conectada a uma fonte de energia.
