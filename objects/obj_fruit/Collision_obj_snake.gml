audio_play_sound(snd_eat,1,0);
obj_snake.largura_corpo ++;
global.pontos ++;
instance_create_layer(0,0,"fruit",obj_fruit);
obj_cam.shake_value = 2;
instance_destroy(id);