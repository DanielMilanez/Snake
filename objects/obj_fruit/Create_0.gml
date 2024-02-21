if (place_snapped(16,16)){
	move_random(16,16)
}

if (place_meeting(x,y,obj_nolp)){
	instance_create_layer(0,0,"fruit",obj_fruit);
	instance_destroy(id);
}

