# PowerPlug
  Projeto para criação de uma extenssão, usando arduino, para tomada que é controlada pela rede sem fio. [Site auxiliar](https://github.com/NascimentoLucas/SiteTomadaArduino).
  
# Materiais  
  - Arduino Uno.
  - Uma placa de rede ESP8266.
  - Módulo rele 1 Canal.

# ESP8266
  Como alternativa para a comunicação em rede, foi implementado um webserver. Para implementar foi necessário [configurar](https://blogmasterwalkershop.com.br/embarcados/esp8266/upgrade-de-firmware-do-wifi-esp8266-esp-01-atraves-do-arduino-e-conversor-usb-serial/) a memória flash do módulo. 
  Além disso foi usado um adaptador para facilitar a implementação, porém é possível usar sem.

# Configuração
  É necessário configurar a conexão na Classe DataSecurityObject, nela contem exemplos.
  
# Pinagem no Arduino
- Módulo rele:
  - VCC -> 5V
  - GND -> GROUND
  - IN -> 8
  
- Esp8266 com adaptador:  
  - GND -> GROUND
  - VCC -> 5V
  - TX -> 6
  - RX -> 7
  
# Referência
- [Configuração ESP8266](https://blogmasterwalkershop.com.br/arduino/como-usar-com-arduino-modulo-wifi-esp8266-esp-01)
