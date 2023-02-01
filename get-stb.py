import wget
from zipfile import ZipFile
import os
import sys

url = 'https://github.com/nothings/stb/archive/refs/heads/master.zip'
stb_name = 'stb-master.zip'


def main():

	# download last STB version
	print('downloading nothings/stb')
	wget.download(url)

	# loading and creating a zip object
	print('\n\nunzip ' + stb_name)
	with ZipFile(stb_name, 'r') as zObject:
		zObject.extractall()

	
if __name__ == "__main__":
	main()