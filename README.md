# Webmote

POC for a DIY IR Remote Control Hub using an arduino with the ethernet shield.

Lots of improvements possible, including:
  - send the IR code directly to the arduino instead of evaluating some other code
  - the above also to prevent changes are needed in 3 files
  - use a server side framework to get rid of the extra script
  - interface 
  - a complete rewrite? :)

## Arduino

The arduino used is an Etherten, an Arduino with ethernet shield onboard.
Load the webir.ino sketch, make sure to configure an IP address.

## IR

I use 2 IR leds atm connected to port 3 of the Etherten via a 2N2222A transistor.
(Both LEDs are connected in parallel between the +5V supply and the collector of the transistor)
The IR lib documentation mentions other options to connect multiple LEDs (using a combo of PNP and NPN transistors, but this seems to work fine too.

## Interface

Extremely basic bootstrap page.
The buttons call a function that just passes on the info to a PHP page.

Update config.php with the correct arduino ip.

## Reminder

This is a POC :)
