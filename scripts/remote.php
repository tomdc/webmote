<?php

include "config.php";

#
## Sendir function
function sendir($ip, $port, $ircommand, $repeat = 1) {
  for ($x = 0; $x < $repeat; $x++) {
    echo "Command: echo $ircommand| nc $ip $port<br>";
    exec("echo $ircommand | nc $ip $port");
    usleep(50000);
  }
}

# Get params
$device=$_GET["device"];
$action=$_GET["action"];

# Debug echo
echo "<h2>DEVICE: $device ACTION: $action</h2>";

# Get command to send to arduino
$command=$ircommand[$device][$action];

# If vol commands for sony, do it multiple times
if ( $device == 'sony' and preg_match('/vol/', $action) ) {
  sendir($arduino_ip, $arduino_port, $command, 3);
} else {
  sendir($arduino_ip, $arduino_port, $command);
}

# Return to webmote
header("Location:/webmote.html");


?>
