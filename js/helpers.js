/**

Arduino helpers

*/


function sendir(device,action) {

  location.href = 'scripts/remote.php?device=' + device + '&action=' + action;
  console.log(device, action)
  

}

