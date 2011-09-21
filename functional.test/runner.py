#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os, sys, subprocess

dir = os.path.dirname(sys.argv[0])

files = os.listdir(dir)
cppfiles = filter(lambda f: f.endswith('.cpp'), files)

failure_count = 0;

for f in sorted(cppfiles):
	status = subprocess.call([sys.argv[1], f])
	if status != 0:
		print("%s: failed" % f)
		failure_count = failure_count + 1;

sys.exit(failure_count)
