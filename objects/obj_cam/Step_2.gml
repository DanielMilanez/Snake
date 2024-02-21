var _camx = camera_get_view_x(view_camera[0]);
var _camy = camera_get_view_y(view_camera[0]);
var _camh = camera_get_view_height(view_camera[0]);
var _camw = camera_get_view_width(view_camera[0]);

var _shake = power(shake_value, 2) * shake_power;
_camx += random_range(-_shake, _shake);
_camy += random_range(-_shake, _shake);


camera_set_view_angle(view_camera[0], random_range(-_shake, _shake)* .5);