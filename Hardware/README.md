<h1>Designer's notes for Hardware development</h1>
<h2>USB C power supply current capability</h2>
The capability of each power supply can be determined by reading analog voltages on pins CC1 and CC2 connected to voltage dividers.

If the USB C standard in the cable and power adapter in use is properly implemented, one of the CC pins should always read 0V and the second one should be on one of the following voltage levels:
<ul>
  <li><strong>0,42V</strong> - legcy USB (1000mA most of the times)</li>
  <li><strong>0,94V</strong> - 1500mA</li>
  <li><strong>1,68V</strong> - 3000mA</li>
</ul>
The order of CC pins (e.g. if CC1 is 0V and CC2 is one of the three voltages or vice versa) is determined by the orientation of the cable and does not matter in our application.


<h2>To do list for next HW revision</h2>
<ul>
  <li>Zener diodes for power rails protection</li>
  <li>multi board wide power connector for testing</li>
  <li>add I2C header if possible</li>
  <li>buzzer pin spacing too wide</li>
  <li>Touch connector to JST, possibly without ground</li>
  <li>Fotorezistory - jeden na prostředek před dvojtečokou kolmo z desky, druhej ve stejné výčce</li>
  <li>lišta 240 mm</li>
  <li>díry 4 dolů a dvě mezi osmičky</li>
  <li>konektor na ws pásek k hraně</li>
  <li>reset possibly šroubovákem</li>
  <li>smdčka u segmentů bokem</li>

</ul>

<h2>To do list for next (H02) HW revision</h2>
<ul>
  <li>Add JST-XH connectors for the photoresistor in the back and backlight LED strip.</li>
  <li>Change touchbar graphics</li>
  <li>Lower supercapacitor resistor value</li>
  <li>Add 100k resistors in series between CC and Sensor V pins</li>
  <li>Maybye move the temperature sensor to the bottom</li>
  <li>Add LPF to photoresistor inputs</li>
  <li>Bigger Vedatori logo on the bottom, change to silk layer instead of copper.</li>
</ul>