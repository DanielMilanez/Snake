var _left, _right, _up, _down;

_left = keyboard_check_pressed(vk_left);
_right = keyboard_check_pressed(vk_right);
_up = keyboard_check_pressed(vk_up);
_down = keyboard_check_pressed(vk_down);


if (_right && dir_inicial != 2){
	dir_final = 0;
}
else if (_left && dir_inicial != 0){
	dir_final = 2;
}
else if (_up && dir_inicial != 3){
	dir_final = 1;
}
else if (_down && dir_inicial != 1){
	dir_final = 3;
}