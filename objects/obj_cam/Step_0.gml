shake_value = lerp(shake_value,0,.5);

if (global.morreu){
	show_message("Você morreu!");
	game_restart();
}