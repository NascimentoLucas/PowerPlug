var powerPlug = false;
var buttonTurnPowerPlug;
function start(){
	console.log("start");
	buttonTurnPowerPlug = document.getElementById("buttonTurn");
	buttonTurnPowerPlug.addEventListener("click", ChangeState);
	//ChangeNameState(buttonTurnPowerPlug);
}

function ChangeState(){
	if(powerPlug){
		//todo turn of
		console.log("off");
		powerPlug = false;
	}
	else{
		//todo turn on
		console.log("on");
		powerPlug = true;
	}
	ChangeNameState(buttonTurnPowerPlug);
}

function ChangeNameState(button){
	if(powerPlug){
		button.innerText = "Turn Off";
	}
	else{
		button.innerText = "Turn On";
	}
}

window.onload = start;