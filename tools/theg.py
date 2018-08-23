import sys
import json 
import io

#handle the file as argument
print(sys.argv[1], 'loaded')
print('sorting gcode..')
fileName = sys.argv[1]
gcode = open(fileName,'r')
gcodelines = gcode.readlines()

#data_buffers
layers = {}
typesBuffer = {}
gcodeBuffer = []

fileName = 'parsed_gcode'

#data_indexes 
layerIndex = 0
typesIndex = 0
operationIndex = 0
prevLayer = ''
prevType = ''

#loop trough all lines 
for i in range(0,len(gcodelines)):
	l1 = gcodelines[i].strip()
	#search for first layer
	if('LAYER:' in l1):
		#check if first layer exists: 
		if(typesIndex > 0):
			typesBuffer[typesIndex-1] = {'type': prevType, 'gcode' : 'gcodeBuffer'}
			typesIndex += 1
			prevType = l1.replace(';TYPE:','')
			gcodeBuffer = []	

		if(layerIndex > 0):
			layers[layerIndex-1] = typesBuffer
			typesBuffer = {}
			layerIndex += 1
			typesIndex = 0
			prevLayer = l1
		else: 
			layers[layerIndex] = ''
			layerIndex += 1
			prevLayer = l1
	if('TYPE:' in l1):
		#check if first type exists
		#allways add gcodebuffer to previous operation 
		if(typesIndex > 0):
			typesBuffer[typesIndex-1] = {'type': prevType, 'gcode' : 'gcodeBuffer'}
			typesIndex += 1
			prevType = l1.replace(';TYPE:','')
		else:
			typesBuffer[typesIndex] = {'type': l1, 'gcode' : 'gcodeBuffer'}
			typesIndex += 1
			prevType = l1.replace(';TYPE:','')
		gcodeBuffer = []
			
	#add gcode lines to buffer
	if('G0' in l1 or 'G1' in l1):
		gcodeBuffer.append(l1)

#dump to json 
f1 = open('stig.json', "w")
json = json.dumps(layers,indent=5, sort_keys=True)
f1.write(json)
f1.close()

print('gcode-file is parsed')
print('stored as: ', fileName)

#print(layers)
#print(types[2])

 
	

