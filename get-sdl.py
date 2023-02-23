import wget
from zipfile import ZipFile
import os
import sys

sdl_version = '2.26.2'
sdl_name = 'SDL2-' + sdl_version + '.zip'
url = 'https://github.com/libsdl-org/SDL/releases/download/release-' + sdl_version + '/' + sdl_name

#sdl_mixer_version = '2.6.3'
#sdl_mixer_name = 'SDL_mixer-' + sdl_mixer_version + '.zip'
#sdl_mixer_url = 'https://github.com/libsdl-org/SDL_mixer/releases/download/release-' + sdl_mixer_version + sdl_mixer_name

def main():
	global sdl_version

	if(len(sys.argv) > 1 and isinstance(sys.argv[1], str)):
		sdl_version = sys.argv[1]

	# download SDL
	print('downloading SDL ' + sdl_version)
	wget.download(url)

	# loading and creating a zip object
	print('\n\nunzip ' + sdl_name)
	with ZipFile(sdl_name, 'r') as zObject:
		zObject.extractall()

	
if __name__ == "__main__":
	main()