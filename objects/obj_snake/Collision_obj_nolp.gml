global.andar = 0;
if (vezes >= 1){
	obj_cam.shake_value = 3;
	audio_play_sound(snd_death,1,0);
}
sprite_index = spr_snake_death;

vezes = 0;