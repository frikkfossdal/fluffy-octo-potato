import sys
import json
import io
import re

#handle human and file 
print(sys.argv[1], 'loaded')
print('sorting gcode and cleaning coordinates')
inputfile = sys.argv[1]
outpulfile = sys.argv[2]
gcode = open(inputfile, 'r')
gcode = gcode.readlines() 

#data_buffers
layers = {}
typesIndex = {}
prevLayer = ''
prevType = ''
prevZheight = 0
prevFeed = 0

#data indexes 
layerIndex = 0
operationIndex = 0

#test gcode

#handle arguments
print(sys.argv[1])
print(sys.argv[2])

#strip the gcode to its bare coordinates 
def gcodeToCoord(gcodeline):
	gcodeline = gcodeline.strip()
	coord = re.findall(r'[XYZEF].?\d+.\d+', gcodeline)
	z = re.findall(r'[Z].?\d+.\d+', gcodeline)
	if z:
		prevZheight = z
		print('hello',prevZheight)
	#if not z: 
		#add prevZ to line 
def operationTracker(gcodeline): 
	if 'LAYER:' in gcodeline:
		layerIndex += 1

	if 'TYPE:' in gcodeline:
		typesIndex += 1

	if('G0' in gcodeline or 'G1' in gcodeline):
		gcodeToCoord(gcodeline)

#loop trough all lines in file
for line in gcode:
	operationTracker(line)