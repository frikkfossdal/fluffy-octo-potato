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
	totalNumJobs = 0
	totalNumLayers = 0
	firstLayerfound = False
	gcodeBuffer = []
	typesBuffer = {}
	typeKey = ''
	prevTypeKey = ''

	#loop trough gcode and rebuild it
	for line in gcode: 
		line = line.strip()
		if ';LAYER:' in line:
			if layerIndex > 0:
				key = 'LAYER: '+ str(layerIndex-1)
				layers[key] = typesBuffer
				typesBuffer = {}
				typesIndex = 0
				layerIndex += 1
			else: 
				layerIndex += 1
				typesIndex = 0
				typesBuffer = {}
				firstLayerfound = True
			totalNumLayers += 1
		#build new type element
		if ';TYPE:' in line:
			typeKey = str(typesIndex) + ': ' + cleanType(line) 
			if typesIndex > 0:
				#add gcode buffer to previous type
				typesBuffer[prevTypeKey] = gcodeBuffer
			gcodeBuffer = []
			typesIndex += 1
			prevTypeKey = typeKey
			totalNumJobs += 1

		#add coordinates to current type
		if 'G0' in line or 'G1' in line:
			#print('gcode')
			if firstLayerfound:
				gcodeBuffer.append(gcodeToCoord(line))
		#current layer index output
		print(layerIndex, end='\r')
	print('TOTAL NUM LAYERS: ', totalNumLayers)
	print('TOTAL NUM TASKS: ', totalNumJobs)

	#make json and output file
	print('setting up json file')
	f1 = open(outputfile, 'w')
	print('dumping cleaned gcode to: ', outputfile)
	something = json.dumps(layers,indent=5, sort_keys=False)
	f1.write(something)
	f1.close()
	print('done!')

if __name__ == '__main__':
#loop trough all lines in file
	main()