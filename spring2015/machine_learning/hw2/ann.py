from pybrain.structure import FullConnection, FeedForwardNetwork, SigmoidLayer, LinearLayer, SoftmaxLayer
from pybrain.supervised.trainers import BackpropTrainer
from pybrain.tools.shortcuts     import buildNetwork
from pybrain.utilities           import percentError

class net:

	def __init__(self,layer_type):
		self.inputLayer = LinearLayer(2)
		self.hiddenLayer = layer_type(10)
		self.outputLayer = layer_type(2)

		self.net = FeedForwardNetwork()
		self.net.addInputModule(self.inputLayer)
		self.net.addModule(self.hiddenLayer)
		self.net.addOutputModule(self.outputLayer)

		self.inputToHidden = FullConnection(self.inputLayer,self.hiddenLayer)
		self.hiddenToOutput = FullConnection(self.hiddenLayer,self.outputLayer)

		self.net.addConnection(self.inputToHidden)
		self.net.addConnection(self.hiddenToOutput)

		self.net.sortModules()

import numpy as np

alldataRaw = [ ([x,y],[int(np.power(x-.5,2)+np.power(y-.6,2)<.16)]) for (x,y) in zip(np.random.uniform(0,1,size=200), np.random.uniform(0,1,size=200)) ]

from pybrain.datasets import ClassificationDataSet

trndata = ClassificationDataSet(2, nb_classes=2, class_labels=['inside','outside'])
tstdata = ClassificationDataSet(2, nb_classes=2, class_labels=['inside','outside'])

for i in range(100):
	trndata.appendLinked(alldataRaw[i][0],alldataRaw[i][1])
	tstdata.appendLinked(alldataRaw[i+100][0],alldataRaw[i+100][1])


trndata._convertToOneOfMany()
tstdata._convertToOneOfMany()


for epochs in range(20):
	signet = net(SigmoidLayer)
	stepnet = net(SoftmaxLayer)

	trainer1 = BackpropTrainer( signet.net, dataset=trndata,verbose=False, weightdecay=0.01)
	trainer2 = BackpropTrainer( stepnet.net, dataset=trndata,verbose=False, weightdecay=0.01)

	print("\n*** Sigmoid net\n")
	trainer1.trainEpochs(epochs)
	trnresult1 = percentError( trainer1.testOnClassData(), trndata['class'] )
	tstresult1 = percentError( trainer1.testOnClassData(dataset=tstdata ), tstdata['class'] )
	print "*** epochs: %4d" % trainer1.totalepochs, "  train error: %5.2f%%" % trnresult1, "  test error: %5.2f%%" % tstresult1	
	print "*** Hyperplane Parameters"
	print signet.hiddenToOutput.params
		
	print("\n*** Step function net\n")
	trainer2.trainEpochs(epochs)
	trnresult2 = percentError( trainer2.testOnClassData(), trndata['class'] )
	tstresult2 = percentError( trainer2.testOnClassData(dataset=tstdata ), tstdata['class'] )	
	print "*** epochs: %4d" % trainer2.totalepochs, "  train error: %5.2f%%" % trnresult2, "  test error: %5.2f%%" % tstresult2
	print "*** Hyperplane Parameters"	
	print stepnet.hiddenToOutput.params
'''
out1 = signet.net.activateOnDataset(tstdata)
out1 = out1.argmax(axis=1)  # the highest output activation gives the class
out2 = stepnet.net.activateOnDataset(tstdata)
out2 = out2.argmax(axis=1)  # the highest output activation gives the class'''
