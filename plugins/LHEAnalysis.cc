// -*- C++ -*-
//
// Package:    LHEAnalysis/LHEAnalysis
// Class:      LHEAnalysis
// 
/**\class LHEAnalysis LHEAnalysis.cc LHEAnalysis/LHEAnalysis/plugins/LHEAnalysis.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andrea Carlo Marini
//         Created:  Sun, 22 May 2016 21:04:15 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

// TFile Service
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

// LHE
//#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
// GEN
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
//#include "SimDataFormats/GeneratorProducts/interface/GenRunInfoProduct.h"

//#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
//#include "DataFormats/Candidate/interface/Candidate.h"
//#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

//#include "DataFormats/JetReco/interface/GenJet.h"
//#include "DataFormats/JetReco/interface/GenJetCollection.h"
//
// class declaration
//

#include "TFile.h"
#include "TTree.h"
// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.
//
#include <iostream>
using namespace std;

class LHEAnalysis : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit LHEAnalysis(const edm::ParameterSet&);
      ~LHEAnalysis();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      //
      edm::Handle<GenEventInfoProduct> handle_ge;
      edm::EDGetTokenT<GenEventInfoProduct> token_ge;


      edm::Service<TFileService> fileService_;
      TTree *tree;
      int np{-999};
      double mcWeight;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
LHEAnalysis::LHEAnalysis(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   //usesResource("TFileService");
   token_ge=consumes<GenEventInfoProduct>(edm::InputTag("generator"));

   tree = fileService_ -> make<TTree>("events", "events");
   tree->Branch("np",&np,"np/I");
   tree->Branch("mcWeight",&mcWeight,"mcWeight/F");
}


LHEAnalysis::~LHEAnalysis()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
LHEAnalysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   iEvent.getByToken(token_ge,handle_ge);

   //cout<<" event GEIP : "<< (*handle_ge).nMEPartons() <<" Filtered "<< (*handle_ge).nMEPartonsFiltered() <<endl;
   //
   np=(*handle_ge).nMEPartons();
   mcWeight=(*handle_ge).weight();
   tree->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
LHEAnalysis::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
LHEAnalysis::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
LHEAnalysis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(LHEAnalysis);
