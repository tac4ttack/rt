

float4						get_ray_cam(__local t_scene *scene, const uint2 pix)
{
	float4					cam_ray = 0;
	float					ratio = 1024 / 720;

	cam_ray.x = ((2 * ((pix.x + 0.5) / scene->win_w)) - 1) * ratio * (tan(radians(ACTIVECAM.fov / 2)));
	cam_ray.y = ((1 - (2 * ((pix.y + 0.5) / scene->win_h))) * tan(radians(ACTIVECAM.fov / 2)));
	cam_ray.z = 1;
	cam_ray = rotat_zyx(cam_ray, ACTIVECAM.pitch, ACTIVECAM.yaw, 0);
	return(fast_normalize(cam_ray));
}

/*
float4						old_get_ray_cam(const t_cam cam, const t_scene scene, const int x, const int y)
{
	float4					cam_ray = 0;
	float					ratio = (float)PARAM->win_w / (float)PARAM->win_h;

	cam_ray.x = ((2 * ((x + 0.5) / PARAM->win_w)) - 1) * ratio * (tan(radians(cam.fov / 2)));
	cam_ray.y = ((1 - (2 * ((y + 0.5) / PARAM->win_h))) * tan(radians(cam.fov / 2)));
	cam_ray.z = 1;
//  rotation XYZ
//	cam_ray.x = xx * cos(yaw) * cos(roll) + yy * cos(yaw) * -sin(roll) + sin(yaw);
//	cam_ray.y = xx * (-sin(pitch) * -sin(yaw) * cos(roll) + cos(pitch) * sin(roll)) + yy * (-sin(pitch) * -sin(yaw) * -sin(roll) + cos(pitch) * cos(roll)) + cos(yaw) * -sin(pitch);
//	cam_ray.z = xx * (cos(pitch) * -sin(yaw) * cos(roll) + sin(pitch) * sin(roll)) + yy * (cos(pitch) * -sin(yaw) * -sin(roll) + sin(pitch) * cos(roll)) + cos(yaw) * cos(pitch);
//
// rotation ZYX
//	cam_ray.x = xx * cos(roll) * cos(yaw) + yy * (cos(pitch) * -sin(roll) + cos(roll) * sin(yaw) * sin(pitch)) + (-sin(roll) * -sin(pitch) + cos(roll) * sin(yaw) * cos(pitch));
//	cam_ray.y = xx * sin(roll) * cos(yaw) + yy * (cos(roll) * cos(pitch) + sin(roll) * sin(yaw) * sin(pitch)) + (cos(roll) * -sin(pitch) + sin(roll) * sin(yaw) * cos(pitch));
//	cam_ray.z = xx * -sin(yaw) + yy * cos(yaw) * sin(pitch) + cos(yaw) * cos(pitch);
//	calcul simplifié
//	cam_ray.x = xx * cos(yaw) + yy * (sin(yaw) * sin(pitch)) + (sin(yaw) * cos(pitch));
//	cam_ray.y = yy * cos(pitch) + -sin(pitch);
//	cam_ray.z = xx * -sin(yaw) + yy * cos(yaw) * sin(pitch) + cos(yaw) * cos(pitch);
//
	cam_ray = rotat_zyx(cam_ray, cam.pitch, cam.yaw, 0);
	return(fast_normalize(cam_ray));
}
*/
