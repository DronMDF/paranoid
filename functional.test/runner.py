#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os, sys, subprocess

dir = os.path.dirname(sys.argv[0])

files = os.listdir(dir)
cppfiles = filter(lambda f: f.endswith('.cpp'), files)

failure_count = 0;

for f in sorted(cppfiles):
	p = subprocess.Popen([sys.argv[1], dir + '/' + f], 
		stdout = subprocess.PIPE, stderr = open('/dev/null'))
	output = p.stdout.readlines()
	expected = open(dir + '/' + f.replace('.cpp', '.out')).readlines()
	if p.wait() != 0 or output != expected:
		failure_count = failure_count + 1;
		print("%s: failed" % f)
		for o in output:
			print(o)

sys.exit(failure_count)
