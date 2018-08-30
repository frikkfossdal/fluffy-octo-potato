import sys
import json
import io
import re

#data_buffers
layers = {}
types = {}
gcode = []
prevLayer = ''
prevType = ''
prevZheight = 0 
prevFeed = 0

#data indexes 
layerIndex = 0
typesIndex = 0
operationIndex = 0 
maxOperations = 0

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
#keep track of layerCount, operations and gcode
def operationTracker(gcodeline): 
	global layerIndex
	global typesIndex
	global maxOperations
	if 'LAYER:' in gcodeline:
		layerIndex += 1
		print('LAYER NUMBER: ', layerIndex)
		print('NUMBER OF OPS: ', typesIndex)
		typesIndex = 0

	if 'TYPE:' in gcodeline:
		typesIndex += 1
		#print(typesIndex)

	if('G0' in gcodeline or 'G1' in gcodeline):
		gcodeline = gcodeToCoord(gcodeline)
		gcode.append(gcodeline)
		#print(gcodeline)

def main():
	#handle human and file
	print(sys.argv[1], 'loaded')
	print('sorting gcode and cleaning coordinates')
	inputfile = sys.argv[1]
	outpulfile = sys.argv[2]
	gcode = open(inputfile, 'r')
	gcode = gcode.readlines()

	#empty global variables 
	prevZheight = 0

	#loop trough gcode and rebuild it
	for line in gcode: 
		operationTracker(line)
	f1 = open(outpulfile, 'w')
	json = json.dumps(layers,indent=5, sort_keys=True)
	f1.write(json)
	f1.close()

if __name__ == '__main__':
#loop trough all lines in file
	main()