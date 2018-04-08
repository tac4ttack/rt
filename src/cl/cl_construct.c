
static bool			cl_create_base(t_cl *cl, int type)
{
	if ((cl->err = clGetPlatformIDs(1, &cl->platform_id, &cl->num_platforms)) \
																!= CL_SUCCESS)
		return (cl_builderrors(cl, 1, cl->err));
	if ((cl->err = clGetDeviceIDs(NULL, type, 1, &cl->device_id, NULL)) \
																!= CL_SUCCESS)
		return (cl_builderrors(cl, 1, cl->err));
	if (!(cl->context = clCreateContext(0, 1, \
			(const cl_device_id *)&cl->device_id, NULL, NULL, &cl->err)))
		return (cl_builderrors(cl, 2, cl->err));
	if (!(cl->queue = clCreateCommandQueue(cl->context, cl->device_id, \
															0, &cl->err)))
		return (cl_builderrors(cl, 3, cl->err));
	if (!(cl->program = clCreateProgramWithSource(cl->context, 1, \
							(const char **)&cl->kernel_src, NULL, &cl->err)))
		return (cl_builderrors(cl, 4, cl->err));
	(void)type;
	return (true);
}

static bool			cl_build(t_cl *cl)
{
	if ((cl->err = clBuildProgram(cl->program, 0, NULL, \
				"-Werror -I ./kernel/includes/ ", NULL, NULL)) != CL_SUCCESS)
		return (cl_builderrors(cl, 5, cl->err));
	if (!(cl->kernel = clCreateKernel(cl->program, "ray_trace", &cl->err)) \
										|| cl->err != CL_SUCCESS)
		return (cl_builderrors(cl, 6, cl->err));
	if ((cl->err = clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
						CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t),
									&cl->local_item_size, NULL)))
		return (cl_builderrors(cl, 0, cl->err));
	return (true);
}

t_cl				*cl_construct(const char *path, \
					const size_t width, const size_t height, int type)
{
	t_cl			*cl;
	cl_ulong		size;

	if (!(cl = ft_memalloc(sizeof(t_cl))))
		return (NULL);
	if (!(cl->kernel_src = (char *)ft_memalloc(MAX_SOURCE_SIZE)))
		return (cl_destruct(&cl));
	if (!cl_load_src(cl, path) ||
		!cl_create_base(cl, type) ||
		!cl_build(cl))
		return (NULL);
	cl->add_buffer = &cl_add_buffer;
	cl->compute = &cl_compute;
	cl->dimension[0] = width;
	cl->dimension[1] = height;
	clGetDeviceInfo(cl->device_id, CL_DEVICE_LOCAL_MEM_SIZE, \
					sizeof(cl_ulong), &size, 0);
	return (cl);
}
