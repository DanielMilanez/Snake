// Evento Draw do obj_snake
if (object_exists(obj_snake)){
	draw_set_color(make_color_rgb(224,248,207));
	var fontSize = 10;
	draw_set_font(fnt_score);

	// Definindo as coordenadas de desenho no centro da tela no eixo X
	var draw_x = room_width / 2;
	draw_text(draw_x, 5, global.pontos); // Desenha o texto no centro da tela no eixo X
}
