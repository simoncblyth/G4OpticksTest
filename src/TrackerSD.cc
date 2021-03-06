// -----------------------------------------------------
//  _    _        _____         _   
// | |  / \   _ _|_   _|__  ___| |_ 
// | | / _ \ | '__|| |/ _ \/ __| __|
// | |/ ___ \| |   | |  __/\__ \ |_ 
// |_/_/   \_\_|   |_|\___||___/\__|
//                                  
// lArTest: A Geant4 application to study and profile  
//          simulation of physics processes relevant 
//          to liquid Ar TPCs
//
// Author: Hans Wenzel, Fermilab
// -----------------------------------------------------
// Geant4 headers
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
// project headers
#include "TrackerSD.hh"
//#include "ConfigurationManager.hh"
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::TrackerSD(G4String name)
: G4VSensitiveDetector(name) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TrackerSD::~TrackerSD() {

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerSD::Initialize(G4HCofThisEvent* hce) {

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool TrackerSD::ProcessHits(G4Step* aStep,
        G4TouchableHistory*) {
    G4double edep = aStep->GetTotalEnergyDeposit();
    //std::cout<<"TrackerDS:  "<<aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName()<<" Coy: "<<aStep->GetPostStepPoint()->GetPhysicalVolume()->GetCopyNo()<<std::endl;
    //std::cout<<"TrackerDS:  "<<aStep->GetPostStepPoint()->GetPhysicalVolume()->GetLogicalVolume()<<std::endl;
    if (edep == 0.) return false;
    if (aStep->GetTrack()->GetDynamicParticle()->GetCharge() == 0) return false;
    /*
 //   G4int photons = 0;
    G4SteppingManager* fpSteppingManager = G4EventManager::GetEventManager()
            ->GetTrackingManager()->GetSteppingManager();
   // G4StepStatus stepStatus = fpSteppingManager->GetfStepStatus();
    

  //  ConfigurationManager* cfMgr = ConfigurationManager::getInstance();
   // std::map<G4String, int> *mapOfntIDs = cfMgr->getMapOfntIDs();
    //const G4String name = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName() + "_Tracker";
    //const G4String name = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetName() + "_Tracker";
    //G4int ID = 0;
    //std::map<G4String, int>::iterator iter = mapOfntIDs->find(name);
    //G4int ID = (*mapOfntIDs)[name];
    //std::cout <<"ID:  "<<ID<<std::endl;
    //for (std::map<G4String, int>::iterator ii = mapOfntIDs->begin(); ii != mapOfntIDs->end(); ++ii) {
    //    std::cout << (*ii).first << ": " << (*ii).second << std::endl;
    //}
    //mapOfntIDs[name];
*/
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TrackerSD::EndOfEvent(G4HCofThisEvent*) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
