#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os, sys, subprocess

dir = os.path.dirname(sys.argv[0])

files = os.listdir(dir)
cppfiles = list(filter(lambda f: f.endswith('.cpp'), files))

failure_count = 0;

for f in sorted(cppfiles):
	p = subprocess.Popen([sys.argv[1], dir + '/' + f], 
		stdout = open('/dev/null'), stderr = subprocess.PIPE)
	# Why binary string returned from subprocess.PIPE?
	output = [l.decode('latin1') for l in p.stderr.readlines()]
	try:
		expected = open(dir + '/' + f.replace('.cpp', '.out')).readlines()
	except IOError:
		expected = []
	if output != expected:
		failure_count = failure_count + 1;
		print("%s: failed" % f)
		print("output:")
		for o in output:
			print(o.rstrip())
		print("expected:")
		for o in expected:
			print(o.rstrip())

print("Done %u tests with %u errors" % (len(cppfiles), failure_count))
sys.exit(failure_count)
