#!/usr/bin/python3
import os, sys

with open("main.cpp", "w+") as outfile:
	outfile.write('#include<bits/stdc++.h>\n')
	for name in sys.argv[1:]:
		with open(name, 'r') as file:
			outfile.write('\n'.join(('', '/'*20, f'//{name}', '/'*20, '', file.read(), '')))
