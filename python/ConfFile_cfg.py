import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

fileList=[
        #'file:myfile.root'
	## DY3 ##
	'/store/mc/RunIIFall15MiniAODv2/DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/50000/DC696ACA-6BB9-E511-900F-001F2965F212.root'
	## MG ##
	#'/store/mc/RunIIFall15MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/EC68FB75-D5B8-E511-9D29-00259085E8BC.root'
	## AMC ##
	##'/store/mc/RunIIFall15MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8//MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/9073751D-05C8-E511-A802-0025901D40CA.root'
		]

# do not remove the following line
###FILELIST###

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
	    fileList
    )

)

process.TFileService = cms.Service("TFileService",
        closeFileFast = cms.untracked.bool(True),
        fileName = cms.string("output.root"),
        )

process.demo = cms.EDAnalyzer('LHEAnalysis'
)


process.p = cms.Path(process.demo)
