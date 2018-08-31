import sys
import json
import io
import re

#data_buffers
layers = {}

prevLayer = ''
prevType = ''
prevZheight = 0 
prevFeed = 0

#test gcode

#handle arguments
print(sys.argv[1])
print(sys.argv[2])

#strip the gcode to its bare coordinates 
def gcodeToCoord(gcodeline):
	global prevZheight
	gcodeline = gcodeline.strip()
	#find z or add it if its missing
	z = re.findall(r'[Z].?\d+.\d+', gcodeline)
	if z:
		prevZheight = z
	if not z: 
		gcodeline = gcodeline + " Z" + str(prevZheight)
	#extract X, Y and Z
	coord = re.findall(r'[XYZ].?\d+.\d+', gcodeline)
	return coord 
def cleanType(line):
	line = line.replace(';TYPE:', '')
	return line
#keep track of layerCount, operations and gcode

def main():
	#handle human and file
	print(sys.argv[1], 'loaded')
	print('sorting gcode and cleaning coordinates')
	inputfile = sys.argv[1]
	outputfile = sys.argv[2]
	gcode = open(inputfile, 'r')
	gcode = gcode.readlines()

	#empty global variables 
	prevZheight = 0

	
	layerIndex = 0 
	typesIndex = 0
	firstLayerfound = False
	gcodeBuffer = []
	typesBuffer = {}

	#loop trough gcode and rebuild it
	for line in gcode: 
		line = line.strip()
		if ';LAYER:' in line:
			if layerIndex > 1:
				key = 'LAYER: '+ str(layerIndex-1)
				layers[key] = typesBuffer
				typesBuffer = {}
				layerIndex += 1
			else: 
				layerIndex += 1
		if ';TYPE:' in line:
			if typesIndex > 1:
				key1 = str(typesIndex) + ': ' + cleanType(line)
				typesBuffer[key1] = 'gcodeBuffer'
				typesIndex += 1
				gcodeBuffer = []
			else: 
				typesBuffer[cleanType(line)] = 'gcodeBuffer'
				typesIndex += 1
				gcodeBuffer = []
		if 'G0' in line or 'G1' in line:
			#print('gcode')
			if firstLayerfound:
				gcodeBuffer.append(gcodeToCoord(line))

	#make json and output file
	f1 = open(outputfile, 'w')
	something = json.dumps(layers,indent=5, sort_keys=False)
	f1.write(something)
	f1.close()

if __name__ == '__main__':
#loop trough all lines in file
	main()