/*
 * \file		main.c
 * \brief		snippets library for directory
 * \author		squad
 * \version		Ver 1.0
 * \date		2026-07-01
 * \copyright	Copyright 2026 squad
 * \license		This library is released under the MIT license.
 */

#include "libdir.h"

#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

#include "libfile.h"

int isDir(char *path)
{
	struct stat dirStat;
	if(stat(path, &dirStat) != 0) return -1;
	return S_ISDIR(dirStat.st_mode);
}

int mkdir_rec(char *path)
{
	int ret = -1;

cont:
	mkdir(path);

	DIR *bufHandle = opendir(path);

	if(bufHandle){
		//NOP
	}else if(errno == ENOENT){

		char *last_pos = strrchr(path, '\\');
		if(last_pos == NULL){
			ret = -2;
			goto err0;
		}

		char *path_buf = alloca(last_pos - path + 1);
		memset(path_buf, 0, last_pos - path + 1);
		memcpy(path_buf, path, last_pos - path);

		if(mkdir_rec(path_buf) != 0){
			ret = -3;
			goto err0;
		}

		goto cont;

	}else{
		goto err0;
	}


	ret = 0;
	closedir(bufHandle);
err0:
	return ret;
}

int dcopy(char *dst, char *src)
{
	int ret = -1;

	mkdir_rec(dst);

	//dir
	DIR *dirHandle;
	if((dirHandle = opendir(src)) == NULL) goto err0;

	struct dirent *dirStr;
	while((dirStr = readdir(dirHandle)) != NULL){
		if(!((strstr(dirStr->d_name, ".") - dirStr->d_name) == 0 && dirStr->d_namlen == 1) &&
			!((strstr(dirStr->d_name, "..") - dirStr->d_name) == 0 && dirStr->d_namlen == 2)){

			printf_s("dir: %s\n", dirStr->d_name, dirStr->d_namlen);
			char *src_path_buf = alloca(strlen(src)  + 1 + dirStr->d_namlen + 1);
			memset(src_path_buf, 0, strlen(src) + 1 + dirStr->d_namlen + 1);
			memcpy(src_path_buf, src, strlen(src));
			memcpy(src_path_buf + strlen(src), "\\", 1);
			memcpy(src_path_buf + strlen(src) + 1, dirStr->d_name, dirStr->d_namlen);

			char *dst_path_buf = alloca(strlen(dst)  + 1 + dirStr->d_namlen + 1);
			memset(dst_path_buf, 0, strlen(dst) + 1 + dirStr->d_namlen + 1);
			memcpy(dst_path_buf, dst, strlen(dst));
			memcpy(dst_path_buf + strlen(dst), "\\", 1);
			memcpy(dst_path_buf + strlen(dst) + 1, dirStr->d_name, dirStr->d_namlen);

			int rett = 0;

			if((rett = isDir(src_path_buf)) < 0){
				ret = -2;
				goto err1;
			}

			if(rett == 1 || dcopy(dst_path_buf, src_path_buf) != 0){
				ret = -3;
				goto err1;
			}

			if((rett = isFile(src_path_buf)) < 0){
				ret = -4;
				goto err1;
			}

			if(rett == 1) if(fcopy(dst_path_buf, src_path_buf) != 0){
				ret = -5;
				goto err1;
			}
		}
	}

	ret = 0;
err1:
	closedir(dirHandle);
err0:
	return ret;
}

