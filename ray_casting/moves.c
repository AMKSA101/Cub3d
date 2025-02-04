#include "../Headers/cub3d.h"

int key_pres(int keycode, t_data *data)
{
	if (keycode == W)
		data->player->key_up= true;
	if (keycode == S)
		data->player->key_down = true;
	if (keycode == A)
		data->player->key_left = true;
	if (keycode == D)
		data->player->key_right = true;
	if (keycode == LEFT)
		data->player->left_rotate = true;
	if (keycode == RIGHT)
		data->player->right_rotate = true;
	if (keycode == SPACE)
		data->player->speed_rotate = true;
	return (0);
}

int key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->player->key_up= false;
	if (keycode == S)
		data->player->key_down = false;
	if (keycode == A)
		data->player->key_left = false;
	if (keycode == D)
		data->player->key_right = false;
	if (keycode == LEFT)
		data->player->left_rotate = false;
	if (keycode == RIGHT)
		data->player->right_rotate = false;
	if (keycode == SPACE)
		data->player->speed_rotate = false;
	return (0);
}


void move_player(t_scene *img, t_player *player)
{
	int speed = 1;
	float angle_speed = 0.01;
	float cos_angle = cos(player->angle);
	float sin_angle = sin(player->angle);
	if (player->left_rotate)
		player->angle += angle_speed;
	if (player->right_rotate)
		player->angle -= angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	float new_x = player->x;
	float new_y = player->y;
	
	if (player->key_up) {
		new_x -= cos_angle * speed;
		new_y -= sin_angle * speed;
	}
	if (player->key_down) {
		new_x += cos_angle * speed;
		new_y += sin_angle * speed;
	}
	if (player->key_left) {
		new_x -= sin_angle * speed;
		new_y += cos_angle * speed;
	}
	if (player->key_right) {
		new_x += sin_angle * speed;
		new_y -= cos_angle * speed;
	}

	if (player->speed_rotate)
		player->speed = 0.5;
	if (!player->speed_rotate)
		player->speed = 0.2;
	if (!is_wall(img, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}