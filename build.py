#!/usr/bin/env python3.7

import glob
import os
import subprocess
from shutil import copyfile
import shutil
import sys

# Build code
def build_code():
    if os.path.isdir('bin'):
        shutil.rmtree('bin')
    os.makedirs('bin')

    cc = '/usr/local/djgpp/bin/i586-pc-msdosdjgpp-g++'

    cargs = ['-I/usr/local/djgpp/i586-pc-msdosdjgpp/sys-include']
    libs = ['-L/usr/local/djgpp/i586-pc-msdosdjgpp/lib/','-lm']
    output = ['-o', 'bin/aoc.exe']
    files = glob.glob('src/**/*.c', recursive=True)

    args = [cc, *cargs, *files, *output, *libs ]

    subprocess.call(args)

def build_execute():
    args = ['dosbox',
        '-conf','./dosbox.config',
        '-c' ,'d:',
        '-c', 'aoc.exe']

    subprocess.call(args)

for el in sys.argv:
    if el == 'build':
        build_code()
    if el == 'content':
        build_images()
    if el == 'run':
        build_execute()
    if el == 'all':
        build_code()

print('done.')