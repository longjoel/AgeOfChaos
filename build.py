#!/usr/bin/env python3.7

import glob
import os
import subprocess
from shutil import copyfile
import shutil
import sys
from PIL import Image

# Build code
def build_code():
    if os.path.isdir('bin'):
        shutil.rmtree('bin')
    os.makedirs('bin')
    os.makedirs('bin/scripts')
    os.makedirs('bin/images')

    cc = '/usr/local/djgpp/bin/i586-pc-msdosdjgpp-g++'

    cargs = ['-I/usr/local/djgpp/i586-pc-msdosdjgpp/sys-include']
    libs = ['-L/usr/local/djgpp/i586-pc-msdosdjgpp/lib/','-lm']
    output = ['-o', 'bin/aoc.exe']
    files = glob.glob('src/**/*.cpp', recursive=True)+glob.glob('src/**/*.c', recursive=True)

    args = [cc, *cargs, *files, *output, *libs ]

    subprocess.call(args)

    source = os.listdir("src/scripts/")
    destination = "bin/scripts/"
    for files in source:
        shutil.copy("src/scripts/"+files,destination)

def windows_to_unix(s):
    if os.name == 'nt':
        return s.replace('\\','/').replace(':','',1)
    return s


def build_docker():
    if os.path.isdir('bin'):
        shutil.rmtree('bin')
    os.makedirs('bin')
    os.makedirs('bin/scripts')
    os.makedirs('bin/images')

    dockerArgs=['run','--rm', '-it', '--volume='+os.getcwd()+'/:/workdir', 'gstolarz/djgpp']
    print(os.getcwd())
    cc = ['/usr/local/djgpp/bin/djgpp-g++']

    cargs = ['-I/usr/local/djgpp/i586-pc-msdosdjgpp/sys-include']
    libs = ['-L/usr/local/djgpp/i586-pc-msdosdjgpp/lib/','-lm']
    output = ['-o', 'bin/aoc.exe']
    files = map(windows_to_unix, glob.glob('src/**/*.cpp', recursive=True)+glob.glob('src/**/*.c', recursive=True))

    args = ['docker',*dockerArgs, *cc, *cargs, *files, *output, *libs ]

    print(' '.join(args))

    subprocess.call(args)

    source = os.listdir("src/scripts/")
    destination = "bin/scripts/"
    for files in source:
        shutil.copy("src/scripts/"+files,destination)

def build_execute():
    args = ['dosbox',
        '-conf','./dosbox.config',
        '-c' ,'d:',
        '-c', 'aoc.exe'
        ]

    subprocess.call(args)

def build_images():
    source = os.listdir("images/")
    destination = "bin/images/"
    for files in source:
        image = Image.open(os.path.join('images',files))
        image = image.convert('P', palette=Image.ADAPTIVE, colors=256)
        image.save(os.path.join('bin/images',os.path.splitext(files)[0]+".bmp"))


for el in sys.argv:
    if el == 'build':
        build_code()
        build_images()
    if el == 'build:docker':
        build_docker()
        build_images()
    if el == 'run':
        build_execute()
    if el == 'all':
        build_code()

print('done.')