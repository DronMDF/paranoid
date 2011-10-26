#!/usr/bin/env python3

import os, sys, subprocess

TARGET = sys.argv[1]
SRCDIR = sys.argv[2]

# Environment:
# OBJDIR - object file directory
# CXX - c++ compiler
# CXXFLAGS - c++ compiler flags
# LD - linker
# LDFLAGS - linker flags

def depends(source, target):
	cmd = ' '.join([ os.environ['CXX'], os.environ['CXXFLAGS'], "-E -MM -MT", target, source ])
	result = subprocess.check_output(cmd.split()).decode('ascii')
	return result.replace(':', ' ').replace('\\', ' ').split()[1:]

def compile(object, source):
	pass

def ld(bundle, objects):
	pass

def buildObject(object, source):
	deps = depends(source, object)
	if os.path.isfile(object):
		object_time = os.stat(object).st_mtime
		if True not in map(lambda d: os.stat(d).st_mtime > object_time, deps):
			return 
	compile(object, source)

def buildBundle(bundle, sources):
	objects = map(lambda f: (f, f.replace('.cpp', '.o')), sources)
	for src, obj in objects:
		buildObject(obj, src)
	if os.path.isfile(bundle):
		bundle_time = os.stat(bundle).st_mtime
		if True not in map(lambda o: os.stat(o[1]).st_mtime > bundle_time, objects):
			return 
	ld(bundle, map(lambda o: o[2], objects))
	
def buildTarget(target, bundles):
	for bundle, sources in bundles:
		buildBundle(bundle, sources)
	if os.path.isfile(target):
		target_time = os.stat(target).st_mtime
		if True not in map(lambda b: os.stat(b[0]).st_mtime > bundle_time, bundles):
			return 
	ld(bundle, map(lambda o: o[2], objects))
	

# list of subdirs
#for root, dirs, files in os.walk(SRCDIR):
	# if cpp files in dir - this is bundled dir
#	cpps = list(filter(lambda f: f.endswith(".cpp"), files))
#	if cpps:
#		print (root, cpps)

print(depends(SRCDIR, TARGET))
